# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/bryan/devdir/libtestdir/jsoncpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bryan/devdir/libtestdir/jsoncpp/build

# Include any dependencies generated for this target.
include CMakeFiles/jsoncpp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/jsoncpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/jsoncpp.dir/flags.make

CMakeFiles/jsoncpp.dir/jsoncpp.cpp.o: CMakeFiles/jsoncpp.dir/flags.make
CMakeFiles/jsoncpp.dir/jsoncpp.cpp.o: ../jsoncpp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bryan/devdir/libtestdir/jsoncpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/jsoncpp.dir/jsoncpp.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jsoncpp.dir/jsoncpp.cpp.o -c /home/bryan/devdir/libtestdir/jsoncpp/jsoncpp.cpp

CMakeFiles/jsoncpp.dir/jsoncpp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp.dir/jsoncpp.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bryan/devdir/libtestdir/jsoncpp/jsoncpp.cpp > CMakeFiles/jsoncpp.dir/jsoncpp.cpp.i

CMakeFiles/jsoncpp.dir/jsoncpp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp.dir/jsoncpp.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bryan/devdir/libtestdir/jsoncpp/jsoncpp.cpp -o CMakeFiles/jsoncpp.dir/jsoncpp.cpp.s

# Object files for target jsoncpp
jsoncpp_OBJECTS = \
"CMakeFiles/jsoncpp.dir/jsoncpp.cpp.o"

# External object files for target jsoncpp
jsoncpp_EXTERNAL_OBJECTS =

jsoncpp: CMakeFiles/jsoncpp.dir/jsoncpp.cpp.o
jsoncpp: CMakeFiles/jsoncpp.dir/build.make
jsoncpp: /usr/lib/x86_64-linux-gnu/libjsoncpp.so.1.7.4
jsoncpp: CMakeFiles/jsoncpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bryan/devdir/libtestdir/jsoncpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable jsoncpp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jsoncpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/jsoncpp.dir/build: jsoncpp

.PHONY : CMakeFiles/jsoncpp.dir/build

CMakeFiles/jsoncpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/jsoncpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/jsoncpp.dir/clean

CMakeFiles/jsoncpp.dir/depend:
	cd /home/bryan/devdir/libtestdir/jsoncpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bryan/devdir/libtestdir/jsoncpp /home/bryan/devdir/libtestdir/jsoncpp /home/bryan/devdir/libtestdir/jsoncpp/build /home/bryan/devdir/libtestdir/jsoncpp/build /home/bryan/devdir/libtestdir/jsoncpp/build/CMakeFiles/jsoncpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/jsoncpp.dir/depend

