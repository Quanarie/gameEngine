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
CMAKE_COMMAND = /Users/me/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake

# The command to remove a file.
RM = /Users/me/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/me/my/game_engine/game

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/me/my/game_engine/game/cmake-build-debug

# Include any dependencies generated for this target.
include gameEngineBuild/CMakeFiles/gameEngine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include gameEngineBuild/CMakeFiles/gameEngine.dir/compiler_depend.make

# Include the progress variables for this target.
include gameEngineBuild/CMakeFiles/gameEngine.dir/progress.make

# Include the compile flags for this target's objects.
include gameEngineBuild/CMakeFiles/gameEngine.dir/flags.make

gameEngineBuild/CMakeFiles/gameEngine.dir/src/engine.cpp.o: gameEngineBuild/CMakeFiles/gameEngine.dir/flags.make
gameEngineBuild/CMakeFiles/gameEngine.dir/src/engine.cpp.o: /Users/me/my/game_engine/gameEngine/src/engine.cpp
gameEngineBuild/CMakeFiles/gameEngine.dir/src/engine.cpp.o: gameEngineBuild/CMakeFiles/gameEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/me/my/game_engine/game/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object gameEngineBuild/CMakeFiles/gameEngine.dir/src/engine.cpp.o"
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT gameEngineBuild/CMakeFiles/gameEngine.dir/src/engine.cpp.o -MF CMakeFiles/gameEngine.dir/src/engine.cpp.o.d -o CMakeFiles/gameEngine.dir/src/engine.cpp.o -c /Users/me/my/game_engine/gameEngine/src/engine.cpp

gameEngineBuild/CMakeFiles/gameEngine.dir/src/engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/gameEngine.dir/src/engine.cpp.i"
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/me/my/game_engine/gameEngine/src/engine.cpp > CMakeFiles/gameEngine.dir/src/engine.cpp.i

gameEngineBuild/CMakeFiles/gameEngine.dir/src/engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/gameEngine.dir/src/engine.cpp.s"
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/me/my/game_engine/gameEngine/src/engine.cpp -o CMakeFiles/gameEngine.dir/src/engine.cpp.s

gameEngineBuild/CMakeFiles/gameEngine.dir/src/inputs.cpp.o: gameEngineBuild/CMakeFiles/gameEngine.dir/flags.make
gameEngineBuild/CMakeFiles/gameEngine.dir/src/inputs.cpp.o: /Users/me/my/game_engine/gameEngine/src/inputs.cpp
gameEngineBuild/CMakeFiles/gameEngine.dir/src/inputs.cpp.o: gameEngineBuild/CMakeFiles/gameEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/me/my/game_engine/game/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object gameEngineBuild/CMakeFiles/gameEngine.dir/src/inputs.cpp.o"
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT gameEngineBuild/CMakeFiles/gameEngine.dir/src/inputs.cpp.o -MF CMakeFiles/gameEngine.dir/src/inputs.cpp.o.d -o CMakeFiles/gameEngine.dir/src/inputs.cpp.o -c /Users/me/my/game_engine/gameEngine/src/inputs.cpp

gameEngineBuild/CMakeFiles/gameEngine.dir/src/inputs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/gameEngine.dir/src/inputs.cpp.i"
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/me/my/game_engine/gameEngine/src/inputs.cpp > CMakeFiles/gameEngine.dir/src/inputs.cpp.i

gameEngineBuild/CMakeFiles/gameEngine.dir/src/inputs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/gameEngine.dir/src/inputs.cpp.s"
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/me/my/game_engine/gameEngine/src/inputs.cpp -o CMakeFiles/gameEngine.dir/src/inputs.cpp.s

gameEngineBuild/CMakeFiles/gameEngine.dir/src/options.cpp.o: gameEngineBuild/CMakeFiles/gameEngine.dir/flags.make
gameEngineBuild/CMakeFiles/gameEngine.dir/src/options.cpp.o: /Users/me/my/game_engine/gameEngine/src/options.cpp
gameEngineBuild/CMakeFiles/gameEngine.dir/src/options.cpp.o: gameEngineBuild/CMakeFiles/gameEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/me/my/game_engine/game/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object gameEngineBuild/CMakeFiles/gameEngine.dir/src/options.cpp.o"
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT gameEngineBuild/CMakeFiles/gameEngine.dir/src/options.cpp.o -MF CMakeFiles/gameEngine.dir/src/options.cpp.o.d -o CMakeFiles/gameEngine.dir/src/options.cpp.o -c /Users/me/my/game_engine/gameEngine/src/options.cpp

gameEngineBuild/CMakeFiles/gameEngine.dir/src/options.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/gameEngine.dir/src/options.cpp.i"
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/me/my/game_engine/gameEngine/src/options.cpp > CMakeFiles/gameEngine.dir/src/options.cpp.i

gameEngineBuild/CMakeFiles/gameEngine.dir/src/options.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/gameEngine.dir/src/options.cpp.s"
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/me/my/game_engine/gameEngine/src/options.cpp -o CMakeFiles/gameEngine.dir/src/options.cpp.s

gameEngineBuild/CMakeFiles/gameEngine.dir/src/texture_manager.cpp.o: gameEngineBuild/CMakeFiles/gameEngine.dir/flags.make
gameEngineBuild/CMakeFiles/gameEngine.dir/src/texture_manager.cpp.o: /Users/me/my/game_engine/gameEngine/src/texture_manager.cpp
gameEngineBuild/CMakeFiles/gameEngine.dir/src/texture_manager.cpp.o: gameEngineBuild/CMakeFiles/gameEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/me/my/game_engine/game/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object gameEngineBuild/CMakeFiles/gameEngine.dir/src/texture_manager.cpp.o"
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT gameEngineBuild/CMakeFiles/gameEngine.dir/src/texture_manager.cpp.o -MF CMakeFiles/gameEngine.dir/src/texture_manager.cpp.o.d -o CMakeFiles/gameEngine.dir/src/texture_manager.cpp.o -c /Users/me/my/game_engine/gameEngine/src/texture_manager.cpp

gameEngineBuild/CMakeFiles/gameEngine.dir/src/texture_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/gameEngine.dir/src/texture_manager.cpp.i"
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/me/my/game_engine/gameEngine/src/texture_manager.cpp > CMakeFiles/gameEngine.dir/src/texture_manager.cpp.i

gameEngineBuild/CMakeFiles/gameEngine.dir/src/texture_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/gameEngine.dir/src/texture_manager.cpp.s"
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/me/my/game_engine/gameEngine/src/texture_manager.cpp -o CMakeFiles/gameEngine.dir/src/texture_manager.cpp.s

gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/rectangle_colider_component.cpp.o: gameEngineBuild/CMakeFiles/gameEngine.dir/flags.make
gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/rectangle_colider_component.cpp.o: /Users/me/my/game_engine/gameEngine/src/component/collider/rectangle_colider_component.cpp
gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/rectangle_colider_component.cpp.o: gameEngineBuild/CMakeFiles/gameEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/me/my/game_engine/game/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/rectangle_colider_component.cpp.o"
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/rectangle_colider_component.cpp.o -MF CMakeFiles/gameEngine.dir/src/component/collider/rectangle_colider_component.cpp.o.d -o CMakeFiles/gameEngine.dir/src/component/collider/rectangle_colider_component.cpp.o -c /Users/me/my/game_engine/gameEngine/src/component/collider/rectangle_colider_component.cpp

gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/rectangle_colider_component.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/gameEngine.dir/src/component/collider/rectangle_colider_component.cpp.i"
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/me/my/game_engine/gameEngine/src/component/collider/rectangle_colider_component.cpp > CMakeFiles/gameEngine.dir/src/component/collider/rectangle_colider_component.cpp.i

gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/rectangle_colider_component.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/gameEngine.dir/src/component/collider/rectangle_colider_component.cpp.s"
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/me/my/game_engine/gameEngine/src/component/collider/rectangle_colider_component.cpp -o CMakeFiles/gameEngine.dir/src/component/collider/rectangle_colider_component.cpp.s

gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/collision_detector.cpp.o: gameEngineBuild/CMakeFiles/gameEngine.dir/flags.make
gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/collision_detector.cpp.o: /Users/me/my/game_engine/gameEngine/src/component/collider/collision_detector.cpp
gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/collision_detector.cpp.o: gameEngineBuild/CMakeFiles/gameEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/me/my/game_engine/game/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/collision_detector.cpp.o"
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/collision_detector.cpp.o -MF CMakeFiles/gameEngine.dir/src/component/collider/collision_detector.cpp.o.d -o CMakeFiles/gameEngine.dir/src/component/collider/collision_detector.cpp.o -c /Users/me/my/game_engine/gameEngine/src/component/collider/collision_detector.cpp

gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/collision_detector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/gameEngine.dir/src/component/collider/collision_detector.cpp.i"
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/me/my/game_engine/gameEngine/src/component/collider/collision_detector.cpp > CMakeFiles/gameEngine.dir/src/component/collider/collision_detector.cpp.i

gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/collision_detector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/gameEngine.dir/src/component/collider/collision_detector.cpp.s"
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/me/my/game_engine/gameEngine/src/component/collider/collision_detector.cpp -o CMakeFiles/gameEngine.dir/src/component/collider/collision_detector.cpp.s

gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/ellipse_collider_component.cpp.o: gameEngineBuild/CMakeFiles/gameEngine.dir/flags.make
gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/ellipse_collider_component.cpp.o: /Users/me/my/game_engine/gameEngine/src/component/collider/ellipse_collider_component.cpp
gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/ellipse_collider_component.cpp.o: gameEngineBuild/CMakeFiles/gameEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/me/my/game_engine/game/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/ellipse_collider_component.cpp.o"
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/ellipse_collider_component.cpp.o -MF CMakeFiles/gameEngine.dir/src/component/collider/ellipse_collider_component.cpp.o.d -o CMakeFiles/gameEngine.dir/src/component/collider/ellipse_collider_component.cpp.o -c /Users/me/my/game_engine/gameEngine/src/component/collider/ellipse_collider_component.cpp

gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/ellipse_collider_component.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/gameEngine.dir/src/component/collider/ellipse_collider_component.cpp.i"
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/me/my/game_engine/gameEngine/src/component/collider/ellipse_collider_component.cpp > CMakeFiles/gameEngine.dir/src/component/collider/ellipse_collider_component.cpp.i

gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/ellipse_collider_component.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/gameEngine.dir/src/component/collider/ellipse_collider_component.cpp.s"
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/me/my/game_engine/gameEngine/src/component/collider/ellipse_collider_component.cpp -o CMakeFiles/gameEngine.dir/src/component/collider/ellipse_collider_component.cpp.s

# Object files for target gameEngine
gameEngine_OBJECTS = \
"CMakeFiles/gameEngine.dir/src/engine.cpp.o" \
"CMakeFiles/gameEngine.dir/src/inputs.cpp.o" \
"CMakeFiles/gameEngine.dir/src/options.cpp.o" \
"CMakeFiles/gameEngine.dir/src/texture_manager.cpp.o" \
"CMakeFiles/gameEngine.dir/src/component/collider/rectangle_colider_component.cpp.o" \
"CMakeFiles/gameEngine.dir/src/component/collider/collision_detector.cpp.o" \
"CMakeFiles/gameEngine.dir/src/component/collider/ellipse_collider_component.cpp.o"

# External object files for target gameEngine
gameEngine_EXTERNAL_OBJECTS =

gameEngineBuild/libgameEngine.a: gameEngineBuild/CMakeFiles/gameEngine.dir/src/engine.cpp.o
gameEngineBuild/libgameEngine.a: gameEngineBuild/CMakeFiles/gameEngine.dir/src/inputs.cpp.o
gameEngineBuild/libgameEngine.a: gameEngineBuild/CMakeFiles/gameEngine.dir/src/options.cpp.o
gameEngineBuild/libgameEngine.a: gameEngineBuild/CMakeFiles/gameEngine.dir/src/texture_manager.cpp.o
gameEngineBuild/libgameEngine.a: gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/rectangle_colider_component.cpp.o
gameEngineBuild/libgameEngine.a: gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/collision_detector.cpp.o
gameEngineBuild/libgameEngine.a: gameEngineBuild/CMakeFiles/gameEngine.dir/src/component/collider/ellipse_collider_component.cpp.o
gameEngineBuild/libgameEngine.a: gameEngineBuild/CMakeFiles/gameEngine.dir/build.make
gameEngineBuild/libgameEngine.a: gameEngineBuild/CMakeFiles/gameEngine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/me/my/game_engine/game/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX static library libgameEngine.a"
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && $(CMAKE_COMMAND) -P CMakeFiles/gameEngine.dir/cmake_clean_target.cmake
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gameEngine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
gameEngineBuild/CMakeFiles/gameEngine.dir/build: gameEngineBuild/libgameEngine.a
.PHONY : gameEngineBuild/CMakeFiles/gameEngine.dir/build

gameEngineBuild/CMakeFiles/gameEngine.dir/clean:
	cd /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild && $(CMAKE_COMMAND) -P CMakeFiles/gameEngine.dir/cmake_clean.cmake
.PHONY : gameEngineBuild/CMakeFiles/gameEngine.dir/clean

gameEngineBuild/CMakeFiles/gameEngine.dir/depend:
	cd /Users/me/my/game_engine/game/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/me/my/game_engine/game /Users/me/my/game_engine/gameEngine /Users/me/my/game_engine/game/cmake-build-debug /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild /Users/me/my/game_engine/game/cmake-build-debug/gameEngineBuild/CMakeFiles/gameEngine.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : gameEngineBuild/CMakeFiles/gameEngine.dir/depend

