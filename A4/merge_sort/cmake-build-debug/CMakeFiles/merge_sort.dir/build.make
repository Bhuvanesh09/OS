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
CMAKE_SOURCE_DIR = /mnt/e/OS/A4/merge_sort

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/e/OS/A4/merge_sort/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/merge_sort.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/merge_sort.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/merge_sort.dir/flags.make

CMakeFiles/merge_sort.dir/main.c.o: CMakeFiles/merge_sort.dir/flags.make
CMakeFiles/merge_sort.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/OS/A4/merge_sort/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/merge_sort.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/merge_sort.dir/main.c.o   -c /mnt/e/OS/A4/merge_sort/main.c

CMakeFiles/merge_sort.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/merge_sort.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/e/OS/A4/merge_sort/main.c > CMakeFiles/merge_sort.dir/main.c.i

CMakeFiles/merge_sort.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/merge_sort.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/e/OS/A4/merge_sort/main.c -o CMakeFiles/merge_sort.dir/main.c.s

CMakeFiles/merge_sort.dir/main.c.o.requires:

.PHONY : CMakeFiles/merge_sort.dir/main.c.o.requires

CMakeFiles/merge_sort.dir/main.c.o.provides: CMakeFiles/merge_sort.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/merge_sort.dir/build.make CMakeFiles/merge_sort.dir/main.c.o.provides.build
.PHONY : CMakeFiles/merge_sort.dir/main.c.o.provides

CMakeFiles/merge_sort.dir/main.c.o.provides.build: CMakeFiles/merge_sort.dir/main.c.o


# Object files for target merge_sort
merge_sort_OBJECTS = \
"CMakeFiles/merge_sort.dir/main.c.o"

# External object files for target merge_sort
merge_sort_EXTERNAL_OBJECTS =

merge_sort: CMakeFiles/merge_sort.dir/main.c.o
merge_sort: CMakeFiles/merge_sort.dir/build.make
merge_sort: CMakeFiles/merge_sort.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/e/OS/A4/merge_sort/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable merge_sort"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/merge_sort.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/merge_sort.dir/build: merge_sort

.PHONY : CMakeFiles/merge_sort.dir/build

CMakeFiles/merge_sort.dir/requires: CMakeFiles/merge_sort.dir/main.c.o.requires

.PHONY : CMakeFiles/merge_sort.dir/requires

CMakeFiles/merge_sort.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/merge_sort.dir/cmake_clean.cmake
.PHONY : CMakeFiles/merge_sort.dir/clean

CMakeFiles/merge_sort.dir/depend:
	cd /mnt/e/OS/A4/merge_sort/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/e/OS/A4/merge_sort /mnt/e/OS/A4/merge_sort /mnt/e/OS/A4/merge_sort/cmake-build-debug /mnt/e/OS/A4/merge_sort/cmake-build-debug /mnt/e/OS/A4/merge_sort/cmake-build-debug/CMakeFiles/merge_sort.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/merge_sort.dir/depend

