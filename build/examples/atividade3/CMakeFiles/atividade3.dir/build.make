# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_SOURCE_DIR = /home/maracaja/Programacao/CG/Atividade3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/maracaja/Programacao/CG/Atividade3/build

# Include any dependencies generated for this target.
include examples/atividade3/CMakeFiles/atividade3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/atividade3/CMakeFiles/atividade3.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/atividade3/CMakeFiles/atividade3.dir/progress.make

# Include the compile flags for this target's objects.
include examples/atividade3/CMakeFiles/atividade3.dir/flags.make

examples/atividade3/CMakeFiles/atividade3.dir/main.cpp.o: examples/atividade3/CMakeFiles/atividade3.dir/flags.make
examples/atividade3/CMakeFiles/atividade3.dir/main.cpp.o: examples/atividade3/CMakeFiles/atividade3.dir/includes_CXX.rsp
examples/atividade3/CMakeFiles/atividade3.dir/main.cpp.o: /home/maracaja/Programacao/CG/Atividade3/examples/atividade3/main.cpp
examples/atividade3/CMakeFiles/atividade3.dir/main.cpp.o: examples/atividade3/CMakeFiles/atividade3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maracaja/Programacao/CG/Atividade3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/atividade3/CMakeFiles/atividade3.dir/main.cpp.o"
	cd /home/maracaja/Programacao/CG/Atividade3/build/examples/atividade3 && /usr/bin/ccache /home/maracaja/bin/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/atividade3/CMakeFiles/atividade3.dir/main.cpp.o -MF CMakeFiles/atividade3.dir/main.cpp.o.d -o CMakeFiles/atividade3.dir/main.cpp.o -c /home/maracaja/Programacao/CG/Atividade3/examples/atividade3/main.cpp

examples/atividade3/CMakeFiles/atividade3.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/atividade3.dir/main.cpp.i"
	cd /home/maracaja/Programacao/CG/Atividade3/build/examples/atividade3 && /home/maracaja/bin/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maracaja/Programacao/CG/Atividade3/examples/atividade3/main.cpp > CMakeFiles/atividade3.dir/main.cpp.i

examples/atividade3/CMakeFiles/atividade3.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/atividade3.dir/main.cpp.s"
	cd /home/maracaja/Programacao/CG/Atividade3/build/examples/atividade3 && /home/maracaja/bin/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maracaja/Programacao/CG/Atividade3/examples/atividade3/main.cpp -o CMakeFiles/atividade3.dir/main.cpp.s

examples/atividade3/CMakeFiles/atividade3.dir/window.cpp.o: examples/atividade3/CMakeFiles/atividade3.dir/flags.make
examples/atividade3/CMakeFiles/atividade3.dir/window.cpp.o: examples/atividade3/CMakeFiles/atividade3.dir/includes_CXX.rsp
examples/atividade3/CMakeFiles/atividade3.dir/window.cpp.o: /home/maracaja/Programacao/CG/Atividade3/examples/atividade3/window.cpp
examples/atividade3/CMakeFiles/atividade3.dir/window.cpp.o: examples/atividade3/CMakeFiles/atividade3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maracaja/Programacao/CG/Atividade3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object examples/atividade3/CMakeFiles/atividade3.dir/window.cpp.o"
	cd /home/maracaja/Programacao/CG/Atividade3/build/examples/atividade3 && /usr/bin/ccache /home/maracaja/bin/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/atividade3/CMakeFiles/atividade3.dir/window.cpp.o -MF CMakeFiles/atividade3.dir/window.cpp.o.d -o CMakeFiles/atividade3.dir/window.cpp.o -c /home/maracaja/Programacao/CG/Atividade3/examples/atividade3/window.cpp

examples/atividade3/CMakeFiles/atividade3.dir/window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/atividade3.dir/window.cpp.i"
	cd /home/maracaja/Programacao/CG/Atividade3/build/examples/atividade3 && /home/maracaja/bin/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maracaja/Programacao/CG/Atividade3/examples/atividade3/window.cpp > CMakeFiles/atividade3.dir/window.cpp.i

examples/atividade3/CMakeFiles/atividade3.dir/window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/atividade3.dir/window.cpp.s"
	cd /home/maracaja/Programacao/CG/Atividade3/build/examples/atividade3 && /home/maracaja/bin/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maracaja/Programacao/CG/Atividade3/examples/atividade3/window.cpp -o CMakeFiles/atividade3.dir/window.cpp.s

examples/atividade3/CMakeFiles/atividade3.dir/chao.cpp.o: examples/atividade3/CMakeFiles/atividade3.dir/flags.make
examples/atividade3/CMakeFiles/atividade3.dir/chao.cpp.o: examples/atividade3/CMakeFiles/atividade3.dir/includes_CXX.rsp
examples/atividade3/CMakeFiles/atividade3.dir/chao.cpp.o: /home/maracaja/Programacao/CG/Atividade3/examples/atividade3/chao.cpp
examples/atividade3/CMakeFiles/atividade3.dir/chao.cpp.o: examples/atividade3/CMakeFiles/atividade3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maracaja/Programacao/CG/Atividade3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object examples/atividade3/CMakeFiles/atividade3.dir/chao.cpp.o"
	cd /home/maracaja/Programacao/CG/Atividade3/build/examples/atividade3 && /usr/bin/ccache /home/maracaja/bin/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/atividade3/CMakeFiles/atividade3.dir/chao.cpp.o -MF CMakeFiles/atividade3.dir/chao.cpp.o.d -o CMakeFiles/atividade3.dir/chao.cpp.o -c /home/maracaja/Programacao/CG/Atividade3/examples/atividade3/chao.cpp

examples/atividade3/CMakeFiles/atividade3.dir/chao.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/atividade3.dir/chao.cpp.i"
	cd /home/maracaja/Programacao/CG/Atividade3/build/examples/atividade3 && /home/maracaja/bin/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maracaja/Programacao/CG/Atividade3/examples/atividade3/chao.cpp > CMakeFiles/atividade3.dir/chao.cpp.i

examples/atividade3/CMakeFiles/atividade3.dir/chao.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/atividade3.dir/chao.cpp.s"
	cd /home/maracaja/Programacao/CG/Atividade3/build/examples/atividade3 && /home/maracaja/bin/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maracaja/Programacao/CG/Atividade3/examples/atividade3/chao.cpp -o CMakeFiles/atividade3.dir/chao.cpp.s

examples/atividade3/CMakeFiles/atividade3.dir/camera.cpp.o: examples/atividade3/CMakeFiles/atividade3.dir/flags.make
examples/atividade3/CMakeFiles/atividade3.dir/camera.cpp.o: examples/atividade3/CMakeFiles/atividade3.dir/includes_CXX.rsp
examples/atividade3/CMakeFiles/atividade3.dir/camera.cpp.o: /home/maracaja/Programacao/CG/Atividade3/examples/atividade3/camera.cpp
examples/atividade3/CMakeFiles/atividade3.dir/camera.cpp.o: examples/atividade3/CMakeFiles/atividade3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maracaja/Programacao/CG/Atividade3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object examples/atividade3/CMakeFiles/atividade3.dir/camera.cpp.o"
	cd /home/maracaja/Programacao/CG/Atividade3/build/examples/atividade3 && /usr/bin/ccache /home/maracaja/bin/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/atividade3/CMakeFiles/atividade3.dir/camera.cpp.o -MF CMakeFiles/atividade3.dir/camera.cpp.o.d -o CMakeFiles/atividade3.dir/camera.cpp.o -c /home/maracaja/Programacao/CG/Atividade3/examples/atividade3/camera.cpp

examples/atividade3/CMakeFiles/atividade3.dir/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/atividade3.dir/camera.cpp.i"
	cd /home/maracaja/Programacao/CG/Atividade3/build/examples/atividade3 && /home/maracaja/bin/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maracaja/Programacao/CG/Atividade3/examples/atividade3/camera.cpp > CMakeFiles/atividade3.dir/camera.cpp.i

examples/atividade3/CMakeFiles/atividade3.dir/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/atividade3.dir/camera.cpp.s"
	cd /home/maracaja/Programacao/CG/Atividade3/build/examples/atividade3 && /home/maracaja/bin/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maracaja/Programacao/CG/Atividade3/examples/atividade3/camera.cpp -o CMakeFiles/atividade3.dir/camera.cpp.s

# Object files for target atividade3
atividade3_OBJECTS = \
"CMakeFiles/atividade3.dir/main.cpp.o" \
"CMakeFiles/atividade3.dir/window.cpp.o" \
"CMakeFiles/atividade3.dir/chao.cpp.o" \
"CMakeFiles/atividade3.dir/camera.cpp.o"

# External object files for target atividade3
atividade3_EXTERNAL_OBJECTS =

/home/maracaja/Programacao/CG/Atividade3/public/atividade3.js: examples/atividade3/CMakeFiles/atividade3.dir/main.cpp.o
/home/maracaja/Programacao/CG/Atividade3/public/atividade3.js: examples/atividade3/CMakeFiles/atividade3.dir/window.cpp.o
/home/maracaja/Programacao/CG/Atividade3/public/atividade3.js: examples/atividade3/CMakeFiles/atividade3.dir/chao.cpp.o
/home/maracaja/Programacao/CG/Atividade3/public/atividade3.js: examples/atividade3/CMakeFiles/atividade3.dir/camera.cpp.o
/home/maracaja/Programacao/CG/Atividade3/public/atividade3.js: examples/atividade3/CMakeFiles/atividade3.dir/build.make
/home/maracaja/Programacao/CG/Atividade3/public/atividade3.js: abcg/libabcg.a
/home/maracaja/Programacao/CG/Atividade3/public/atividade3.js: abcg/external/fmt/libfmt.a
/home/maracaja/Programacao/CG/Atividade3/public/atividade3.js: abcg/external/imgui/libimgui.a
/home/maracaja/Programacao/CG/Atividade3/public/atividade3.js: examples/atividade3/CMakeFiles/atividade3.dir/linklibs.rsp
/home/maracaja/Programacao/CG/Atividade3/public/atividade3.js: examples/atividade3/CMakeFiles/atividade3.dir/objects1.rsp
/home/maracaja/Programacao/CG/Atividade3/public/atividade3.js: examples/atividade3/CMakeFiles/atividade3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/maracaja/Programacao/CG/Atividade3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable /home/maracaja/Programacao/CG/Atividade3/public/atividade3.js"
	cd /home/maracaja/Programacao/CG/Atividade3/build/examples/atividade3 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/atividade3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/atividade3/CMakeFiles/atividade3.dir/build: /home/maracaja/Programacao/CG/Atividade3/public/atividade3.js
.PHONY : examples/atividade3/CMakeFiles/atividade3.dir/build

examples/atividade3/CMakeFiles/atividade3.dir/clean:
	cd /home/maracaja/Programacao/CG/Atividade3/build/examples/atividade3 && $(CMAKE_COMMAND) -P CMakeFiles/atividade3.dir/cmake_clean.cmake
.PHONY : examples/atividade3/CMakeFiles/atividade3.dir/clean

examples/atividade3/CMakeFiles/atividade3.dir/depend:
	cd /home/maracaja/Programacao/CG/Atividade3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maracaja/Programacao/CG/Atividade3 /home/maracaja/Programacao/CG/Atividade3/examples/atividade3 /home/maracaja/Programacao/CG/Atividade3/build /home/maracaja/Programacao/CG/Atividade3/build/examples/atividade3 /home/maracaja/Programacao/CG/Atividade3/build/examples/atividade3/CMakeFiles/atividade3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/atividade3/CMakeFiles/atividade3.dir/depend

