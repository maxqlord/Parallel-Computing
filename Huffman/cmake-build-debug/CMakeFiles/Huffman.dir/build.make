# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/maxlord/Google Drive/Parallel Computing/Huffman"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/maxlord/Google Drive/Parallel Computing/Huffman/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Huffman.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Huffman.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Huffman.dir/flags.make

CMakeFiles/Huffman.dir/main.c.o: CMakeFiles/Huffman.dir/flags.make
CMakeFiles/Huffman.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/maxlord/Google Drive/Parallel Computing/Huffman/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Huffman.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Huffman.dir/main.c.o   -c "/Users/maxlord/Google Drive/Parallel Computing/Huffman/main.c"

CMakeFiles/Huffman.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Huffman.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/maxlord/Google Drive/Parallel Computing/Huffman/main.c" > CMakeFiles/Huffman.dir/main.c.i

CMakeFiles/Huffman.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Huffman.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/maxlord/Google Drive/Parallel Computing/Huffman/main.c" -o CMakeFiles/Huffman.dir/main.c.s

CMakeFiles/Huffman.dir/main.c.o.requires:

.PHONY : CMakeFiles/Huffman.dir/main.c.o.requires

CMakeFiles/Huffman.dir/main.c.o.provides: CMakeFiles/Huffman.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/Huffman.dir/build.make CMakeFiles/Huffman.dir/main.c.o.provides.build
.PHONY : CMakeFiles/Huffman.dir/main.c.o.provides

CMakeFiles/Huffman.dir/main.c.o.provides.build: CMakeFiles/Huffman.dir/main.c.o


# Object files for target Huffman
Huffman_OBJECTS = \
"CMakeFiles/Huffman.dir/main.c.o"

# External object files for target Huffman
Huffman_EXTERNAL_OBJECTS =

Huffman: CMakeFiles/Huffman.dir/main.c.o
Huffman: CMakeFiles/Huffman.dir/build.make
Huffman: CMakeFiles/Huffman.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/maxlord/Google Drive/Parallel Computing/Huffman/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Huffman"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Huffman.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Huffman.dir/build: Huffman

.PHONY : CMakeFiles/Huffman.dir/build

CMakeFiles/Huffman.dir/requires: CMakeFiles/Huffman.dir/main.c.o.requires

.PHONY : CMakeFiles/Huffman.dir/requires

CMakeFiles/Huffman.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Huffman.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Huffman.dir/clean

CMakeFiles/Huffman.dir/depend:
	cd "/Users/maxlord/Google Drive/Parallel Computing/Huffman/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/maxlord/Google Drive/Parallel Computing/Huffman" "/Users/maxlord/Google Drive/Parallel Computing/Huffman" "/Users/maxlord/Google Drive/Parallel Computing/Huffman/cmake-build-debug" "/Users/maxlord/Google Drive/Parallel Computing/Huffman/cmake-build-debug" "/Users/maxlord/Google Drive/Parallel Computing/Huffman/cmake-build-debug/CMakeFiles/Huffman.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Huffman.dir/depend

