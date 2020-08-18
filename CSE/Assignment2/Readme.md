#Name : Dolton Fernandes
#Roll No : 2018111007

*####C-Shell*

###Introduction:

A simple interactive shell written in c.

###Running:

* Run make
* Execute shell by the command : ./a.out

###Files:

* header.h : Contains all the header file , variable , function declarations.
* shell.c : Contains the main loop and some array declarations.
* bgcheck.c : Check if any background process has ended normally or by a signal and updates accordingly.
* echo.c : Print given input on the console.
* execute.c : Finds which command is to be executed and calls the appropriate function.
* format.c : Gets username,hostname,makes the path relative to home directory and does the formatting of strings.
* input.c : Takes care of shell input and formatting.
* ls.c : Prints details of files in provided dirctory with various flags.
* pinfo.c : Prints process related info.
* makefile : Compiles all the .c files to give an executable file.
* history.c : Stores all the typed commands in a file named history in the same directory as the a.out file. It also prints them on request.
* dirty.c : Prints the amount of dirty memory after specified amount of time untill the key 'q' is pressed.