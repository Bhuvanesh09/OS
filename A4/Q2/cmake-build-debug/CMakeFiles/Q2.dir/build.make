# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/e/OS/A4/Q2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/e/OS/A4/Q2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Q2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Q2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Q2.dir/flags.make

CMakeFiles/Q2.dir/main.c.o: CMakeFiles/Q2.dir/flags.make
CMakeFiles/Q2.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/OS/A4/Q2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Q2.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Q2.dir/main.c.o   -c /mnt/e/OS/A4/Q2/main.c

CMakeFiles/Q2.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Q2.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/e/OS/A4/Q2/main.c > CMakeFiles/Q2.dir/main.c.i

CMakeFiles/Q2.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Q2.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/e/OS/A4/Q2/main.c -o CMakeFiles/Q2.dir/main.c.s

CMakeFiles/Q2.dir/main.c.o.requires:

.PHONY : CMakeFiles/Q2.dir/main.c.o.requires

CMakeFiles/Q2.dir/main.c.o.provides: CMakeFiles/Q2.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/Q2.dir/build.make CMakeFiles/Q2.dir/main.c.o.provides.build
.PHONY : CMakeFiles/Q2.dir/main.c.o.provides

CMakeFiles/Q2.dir/main.c.o.provides.build: CMakeFiles/Q2.dir/main.c.o


CMakeFiles/Q2.dir/student.c.o: CMakeFiles/Q2.dir/flags.make
CMakeFiles/Q2.dir/student.c.o: ../student.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/OS/A4/Q2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Q2.dir/student.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Q2.dir/student.c.o   -c /mnt/e/OS/A4/Q2/student.c

CMakeFiles/Q2.dir/student.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Q2.dir/student.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/e/OS/A4/Q2/student.c > CMakeFiles/Q2.dir/student.c.i

CMakeFiles/Q2.dir/student.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Q2.dir/student.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/e/OS/A4/Q2/student.c -o CMakeFiles/Q2.dir/student.c.s

CMakeFiles/Q2.dir/student.c.o.requires:

.PHONY : CMakeFiles/Q2.dir/student.c.o.requires

CMakeFiles/Q2.dir/student.c.o.provides: CMakeFiles/Q2.dir/student.c.o.requires
	$(MAKE) -f CMakeFiles/Q2.dir/build.make CMakeFiles/Q2.dir/student.c.o.provides.build
.PHONY : CMakeFiles/Q2.dir/student.c.o.provides

CMakeFiles/Q2.dir/student.c.o.provides.build: CMakeFiles/Q2.dir/student.c.o


CMakeFiles/Q2.dir/zone.c.o: CMakeFiles/Q2.dir/flags.make
CMakeFiles/Q2.dir/zone.c.o: ../zone.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/OS/A4/Q2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Q2.dir/zone.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Q2.dir/zone.c.o   -c /mnt/e/OS/A4/Q2/zone.c

CMakeFiles/Q2.dir/zone.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Q2.dir/zone.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/e/OS/A4/Q2/zone.c > CMakeFiles/Q2.dir/zone.c.i

CMakeFiles/Q2.dir/zone.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Q2.dir/zone.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/e/OS/A4/Q2/zone.c -o CMakeFiles/Q2.dir/zone.c.s

CMakeFiles/Q2.dir/zone.c.o.requires:

.PHONY : CMakeFiles/Q2.dir/zone.c.o.requires

CMakeFiles/Q2.dir/zone.c.o.provides: CMakeFiles/Q2.dir/zone.c.o.requires
	$(MAKE) -f CMakeFiles/Q2.dir/build.make CMakeFiles/Q2.dir/zone.c.o.provides.build
.PHONY : CMakeFiles/Q2.dir/zone.c.o.provides

CMakeFiles/Q2.dir/zone.c.o.provides.build: CMakeFiles/Q2.dir/zone.c.o


CMakeFiles/Q2.dir/pharma.c.o: CMakeFiles/Q2.dir/flags.make
CMakeFiles/Q2.dir/pharma.c.o: ../pharma.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/OS/A4/Q2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Q2.dir/pharma.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Q2.dir/pharma.c.o   -c /mnt/e/OS/A4/Q2/pharma.c

CMakeFiles/Q2.dir/pharma.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Q2.dir/pharma.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/e/OS/A4/Q2/pharma.c > CMakeFiles/Q2.dir/pharma.c.i

CMakeFiles/Q2.dir/pharma.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Q2.dir/pharma.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/e/OS/A4/Q2/pharma.c -o CMakeFiles/Q2.dir/pharma.c.s

CMakeFiles/Q2.dir/pharma.c.o.requires:

.PHONY : CMakeFiles/Q2.dir/pharma.c.o.requires

CMakeFiles/Q2.dir/pharma.c.o.provides: CMakeFiles/Q2.dir/pharma.c.o.requires
	$(MAKE) -f CMakeFiles/Q2.dir/build.make CMakeFiles/Q2.dir/pharma.c.o.provides.build
.PHONY : CMakeFiles/Q2.dir/pharma.c.o.provides

CMakeFiles/Q2.dir/pharma.c.o.provides.build: CMakeFiles/Q2.dir/pharma.c.o


# Object files for target Q2
Q2_OBJECTS = \
"CMakeFiles/Q2.dir/main.c.o" \
"CMakeFiles/Q2.dir/student.c.o" \
"CMakeFiles/Q2.dir/zone.c.o" \
"CMakeFiles/Q2.dir/pharma.c.o"

# External object files for target Q2
Q2_EXTERNAL_OBJECTS =

Q2: CMakeFiles/Q2.dir/main.c.o
Q2: CMakeFiles/Q2.dir/student.c.o
Q2: CMakeFiles/Q2.dir/zone.c.o
Q2: CMakeFiles/Q2.dir/pharma.c.o
Q2: CMakeFiles/Q2.dir/build.make
Q2: CMakeFiles/Q2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/e/OS/A4/Q2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable Q2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Q2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Q2.dir/build: Q2

.PHONY : CMakeFiles/Q2.dir/build

CMakeFiles/Q2.dir/requires: CMakeFiles/Q2.dir/main.c.o.requires
CMakeFiles/Q2.dir/requires: CMakeFiles/Q2.dir/student.c.o.requires
CMakeFiles/Q2.dir/requires: CMakeFiles/Q2.dir/zone.c.o.requires
CMakeFiles/Q2.dir/requires: CMakeFiles/Q2.dir/pharma.c.o.requires

.PHONY : CMakeFiles/Q2.dir/requires

CMakeFiles/Q2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Q2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Q2.dir/clean

CMakeFiles/Q2.dir/depend:
	cd /mnt/e/OS/A4/Q2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/e/OS/A4/Q2 /mnt/e/OS/A4/Q2 /mnt/e/OS/A4/Q2/cmake-build-debug /mnt/e/OS/A4/Q2/cmake-build-debug /mnt/e/OS/A4/Q2/cmake-build-debug/CMakeFiles/Q2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Q2.dir/depend

