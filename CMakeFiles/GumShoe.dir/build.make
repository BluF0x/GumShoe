# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/blu/projetos/GumShoe

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/blu/projetos/GumShoe

# Include any dependencies generated for this target.
include CMakeFiles/GumShoe.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/GumShoe.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/GumShoe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GumShoe.dir/flags.make

CMakeFiles/GumShoe.dir/codegen:
.PHONY : CMakeFiles/GumShoe.dir/codegen

CMakeFiles/GumShoe.dir/main.cpp.o: CMakeFiles/GumShoe.dir/flags.make
CMakeFiles/GumShoe.dir/main.cpp.o: main.cpp
CMakeFiles/GumShoe.dir/main.cpp.o: CMakeFiles/GumShoe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/blu/projetos/GumShoe/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GumShoe.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GumShoe.dir/main.cpp.o -MF CMakeFiles/GumShoe.dir/main.cpp.o.d -o CMakeFiles/GumShoe.dir/main.cpp.o -c /home/blu/projetos/GumShoe/main.cpp

CMakeFiles/GumShoe.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GumShoe.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/blu/projetos/GumShoe/main.cpp > CMakeFiles/GumShoe.dir/main.cpp.i

CMakeFiles/GumShoe.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GumShoe.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/blu/projetos/GumShoe/main.cpp -o CMakeFiles/GumShoe.dir/main.cpp.s

# Object files for target GumShoe
GumShoe_OBJECTS = \
"CMakeFiles/GumShoe.dir/main.cpp.o"

# External object files for target GumShoe
GumShoe_EXTERNAL_OBJECTS =

GumShoe: CMakeFiles/GumShoe.dir/main.cpp.o
GumShoe: CMakeFiles/GumShoe.dir/build.make
GumShoe: CMakeFiles/GumShoe.dir/compiler_depend.ts
GumShoe: /usr/lib/libSDL3.so.0.2.10
GumShoe: CMakeFiles/GumShoe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/blu/projetos/GumShoe/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable GumShoe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GumShoe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GumShoe.dir/build: GumShoe
.PHONY : CMakeFiles/GumShoe.dir/build

CMakeFiles/GumShoe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GumShoe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GumShoe.dir/clean

CMakeFiles/GumShoe.dir/depend:
	cd /home/blu/projetos/GumShoe && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/blu/projetos/GumShoe /home/blu/projetos/GumShoe /home/blu/projetos/GumShoe /home/blu/projetos/GumShoe /home/blu/projetos/GumShoe/CMakeFiles/GumShoe.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/GumShoe.dir/depend

