# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jmacey/teaching/Code/WebAsm/Selection

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jmacey/teaching/Code/WebAsm/Selection

# Include any dependencies generated for this target.
include CMakeFiles/index.js.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/index.js.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/index.js.dir/flags.make

CMakeFiles/index.js.dir/main.cpp.o: CMakeFiles/index.js.dir/flags.make
CMakeFiles/index.js.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jmacey/teaching/Code/WebAsm/Selection/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/index.js.dir/main.cpp.o"
	/Users/jmacey/emsdk/fastcomp/emscripten/em++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/index.js.dir/main.cpp.o -c /Users/jmacey/teaching/Code/WebAsm/Selection/main.cpp

CMakeFiles/index.js.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/index.js.dir/main.cpp.i"
	/Users/jmacey/emsdk/fastcomp/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jmacey/teaching/Code/WebAsm/Selection/main.cpp > CMakeFiles/index.js.dir/main.cpp.i

CMakeFiles/index.js.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/index.js.dir/main.cpp.s"
	/Users/jmacey/emsdk/fastcomp/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jmacey/teaching/Code/WebAsm/Selection/main.cpp -o CMakeFiles/index.js.dir/main.cpp.s

# Object files for target index.js
index_js_OBJECTS = \
"CMakeFiles/index.js.dir/main.cpp.o"

# External object files for target index.js
index_js_EXTERNAL_OBJECTS =

index.js: CMakeFiles/index.js.dir/main.cpp.o
index.js: CMakeFiles/index.js.dir/build.make
index.js: CMakeFiles/index.js.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jmacey/teaching/Code/WebAsm/Selection/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable index.js"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/index.js.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/index.js.dir/build: index.js

.PHONY : CMakeFiles/index.js.dir/build

CMakeFiles/index.js.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/index.js.dir/cmake_clean.cmake
.PHONY : CMakeFiles/index.js.dir/clean

CMakeFiles/index.js.dir/depend:
	cd /Users/jmacey/teaching/Code/WebAsm/Selection && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jmacey/teaching/Code/WebAsm/Selection /Users/jmacey/teaching/Code/WebAsm/Selection /Users/jmacey/teaching/Code/WebAsm/Selection /Users/jmacey/teaching/Code/WebAsm/Selection /Users/jmacey/teaching/Code/WebAsm/Selection/CMakeFiles/index.js.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/index.js.dir/depend

