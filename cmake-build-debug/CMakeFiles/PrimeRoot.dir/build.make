# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /snap/clion/123/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/123/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/blackberry/Projects/PrimeRoot

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/blackberry/Projects/PrimeRoot/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/PrimeRoot.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PrimeRoot.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PrimeRoot.dir/flags.make

CMakeFiles/PrimeRoot.dir/main.cpp.o: CMakeFiles/PrimeRoot.dir/flags.make
CMakeFiles/PrimeRoot.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/blackberry/Projects/PrimeRoot/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PrimeRoot.dir/main.cpp.o"
	/usr/bin/mpic++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PrimeRoot.dir/main.cpp.o -c /home/blackberry/Projects/PrimeRoot/main.cpp

CMakeFiles/PrimeRoot.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PrimeRoot.dir/main.cpp.i"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/blackberry/Projects/PrimeRoot/main.cpp > CMakeFiles/PrimeRoot.dir/main.cpp.i

CMakeFiles/PrimeRoot.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PrimeRoot.dir/main.cpp.s"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/blackberry/Projects/PrimeRoot/main.cpp -o CMakeFiles/PrimeRoot.dir/main.cpp.s

CMakeFiles/PrimeRoot.dir/src/Step_Functions.cpp.o: CMakeFiles/PrimeRoot.dir/flags.make
CMakeFiles/PrimeRoot.dir/src/Step_Functions.cpp.o: ../src/Step_Functions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/blackberry/Projects/PrimeRoot/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PrimeRoot.dir/src/Step_Functions.cpp.o"
	/usr/bin/mpic++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PrimeRoot.dir/src/Step_Functions.cpp.o -c /home/blackberry/Projects/PrimeRoot/src/Step_Functions.cpp

CMakeFiles/PrimeRoot.dir/src/Step_Functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PrimeRoot.dir/src/Step_Functions.cpp.i"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/blackberry/Projects/PrimeRoot/src/Step_Functions.cpp > CMakeFiles/PrimeRoot.dir/src/Step_Functions.cpp.i

CMakeFiles/PrimeRoot.dir/src/Step_Functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PrimeRoot.dir/src/Step_Functions.cpp.s"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/blackberry/Projects/PrimeRoot/src/Step_Functions.cpp -o CMakeFiles/PrimeRoot.dir/src/Step_Functions.cpp.s

CMakeFiles/PrimeRoot.dir/src/Memory_Functions.cpp.o: CMakeFiles/PrimeRoot.dir/flags.make
CMakeFiles/PrimeRoot.dir/src/Memory_Functions.cpp.o: ../src/Memory_Functions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/blackberry/Projects/PrimeRoot/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/PrimeRoot.dir/src/Memory_Functions.cpp.o"
	/usr/bin/mpic++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PrimeRoot.dir/src/Memory_Functions.cpp.o -c /home/blackberry/Projects/PrimeRoot/src/Memory_Functions.cpp

CMakeFiles/PrimeRoot.dir/src/Memory_Functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PrimeRoot.dir/src/Memory_Functions.cpp.i"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/blackberry/Projects/PrimeRoot/src/Memory_Functions.cpp > CMakeFiles/PrimeRoot.dir/src/Memory_Functions.cpp.i

CMakeFiles/PrimeRoot.dir/src/Memory_Functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PrimeRoot.dir/src/Memory_Functions.cpp.s"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/blackberry/Projects/PrimeRoot/src/Memory_Functions.cpp -o CMakeFiles/PrimeRoot.dir/src/Memory_Functions.cpp.s

CMakeFiles/PrimeRoot.dir/src/Iterator_Functions.cpp.o: CMakeFiles/PrimeRoot.dir/flags.make
CMakeFiles/PrimeRoot.dir/src/Iterator_Functions.cpp.o: ../src/Iterator_Functions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/blackberry/Projects/PrimeRoot/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/PrimeRoot.dir/src/Iterator_Functions.cpp.o"
	/usr/bin/mpic++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PrimeRoot.dir/src/Iterator_Functions.cpp.o -c /home/blackberry/Projects/PrimeRoot/src/Iterator_Functions.cpp

CMakeFiles/PrimeRoot.dir/src/Iterator_Functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PrimeRoot.dir/src/Iterator_Functions.cpp.i"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/blackberry/Projects/PrimeRoot/src/Iterator_Functions.cpp > CMakeFiles/PrimeRoot.dir/src/Iterator_Functions.cpp.i

CMakeFiles/PrimeRoot.dir/src/Iterator_Functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PrimeRoot.dir/src/Iterator_Functions.cpp.s"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/blackberry/Projects/PrimeRoot/src/Iterator_Functions.cpp -o CMakeFiles/PrimeRoot.dir/src/Iterator_Functions.cpp.s

# Object files for target PrimeRoot
PrimeRoot_OBJECTS = \
"CMakeFiles/PrimeRoot.dir/main.cpp.o" \
"CMakeFiles/PrimeRoot.dir/src/Step_Functions.cpp.o" \
"CMakeFiles/PrimeRoot.dir/src/Memory_Functions.cpp.o" \
"CMakeFiles/PrimeRoot.dir/src/Iterator_Functions.cpp.o"

# External object files for target PrimeRoot
PrimeRoot_EXTERNAL_OBJECTS =

PrimeRoot: CMakeFiles/PrimeRoot.dir/main.cpp.o
PrimeRoot: CMakeFiles/PrimeRoot.dir/src/Step_Functions.cpp.o
PrimeRoot: CMakeFiles/PrimeRoot.dir/src/Memory_Functions.cpp.o
PrimeRoot: CMakeFiles/PrimeRoot.dir/src/Iterator_Functions.cpp.o
PrimeRoot: CMakeFiles/PrimeRoot.dir/build.make
PrimeRoot: /usr/lib/x86_64-linux-gnu/libgmp.a
PrimeRoot: /usr/lib/x86_64-linux-gnu/libgmpxx.a
PrimeRoot: /usr/lib/gcc/x86_64-linux-gnu/9/libgomp.so
PrimeRoot: CMakeFiles/PrimeRoot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/blackberry/Projects/PrimeRoot/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable PrimeRoot"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PrimeRoot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PrimeRoot.dir/build: PrimeRoot

.PHONY : CMakeFiles/PrimeRoot.dir/build

CMakeFiles/PrimeRoot.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PrimeRoot.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PrimeRoot.dir/clean

CMakeFiles/PrimeRoot.dir/depend:
	cd /home/blackberry/Projects/PrimeRoot/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/blackberry/Projects/PrimeRoot /home/blackberry/Projects/PrimeRoot /home/blackberry/Projects/PrimeRoot/cmake-build-debug /home/blackberry/Projects/PrimeRoot/cmake-build-debug /home/blackberry/Projects/PrimeRoot/cmake-build-debug/CMakeFiles/PrimeRoot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PrimeRoot.dir/depend

