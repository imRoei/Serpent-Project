# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\roeig\CodingFolder\Serpent Project"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\roeig\CodingFolder\Serpent Project\build"

# Include any dependencies generated for this target.
include CMakeFiles/MyGTKApp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MyGTKApp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyGTKApp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyGTKApp.dir/flags.make

CMakeFiles/MyGTKApp.dir/src/main.c.obj: CMakeFiles/MyGTKApp.dir/flags.make
CMakeFiles/MyGTKApp.dir/src/main.c.obj: CMakeFiles/MyGTKApp.dir/includes_C.rsp
CMakeFiles/MyGTKApp.dir/src/main.c.obj: C:/Users/roeig/CodingFolder/Serpent\ Project/src/main.c
CMakeFiles/MyGTKApp.dir/src/main.c.obj: CMakeFiles/MyGTKApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\roeig\CodingFolder\Serpent Project\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/MyGTKApp.dir/src/main.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MyGTKApp.dir/src/main.c.obj -MF CMakeFiles\MyGTKApp.dir\src\main.c.obj.d -o CMakeFiles\MyGTKApp.dir\src\main.c.obj -c "C:\Users\roeig\CodingFolder\Serpent Project\src\main.c"

CMakeFiles/MyGTKApp.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/MyGTKApp.dir/src/main.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\roeig\CodingFolder\Serpent Project\src\main.c" > CMakeFiles\MyGTKApp.dir\src\main.c.i

CMakeFiles/MyGTKApp.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/MyGTKApp.dir/src/main.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\roeig\CodingFolder\Serpent Project\src\main.c" -o CMakeFiles\MyGTKApp.dir\src\main.c.s

CMakeFiles/MyGTKApp.dir/src/gui.c.obj: CMakeFiles/MyGTKApp.dir/flags.make
CMakeFiles/MyGTKApp.dir/src/gui.c.obj: CMakeFiles/MyGTKApp.dir/includes_C.rsp
CMakeFiles/MyGTKApp.dir/src/gui.c.obj: C:/Users/roeig/CodingFolder/Serpent\ Project/src/gui.c
CMakeFiles/MyGTKApp.dir/src/gui.c.obj: CMakeFiles/MyGTKApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\roeig\CodingFolder\Serpent Project\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/MyGTKApp.dir/src/gui.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MyGTKApp.dir/src/gui.c.obj -MF CMakeFiles\MyGTKApp.dir\src\gui.c.obj.d -o CMakeFiles\MyGTKApp.dir\src\gui.c.obj -c "C:\Users\roeig\CodingFolder\Serpent Project\src\gui.c"

CMakeFiles/MyGTKApp.dir/src/gui.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/MyGTKApp.dir/src/gui.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\roeig\CodingFolder\Serpent Project\src\gui.c" > CMakeFiles\MyGTKApp.dir\src\gui.c.i

CMakeFiles/MyGTKApp.dir/src/gui.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/MyGTKApp.dir/src/gui.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\roeig\CodingFolder\Serpent Project\src\gui.c" -o CMakeFiles\MyGTKApp.dir\src\gui.c.s

# Object files for target MyGTKApp
MyGTKApp_OBJECTS = \
"CMakeFiles/MyGTKApp.dir/src/main.c.obj" \
"CMakeFiles/MyGTKApp.dir/src/gui.c.obj"

# External object files for target MyGTKApp
MyGTKApp_EXTERNAL_OBJECTS =

MyGTKApp.exe: CMakeFiles/MyGTKApp.dir/src/main.c.obj
MyGTKApp.exe: CMakeFiles/MyGTKApp.dir/src/gui.c.obj
MyGTKApp.exe: CMakeFiles/MyGTKApp.dir/build.make
MyGTKApp.exe: CMakeFiles/MyGTKApp.dir/linkLibs.rsp
MyGTKApp.exe: CMakeFiles/MyGTKApp.dir/objects1.rsp
MyGTKApp.exe: CMakeFiles/MyGTKApp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="C:\Users\roeig\CodingFolder\Serpent Project\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable MyGTKApp.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\MyGTKApp.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyGTKApp.dir/build: MyGTKApp.exe
.PHONY : CMakeFiles/MyGTKApp.dir/build

CMakeFiles/MyGTKApp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\MyGTKApp.dir\cmake_clean.cmake
.PHONY : CMakeFiles/MyGTKApp.dir/clean

CMakeFiles/MyGTKApp.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\roeig\CodingFolder\Serpent Project" "C:\Users\roeig\CodingFolder\Serpent Project" "C:\Users\roeig\CodingFolder\Serpent Project\build" "C:\Users\roeig\CodingFolder\Serpent Project\build" "C:\Users\roeig\CodingFolder\Serpent Project\build\CMakeFiles\MyGTKApp.dir\DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/MyGTKApp.dir/depend
