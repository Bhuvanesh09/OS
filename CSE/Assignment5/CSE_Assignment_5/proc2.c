#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"
#include "pstat.h"

struct {
  struct spinlock lock;
  struct proc proc[5][NPROC];
} ptable;

static struct proc *initproc;

int nextpid = 1;
extern void forkret(void);
extern void trapret(void);

static void wakeup1(void *chan);

void
pinit(void)
{
  initlock(&ptable.lock, "ptable");
}

// Must be called with interrupts disabled
int
cpuid() {
  return mycpu()-cpus;
}

// Must be called with interrupts disabled to avoid the caller being
// rescheduled between reading lapicid and running through the loop.
struct cpu*
mycpu(void)
{
  int apicid, i;
  
  if(readeflags()&FL_IF)
    panic("mycpu called with interrupts enabled\n");
  
  apicid = lapicid();
  // APIC IDs are not guaranteed to be contiguous. Maybe we should have
  // a reverse map, or reserve a register to store &cpus[i].
  for (i = 0; i < ncpu; ++i) {
    if (cpus[i].apicid == apicid)
      return &cpus[i];
  }
  panic("unknown apicid\n");
}

// Disable interrupts so that we are not rescheduled
// while reading proc from the cpu structure
struct proc*
myproc(void) {
  struct cpu *c;
  struct proc *p;
  pushcli();
  c = mycpu();
  p = c->proc;
  popcli();
  return p;
}

//PAGEBREAK: 32
// Look in the process table for an UNUSED proc.
// If found, change state to EMBRYO and initialize
// state required to run in the kernel.
// Otherwise return 0.
static struct proc*
allocproc(void)
{
  struct proc *p;
  char *sp;

  acquire(&ptable.lock);

  for(p = ptable.proc[0]; p < &ptable.proc[0][NPROC]; p++)
  	
    if(p->state == UNUSED)
      goto found;

  release(&ptable.lock);
  return 0;

found:
  p->state = EMBRYO;
  p->pid = nextpid++;

  p->ctime = p->arrival_time = ticks;
  p->rtime = p->etime = p->time_spent = p->num_run = p->cont_time = 0;
  p->current_queue = 1;
  for(int i=0;i<5;i++)
  {
  	p->ticks[i]=0;
  }

  set_priority(60);

  release(&ptable.lock);

  // Allocate kernel stack.
  if((p->kstack = kalloc()) == 0){
    p->state = UNUSED;
    return 0;
  }
  sp = p->kstack + KSTACKSIZE;

  // Leave room for trap frame.
  sp -= sizeof *p->tf;
  p->tf = (struct trapframe*)sp;

  // Set up new context to start executing at forkret,
  // which returns to trapret.
  sp -= 4;
  *(uint*)sp = (uint)trapret;

  sp -= sizeof *p->context;
  p->context = (struct context*)sp;
  memset(p->context, 0, sizeof *p->context);
  p->context->eip = (uint)forkret;

  return p;
}

//PAGEBREAK: 32
// Set up first user process.
void
userinit(void)
{
  struct proc *p;
  extern char _binary_initcode_start[], _binary_initcode_size[];

  p = allocproc();
  
  initproc = p;
  if((p->pgdir = setupkvm()) == 0)
    panic("userinit: out of memory?");
  inituvm(p->pgdir, _binary_initcode_start, (int)_binary_initcode_size);
  p->sz = PGSIZE;
  memset(p->tf, 0, sizeof(*p->tf));
  p->tf->cs = (SEG_UCODE << 3) | DPL_USER;
  p->tf->ds = (SEG_UDATA << 3) | DPL_USER;
  p->tf->es = p->tf->ds;
  p->tf->ss = p->tf->ds;
  p->tf->eflags = FL_IF;
  p->tf->esp = PGSIZE;
  p->tf->eip = 0;  // beginning of initcode.S

  safestrcpy(p->name, "initcode", sizeof(p->name));
  p->cwd = namei("/");

  // this assignment to p->state lets other cores
  // run this process. the acquire forces the above
  // writes to be visible, and the lock is also needed
  // because the assignment might not be atomic.
  acquire(&ptable.lock);

  p->state = RUNNABLE;

  release(&ptable.lock);
}

// Grow current process's memory by n bytes.
// Return 0 on success, -1 on failure.
int
growproc(int n)
{
  uint sz;
  struct proc *curproc = myproc();

  sz = curproc->sz;
  if(n > 0){
    if((sz = allocuvm(curproc->pgdir, sz, sz + n)) == 0)
      return -1;
  } else if(n < 0){
    if((sz = deallocuvm(curproc->pgdir, sz, sz + n)) == 0)
      return -1;
  }
  curproc->sz = sz;
  switchuvm(curproc);
  return 0;
}

// Create a new process copying p as the parent.
// Sets up stack to return as if from system call.
// Caller must set state of returned proc to RUNNABLE.
int
fork(void)
{
  int i, pid;
  struct proc *np;
  struct proc *curproc = myproc();

  // Allocate process.
  if((np = allocproc()) == 0){
    return -1;
  }

  // Copy process state from proc.
  if((np->pgdir = copyuvm(curproc->pgdir, curproc->sz)) == 0){
    kfree(np->kstack);
    np->kstack = 0;
    np->state = UNUSED;
    return -1;
  }
  np->sz = curproc->sz;
  np->parent = curproc;
  *np->tf = *curproc->tf;
  // Clear %eax so that fork returns 0 in the child.
  np->tf->eax = 0;

  for(i = 0; i < NOFILE; i++)
    if(curproc->ofile[i])
      np->ofile[i] = filedup(curproc->ofile[i]);
  np->cwd = idup(curproc->cwd);

  safestrcpy(np->name, curproc->name, sizeof(curproc->name));

  pid = np->pid;

  acquire(&ptable.lock);

  np->state = RUNNABLE;

  release(&ptable.lock);

  return pid;
}

// Exit the current process.  Does not return.
// An exited process remains in the zombie state
// until its parent calls wait() to find out it exited.
void
exit(void)
{
  struct proc *curproc = myproc();
  struct proc *p;
  int fd;

  if(curproc == initproc)
    panic("init exiting");

  // Close all open files.
  for(fd = 0; fd < NOFILE; fd++){
    if(curproc->ofile[fd]){
      fileclose(curproc->ofile[fd]);
      curproc->ofile[fd] = 0;
    }
  }

  begin_op();
  iput(curproc->cwd);
  end_op();
  curproc->cwd = 0;

  curproc->etime = ticks; // End Time

  acquire(&ptable.lock);

  // Parent might be sleeping in wait().
  wakeup1(curproc->parent);

  // Pass abandoned children to init.
  int i=0;
  #ifdef MLFQ
  for(;i<5;i++)
  #endif
  for(p = ptable.proc[i]; p < &ptable.proc[i][NPROC]; p++){
    if(p->parent == curproc){
      p->parent = initproc;
      if(p->state == ZOMBIE)
        wakeup1(initproc);
    }
  }

  // Jump into the scheduler, never to return.
  curproc->state = ZOMBIE;
  sched();
  panic("zombie exit");
}

// Wait for a child process to exit and return its pid.
// Return -1 if this process has no children.
int
wait(void)
{
  struct proc *p;
  int havekids, pid;
  struct proc *curproc = myproc();
  
  acquire(&ptable.lock);
  for(;;){
    // Scan through table looking for exited children.
    havekids = 0;
    int i=0;
    #ifdef MLFQ
    for(;i<5;i++)
    #endif
    for(p = ptable.proc[i]; p < &ptable.proc[i][NPROC]; p++){
      if(p->parent != curproc)
        continue;
      havekids = 1;
      if(p->state == ZOMBIE){
        // Found one.
        pid = p->pid;
        kfree(p->kstack);
        p->kstack = 0;
        freevm(p->pgdir);
        p->pid = 0;
        p->parent = 0;
        p->name[0] = 0;
        p->killed = 0;
        p->state = UNUSED;
        release(&ptable.lock);
        return pid;
      }
    }

    // No point waiting if we don't have any children.
    if(!havekids || curproc->killed){
      release(&ptable.lock);
      return -1;
    }

    // Wait for children to exit.  (See wakeup1 call in proc_exit.)
    sleep(curproc, &ptable.lock);  //DOC: wait-sleep
  }
}

void copyitup(struct proc *x)
{
	struct proc *p;
    for(p = ptable.proc[x->current_queue-2]; p < &ptable.proc[x->current_queue-2][NPROC] && p->state != UNUSED; p++){}
    *p = *x;
	p->current_queue--;
	p->arrival_time = ticks;
	p->time_spent = 0;
}

void copyitdown(struct proc *x)
{
	struct proc *p;
    for(p = ptable.proc[x->current_queue]; p < &ptable.proc[x->current_queue][NPROC] && p->state != UNUSED; p++){}
    *p = *x;
	p->current_queue++;
	p->arrival_time = ticks;
	p->time_spent = 0;
}

void clr(struct proc *p)
{
	p->kstack = 0;
    p->pid = 0;
    p->parent = 0;
    p->name[0] = 0;
    p->killed = 0;
    p->state = UNUSED;
}

//PAGEBREAK: 42
// Per-CPU process scheduler.
// Each CPU calls scheduler() after setting itself up.
// Scheduler never returns.  It loops, doing:
//  - choose a process to run
//  - swtch to start running that process
//  - eventually that process transfers control
//      via swtch back to the scheduler.
void
scheduler(void)
{
  struct cpu *c = mycpu();
  c->proc = 0;

  for(;;){
    // Enable interrupts on this processor.
    sti();

    // Loop over process table looking for process to run.
    acquire(&ptable.lock);
    struct proc *p;

  #ifdef DEFAULT

    for(p = ptable.proc[0]; p < &ptable.proc[0][NPROC]; p++)
    {
      if(p->state != RUNNABLE)
        continue;

      // Switch to chosen process.  It is the process's job
      // to release ptable.lock and then reacquire it
      // before jumping back to us.

      c->proc = p;
      switchuvm(p);
      p->state = RUNNING;
      p->num_run++;

      swtch(&(c->scheduler), p->context);
      switchkvm();

      // Process is done running for now.
      // It should have changed its p->state before coming back.
      c->proc = 0;
    }

  #else
  #ifdef FCFS
    int mini=1e9,process_found=0;
    struct proc *p2;

    // Find process with least creation time
    p2 = 0;
    for(p = ptable.proc[0]; p < &ptable.proc[0][NPROC]; p++)
    {
      if(p->state == RUNNABLE)
      {
        if(mini>p->ctime)
        {
          mini=p->ctime;
          p2=p;
        }
        process_found=1;
      }
    }
    if(!process_found)
    {
      goto there2;
    }
    while(p2->state == RUNNABLE)
    {
      c->proc = p2;
      switchuvm(p2);
      p2->state = RUNNING;
      p2->num_run++;

      swtch(&(c->scheduler), p2->context);
      switchkvm();

      c->proc = 0;
    }
    there2:
  #else
  #ifdef PBS
    int mini=1e9;

    // Find process with highest priority

    for(p = ptable.proc[0]; p < &ptable.proc[0][NPROC]; p++)
    {
      if(p->state == RUNNABLE)
      {
        if(mini>p->priority)
        {
          mini=p->priority;
        }
      }
    }
    for(p = ptable.proc[0]; p < &ptable.proc[0][NPROC]; p++)
    {
      if(p->state == RUNNABLE && p->priority == mini)
      {
	    p->num_run++;
		c->proc = p;
		switchuvm(p);
		p->state = RUNNING;

		swtch(&(c->scheduler), p->context);
		switchkvm();

		c->proc = 0;
      }
    }
  #else
  #ifdef MLFQ

    int onetick = 10;
    // int max_time_in_a_queue[] = {0,200,200,200,200};
    for(int i=0;i<4;i++,onetick*=2)
    {
		int mini=1e9,process_found=0;
		struct proc *p2;

		// Find process with least creation time
		p2 = 0;
		for(p = ptable.proc[i]; p < &ptable.proc[i][NPROC]; p++)
		{
			if(p->state == RUNNABLE && p->pid<3)
			{
				c->proc = p;
				switchuvm(p);
				p->state = RUNNING;
				p->num_run++;

				swtch(&(c->scheduler), p->context);
				switchkvm();

				c->proc = 0;
			}
		}
		for(p = ptable.proc[i]; p < &ptable.proc[i][NPROC]; p++)
		{
			// if(p->state != UNUSED && ticks - p->arrival_time - p->time_spent >= max_time_in_a_queue[i] && i>0)
			// {
			// 	copyitup(p);
			// 	clr(p);
			// 	continue;
			// }
			if(p->state == RUNNABLE && p->pid > 2)
			{
				if(mini>p->ctime)
				{
					mini=p->ctime;
					p2=p;
				}
				process_found=1;
			}
		}
		if(!process_found)
		{
			continue;
		}
		p2->cont_time = 0;
		c->proc = p2;
		switchuvm(p2);
		p2->state = RUNNING;
		p2->num_run++;

		swtch(&(c->scheduler), p2->context);
		switchkvm();

		c->proc = 0;

		if(p2->cont_time >= onetick)
		{
			copyitdown(p2);
			clr(p2);
		}
	}
	for(p = ptable.proc[4]; p < &ptable.proc[4][NPROC]; p++)
    {
	  // if(p->state != UNUSED && ticks - p->arrival_time - p->time_spent >= max_time_in_a_queue[4])
	  // {
		 //  copyitup(p);
		 //  clr(p);
		 //  continue;
	  // }
      if(p->state != RUNNABLE)
        continue;

      c->proc = p;
      p->cont_time = 0;
      switchuvm(p);
      p->state = RUNNING;
      p->num_run++;

      swtch(&(c->scheduler), p->context);
      switchkvm();

      c->proc = 0;
    }

  #endif
  #endif
  #endif
  #endif

    release(&ptable.lock);

  }
}

// Enter scheduler.  Must hold only ptable.lock
// and have changed proc->state. Saves and restores
// intena because intena is a property of this
// kernel thread, not this CPU. It should
// be proc->intena and proc->ncli, but that would
// break in the few places where a lock is held but
// there's no process.
void
sched(void)
{
  int intena;
  struct proc *p = myproc();

  if(!holding(&ptable.lock))
    panic("sched ptable.lock");
  if(mycpu()->ncli != 1)
    panic("sched locks");
  if(p->state == RUNNING)
    panic("sched running");
  if(readeflags()&FL_IF)
    panic("sched interruptible");
  intena = mycpu()->intena;
  swtch(&p->context, mycpu()->scheduler);
  mycpu()->intena = intena;
}

// Give up the CPU for one scheduling round.
void
yield(void)
{
  #ifndef FCFS
  acquire(&ptable.lock);  //DOC: yieldlock
  myproc()->state = RUNNABLE;
  sched();
  release(&ptable.lock);
  #endif
}

// A fork child's very first scheduling by scheduler()
// will swtch here.  "Return" to user space.
void
forkret(void)
{
  static int first = 1;
  // Still holding ptable.lock from scheduler.
  release(&ptable.lock);

  if (first) {
    // Some initialization functions must be run in the context
    // of a regular process (e.g., they call sleep), and thus cannot
    // be run from main().
    first = 0;
    iinit(ROOTDEV);
    initlog(ROOTDEV);
  }

  // Return to "caller", actually trapret (see allocproc).
}

// Atomically release lock and sleep on chan.
// Reacquires lock when awakened.
void
sleep(void *chan, struct spinlock *lk)
{
  struct proc *p = myproc();
  
  if(p == 0)
    panic("sleep");

  if(lk == 0)
    panic("sleep without lk");

  // Must acquire ptable.lock in order to
  // change p->state and then call sched.
  // Once we hold ptable.lock, we can be
  // guaranteed that we won't miss any wakeup
  // (wakeup runs with ptable.lock locked),
  // so it's okay to release lk.
  if(lk != &ptable.lock){  //DOC: sleeplock0
    acquire(&ptable.lock);  //DOC: sleeplock1
    release(lk);
  }
  // Go to sleep.
  p->chan = chan;
  p->state = SLEEPING;

  sched();

  // Tidy up.
  p->chan = 0;

  // Reacquire original lock.
  if(lk != &ptable.lock){  //DOC: sleeplock2
    release(&ptable.lock);
    acquire(lk);
  }
}

//PAGEBREAK!
// Wake up all processes sleeping on chan.
// The ptable lock must be held.
static void
wakeup1(void *chan)
{
  struct proc *p;

  int i=0;
  #ifdef MLFQ
  for(;i<5;i++)
  #endif
  for(p = ptable.proc[i]; p < &ptable.proc[i][NPROC]; p++)
    if(p->state == SLEEPING && p->chan == chan)
      p->state = RUNNABLE;
}

// Wake up all processes sleeping on chan.
void
wakeup(void *chan)
{
  acquire(&ptable.lock);
  wakeup1(chan);
  release(&ptable.lock);
}

// Kill the process with the given pid.
// Process won't exit until it returns
// to user space (see trap in trap.c).
int
kill(int pid)
{
  struct proc *p;

  acquire(&ptable.lock);
  int i=0;
  #ifdef MLFQ
  for(;i<5;i++)
  #endif
  for(p = ptable.proc[i]; p < &ptable.proc[i][NPROC]; p++){
    if(p->pid == pid){
      p->killed = 1;
      // Wake process from sleep if necessary.
      if(p->state == SLEEPING)
        p->state = RUNNABLE;
      release(&ptable.lock);
      return 0;
    }
  }
  release(&ptable.lock);
  return -1;
}

//PAGEBREAK: 36
// Print a process listing to console.  For debugging.
// Runs when user types ^P on console.
// No lock to avoid wedging a stuck machine further.
void
procdump(void)
{
  static char *states[] = {
  [UNUSED]    "unused",
  [EMBRYO]    "embryo",
  [SLEEPING]  "sleep ",
  [RUNNABLE]  "runable",
  [RUNNING]   "run   ",
  [ZOMBIE]    "zombie"
  };
  int i;
  struct proc *p;
  char *state;
  uint pc[10];

  int j=0;
  #ifdef MLFQ
  for(;j<5;j++)
  #endif
  for(p = ptable.proc[j]; p < &ptable.proc[j][NPROC]; p++){
    if(p->state == UNUSED)
      continue;
    if(p->state >= 0 && p->state < NELEM(states) && states[p->state])
      state = states[p->state];
    else
      state = "???";
    cprintf("%d %s %s", p->pid, state, p->name);
    if(p->state == SLEEPING){
      getcallerpcs((uint*)p->context->ebp+2, pc);
      for(i=0; i<10 && pc[i] != 0; i++)
        cprintf(" %p", pc[i]);
    }
    cprintf("\n");
  }
}

int
waitx(int *wtime,int *rtime)
{
  struct proc *p;
  int havekids, pid;
  struct proc *curproc = myproc();

  acquire(&ptable.lock);
  for(;;){
    // Scan through table looking for exited children.
    havekids = 0;
    int i=0;
	#ifdef MLFQ
	for(;i<5;i++)
	#endif
	for(p = ptable.proc[i]; p < &ptable.proc[i][NPROC]; p++){
      if(p->parent != curproc)
        continue;
      havekids = 1;
      if(p->state == ZOMBIE){
        // Found one.
        pid = p->pid;
        kfree(p->kstack);
        p->kstack = 0;
        freevm(p->pgdir);
        p->pid = 0;
        p->parent = 0;
        p->name[0] = 0;
        p->killed = 0;
        p->state = UNUSED;

        *wtime = p->etime - p->ctime - p->rtime; // Waiting Time = End Time - Creation Time - Run Time
        *rtime = p->rtime;                       // Run time

        release(&ptable.lock);
        return pid;
      }
    }

    // No point waiting if we don't have any children.
    if(!havekids || curproc->killed){
      release(&ptable.lock);
      return -1;
    }

    // Wait for children to exit.  (See wakeup1 call in proc_exit.)
    sleep(curproc, &ptable.lock);  //DOC: wait-sleep
  }
}

int
getpinfo(struct proc_stat *x,int pid)
{
  struct proc *p=0;
  int i = 0,f=1;
  #ifdef MLFQ
  for(;i<5 && f;i++)
  #endif
  for(p = ptable.proc[i]; p < &ptable.proc[i][NPROC]; p++)
  {
  	if(p->state != UNUSED)
    if(pid == p->pid)
    {
      f=0;
      break;
    }
  }

  if(f)
  {
  	return -1;
  }

  acquire(&ptable.lock);
  
  x->pid = pid;
  x->runtime = p->rtime;
  x->num_run = p->num_run;
  x->current_queue = p->current_queue;
  for(int i=0;i<5;i++)
  {
  	x->ticks[i] = p->ticks[i];
  }

  release(&ptable.lock);
  return 1;
}

int
set_priority(int x)
{
  struct proc *curproc=myproc();
  if(curproc == 0)
  {
  	return -1;
  }
  int return_value = curproc->priority;;
  curproc->priority = x;
  return return_value;
}

void update_runtime()
{
  struct proc *p;
  acquire(&ptable.lock);
  int i=0;
  #ifdef MLFQ
  for(;i<5;i++)
  #endif
  for(p = ptable.proc[i]; p < &ptable.proc[i][NPROC]; p++)
  {
    if(p->state == RUNNING)
    {
    	p->rtime++;
    	p->time_spent++;
    	p->cont_time++;
    	p->ticks[p->current_queue-1]++;
    }
  }

  // // For Bonus

  // if(ticks%1==0)
  // {
  //   i = 0;
  //   #ifdef MLFQ
  //   for(;i<5;i++)
  //   #endif
  //   for(p = ptable.proc[i]; p < &ptable.proc[i][NPROC]; p++)
  //   {
  //     if(p->state==RUNNING)
  //     {
  //       cprintf("( %d %d )\n",p->pid,p->current_queue);
  //       // cprintf("%d %d\n",p->arrival_time,p->time_spent);
  //     }
  //   }
  // }
  release(&ptable.lock);
}