# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.29.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.29.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/znschaffer/src/plyr

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/znschaffer/src/plyr/build

# Include any dependencies generated for this target.
include CMakeFiles/cimgui.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cimgui.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cimgui.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cimgui.dir/flags.make

CMakeFiles/cimgui.dir/cimgui/cimgui.cpp.o: CMakeFiles/cimgui.dir/flags.make
CMakeFiles/cimgui.dir/cimgui/cimgui.cpp.o: /Users/znschaffer/src/plyr/cimgui/cimgui.cpp
CMakeFiles/cimgui.dir/cimgui/cimgui.cpp.o: CMakeFiles/cimgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/znschaffer/src/plyr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cimgui.dir/cimgui/cimgui.cpp.o"
	/opt/homebrew/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cimgui.dir/cimgui/cimgui.cpp.o -MF CMakeFiles/cimgui.dir/cimgui/cimgui.cpp.o.d -o CMakeFiles/cimgui.dir/cimgui/cimgui.cpp.o -c /Users/znschaffer/src/plyr/cimgui/cimgui.cpp

CMakeFiles/cimgui.dir/cimgui/cimgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cimgui.dir/cimgui/cimgui.cpp.i"
	/opt/homebrew/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/znschaffer/src/plyr/cimgui/cimgui.cpp > CMakeFiles/cimgui.dir/cimgui/cimgui.cpp.i

CMakeFiles/cimgui.dir/cimgui/cimgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cimgui.dir/cimgui/cimgui.cpp.s"
	/opt/homebrew/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/znschaffer/src/plyr/cimgui/cimgui.cpp -o CMakeFiles/cimgui.dir/cimgui/cimgui.cpp.s

CMakeFiles/cimgui.dir/cimgui/imgui/imgui.cpp.o: CMakeFiles/cimgui.dir/flags.make
CMakeFiles/cimgui.dir/cimgui/imgui/imgui.cpp.o: /Users/znschaffer/src/plyr/cimgui/imgui/imgui.cpp
CMakeFiles/cimgui.dir/cimgui/imgui/imgui.cpp.o: CMakeFiles/cimgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/znschaffer/src/plyr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cimgui.dir/cimgui/imgui/imgui.cpp.o"
	/opt/homebrew/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cimgui.dir/cimgui/imgui/imgui.cpp.o -MF CMakeFiles/cimgui.dir/cimgui/imgui/imgui.cpp.o.d -o CMakeFiles/cimgui.dir/cimgui/imgui/imgui.cpp.o -c /Users/znschaffer/src/plyr/cimgui/imgui/imgui.cpp

CMakeFiles/cimgui.dir/cimgui/imgui/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cimgui.dir/cimgui/imgui/imgui.cpp.i"
	/opt/homebrew/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/znschaffer/src/plyr/cimgui/imgui/imgui.cpp > CMakeFiles/cimgui.dir/cimgui/imgui/imgui.cpp.i

CMakeFiles/cimgui.dir/cimgui/imgui/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cimgui.dir/cimgui/imgui/imgui.cpp.s"
	/opt/homebrew/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/znschaffer/src/plyr/cimgui/imgui/imgui.cpp -o CMakeFiles/cimgui.dir/cimgui/imgui/imgui.cpp.s

CMakeFiles/cimgui.dir/cimgui/imgui/imgui_widgets.cpp.o: CMakeFiles/cimgui.dir/flags.make
CMakeFiles/cimgui.dir/cimgui/imgui/imgui_widgets.cpp.o: /Users/znschaffer/src/plyr/cimgui/imgui/imgui_widgets.cpp
CMakeFiles/cimgui.dir/cimgui/imgui/imgui_widgets.cpp.o: CMakeFiles/cimgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/znschaffer/src/plyr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/cimgui.dir/cimgui/imgui/imgui_widgets.cpp.o"
	/opt/homebrew/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cimgui.dir/cimgui/imgui/imgui_widgets.cpp.o -MF CMakeFiles/cimgui.dir/cimgui/imgui/imgui_widgets.cpp.o.d -o CMakeFiles/cimgui.dir/cimgui/imgui/imgui_widgets.cpp.o -c /Users/znschaffer/src/plyr/cimgui/imgui/imgui_widgets.cpp

CMakeFiles/cimgui.dir/cimgui/imgui/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cimgui.dir/cimgui/imgui/imgui_widgets.cpp.i"
	/opt/homebrew/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/znschaffer/src/plyr/cimgui/imgui/imgui_widgets.cpp > CMakeFiles/cimgui.dir/cimgui/imgui/imgui_widgets.cpp.i

CMakeFiles/cimgui.dir/cimgui/imgui/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cimgui.dir/cimgui/imgui/imgui_widgets.cpp.s"
	/opt/homebrew/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/znschaffer/src/plyr/cimgui/imgui/imgui_widgets.cpp -o CMakeFiles/cimgui.dir/cimgui/imgui/imgui_widgets.cpp.s

CMakeFiles/cimgui.dir/cimgui/imgui/imgui_draw.cpp.o: CMakeFiles/cimgui.dir/flags.make
CMakeFiles/cimgui.dir/cimgui/imgui/imgui_draw.cpp.o: /Users/znschaffer/src/plyr/cimgui/imgui/imgui_draw.cpp
CMakeFiles/cimgui.dir/cimgui/imgui/imgui_draw.cpp.o: CMakeFiles/cimgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/znschaffer/src/plyr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/cimgui.dir/cimgui/imgui/imgui_draw.cpp.o"
	/opt/homebrew/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cimgui.dir/cimgui/imgui/imgui_draw.cpp.o -MF CMakeFiles/cimgui.dir/cimgui/imgui/imgui_draw.cpp.o.d -o CMakeFiles/cimgui.dir/cimgui/imgui/imgui_draw.cpp.o -c /Users/znschaffer/src/plyr/cimgui/imgui/imgui_draw.cpp

CMakeFiles/cimgui.dir/cimgui/imgui/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cimgui.dir/cimgui/imgui/imgui_draw.cpp.i"
	/opt/homebrew/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/znschaffer/src/plyr/cimgui/imgui/imgui_draw.cpp > CMakeFiles/cimgui.dir/cimgui/imgui/imgui_draw.cpp.i

CMakeFiles/cimgui.dir/cimgui/imgui/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cimgui.dir/cimgui/imgui/imgui_draw.cpp.s"
	/opt/homebrew/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/znschaffer/src/plyr/cimgui/imgui/imgui_draw.cpp -o CMakeFiles/cimgui.dir/cimgui/imgui/imgui_draw.cpp.s

CMakeFiles/cimgui.dir/cimgui/imgui/imgui_tables.cpp.o: CMakeFiles/cimgui.dir/flags.make
CMakeFiles/cimgui.dir/cimgui/imgui/imgui_tables.cpp.o: /Users/znschaffer/src/plyr/cimgui/imgui/imgui_tables.cpp
CMakeFiles/cimgui.dir/cimgui/imgui/imgui_tables.cpp.o: CMakeFiles/cimgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/znschaffer/src/plyr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/cimgui.dir/cimgui/imgui/imgui_tables.cpp.o"
	/opt/homebrew/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cimgui.dir/cimgui/imgui/imgui_tables.cpp.o -MF CMakeFiles/cimgui.dir/cimgui/imgui/imgui_tables.cpp.o.d -o CMakeFiles/cimgui.dir/cimgui/imgui/imgui_tables.cpp.o -c /Users/znschaffer/src/plyr/cimgui/imgui/imgui_tables.cpp

CMakeFiles/cimgui.dir/cimgui/imgui/imgui_tables.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cimgui.dir/cimgui/imgui/imgui_tables.cpp.i"
	/opt/homebrew/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/znschaffer/src/plyr/cimgui/imgui/imgui_tables.cpp > CMakeFiles/cimgui.dir/cimgui/imgui/imgui_tables.cpp.i

CMakeFiles/cimgui.dir/cimgui/imgui/imgui_tables.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cimgui.dir/cimgui/imgui/imgui_tables.cpp.s"
	/opt/homebrew/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/znschaffer/src/plyr/cimgui/imgui/imgui_tables.cpp -o CMakeFiles/cimgui.dir/cimgui/imgui/imgui_tables.cpp.s

CMakeFiles/cimgui.dir/cimgui/imgui/imgui_demo.cpp.o: CMakeFiles/cimgui.dir/flags.make
CMakeFiles/cimgui.dir/cimgui/imgui/imgui_demo.cpp.o: /Users/znschaffer/src/plyr/cimgui/imgui/imgui_demo.cpp
CMakeFiles/cimgui.dir/cimgui/imgui/imgui_demo.cpp.o: CMakeFiles/cimgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/znschaffer/src/plyr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/cimgui.dir/cimgui/imgui/imgui_demo.cpp.o"
	/opt/homebrew/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cimgui.dir/cimgui/imgui/imgui_demo.cpp.o -MF CMakeFiles/cimgui.dir/cimgui/imgui/imgui_demo.cpp.o.d -o CMakeFiles/cimgui.dir/cimgui/imgui/imgui_demo.cpp.o -c /Users/znschaffer/src/plyr/cimgui/imgui/imgui_demo.cpp

CMakeFiles/cimgui.dir/cimgui/imgui/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cimgui.dir/cimgui/imgui/imgui_demo.cpp.i"
	/opt/homebrew/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/znschaffer/src/plyr/cimgui/imgui/imgui_demo.cpp > CMakeFiles/cimgui.dir/cimgui/imgui/imgui_demo.cpp.i

CMakeFiles/cimgui.dir/cimgui/imgui/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cimgui.dir/cimgui/imgui/imgui_demo.cpp.s"
	/opt/homebrew/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/znschaffer/src/plyr/cimgui/imgui/imgui_demo.cpp -o CMakeFiles/cimgui.dir/cimgui/imgui/imgui_demo.cpp.s

# Object files for target cimgui
cimgui_OBJECTS = \
"CMakeFiles/cimgui.dir/cimgui/cimgui.cpp.o" \
"CMakeFiles/cimgui.dir/cimgui/imgui/imgui.cpp.o" \
"CMakeFiles/cimgui.dir/cimgui/imgui/imgui_widgets.cpp.o" \
"CMakeFiles/cimgui.dir/cimgui/imgui/imgui_draw.cpp.o" \
"CMakeFiles/cimgui.dir/cimgui/imgui/imgui_tables.cpp.o" \
"CMakeFiles/cimgui.dir/cimgui/imgui/imgui_demo.cpp.o"

# External object files for target cimgui
cimgui_EXTERNAL_OBJECTS =

libcimgui.a: CMakeFiles/cimgui.dir/cimgui/cimgui.cpp.o
libcimgui.a: CMakeFiles/cimgui.dir/cimgui/imgui/imgui.cpp.o
libcimgui.a: CMakeFiles/cimgui.dir/cimgui/imgui/imgui_widgets.cpp.o
libcimgui.a: CMakeFiles/cimgui.dir/cimgui/imgui/imgui_draw.cpp.o
libcimgui.a: CMakeFiles/cimgui.dir/cimgui/imgui/imgui_tables.cpp.o
libcimgui.a: CMakeFiles/cimgui.dir/cimgui/imgui/imgui_demo.cpp.o
libcimgui.a: CMakeFiles/cimgui.dir/build.make
libcimgui.a: CMakeFiles/cimgui.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/znschaffer/src/plyr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX static library libcimgui.a"
	$(CMAKE_COMMAND) -P CMakeFiles/cimgui.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cimgui.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cimgui.dir/build: libcimgui.a
.PHONY : CMakeFiles/cimgui.dir/build

CMakeFiles/cimgui.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cimgui.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cimgui.dir/clean

CMakeFiles/cimgui.dir/depend:
	cd /Users/znschaffer/src/plyr/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/znschaffer/src/plyr /Users/znschaffer/src/plyr /Users/znschaffer/src/plyr/build /Users/znschaffer/src/plyr/build /Users/znschaffer/src/plyr/build/CMakeFiles/cimgui.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/cimgui.dir/depend

