#include "param.h"

struct proc_stat {
  int pid; // PID of process
  int runtime; // Runtime of process
  int num_run; // Number of time the process is executed
  int current_queue; // Current assigned queue
  int ticks[5]; // Number of ticks each process has received at each of the 5 priority queue
};