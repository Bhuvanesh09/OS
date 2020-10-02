# Assignment 2 : Shell 

```
Submitted by:
Bhuvanesh Sridharan
2018113002
```

## Instructions to compile and run the code:

Note: The makefile for this program was made by cmake.
 
- Go to directory named as cmake-build-debug in A3_Shell run the following command:

> cmake -s .. -b .
> make


- This will result in an executable with the name `shell`.
- You can run the shell by the following command inside the `cmake-build-debug` directory.

> ./shell

## Directory structure of the code:

```
- shell
    - cmake-build-debug
        > MakeFile
    - commands
        > cd.c
        > bg.c
        > fg.c
        > kjob.c
        > environementSetter.c
        > echo.c
        > generalCommand.c
        > ls.c
        > pinfo.c
    - utils
        > inputHandler.c
        > shellStateDef.c
        > piping.c
        > redirection.c
        > signalHandler.c
    
    > commandHandler.c
    > main.c
```

### Note:
 **Each .c file is accompanied by a .h file as well. They and the CLion files are ommited in the above directory structure.**

## Functions of each c file.

### main.c 

- The main function
- Initiates the shellState structure.
- Calls commandHandler.

### commandHandler.c

- Checks the command and calls the appropriate function from various files in command directory.

## Utils:

### piping.c

- handles all the piping in the assignment and handles the exit code.

### redirection.c

- handles redirection and returns appropriate exit code.

### shellStateDef.c

- has the structure shellState
    - Stores homepath of the instance.
    - prints the hud(`<user@system>`);
    - has the current path

### signalHandlers.c

- Handles the decoy function for the ctrlc and ctrlz signals.

### inputHandler.c

- Parses the input and returs the tokenised command and number of parts.
- uses getline to set the command variable

## Commands
### bg.c

- Runs a stopped background process

### fg.c 

- Brings a background process to the front and runs it

### jobs.c

- lists all the current jobs spawned in the current shell sequentially

### kjob.c

- Kills a  job based on its job id

### cd.c

- implements the cd command.

### ls.c

- ls command

### echo.c

- echo command

### pinfo.c 

- pinfo command

### generalCommand.c

- This file handles all the commands which are not part of the above lot.
- Also handles background and foreground apps.

### history.c

- Has code to add to the history, read from history etc in the home directory.

---

The End

---