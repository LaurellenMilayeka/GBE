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
CMAKE_SOURCE_DIR = "/mnt/c/Users/Flox Ajuro/GBE"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/Flox Ajuro/GBE/build"

# Include any dependencies generated for this target.
include CMakeFiles/GameBoy_Emulator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/GameBoy_Emulator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GameBoy_Emulator.dir/flags.make

CMakeFiles/GameBoy_Emulator.dir/src/OpCodes.cpp.o: CMakeFiles/GameBoy_Emulator.dir/flags.make
CMakeFiles/GameBoy_Emulator.dir/src/OpCodes.cpp.o: ../src/OpCodes.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Flox Ajuro/GBE/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GameBoy_Emulator.dir/src/OpCodes.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GameBoy_Emulator.dir/src/OpCodes.cpp.o -c "/mnt/c/Users/Flox Ajuro/GBE/src/OpCodes.cpp"

CMakeFiles/GameBoy_Emulator.dir/src/OpCodes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GameBoy_Emulator.dir/src/OpCodes.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Flox Ajuro/GBE/src/OpCodes.cpp" > CMakeFiles/GameBoy_Emulator.dir/src/OpCodes.cpp.i

CMakeFiles/GameBoy_Emulator.dir/src/OpCodes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GameBoy_Emulator.dir/src/OpCodes.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Flox Ajuro/GBE/src/OpCodes.cpp" -o CMakeFiles/GameBoy_Emulator.dir/src/OpCodes.cpp.s

CMakeFiles/GameBoy_Emulator.dir/src/OpCodes.cpp.o.requires:

.PHONY : CMakeFiles/GameBoy_Emulator.dir/src/OpCodes.cpp.o.requires

CMakeFiles/GameBoy_Emulator.dir/src/OpCodes.cpp.o.provides: CMakeFiles/GameBoy_Emulator.dir/src/OpCodes.cpp.o.requires
	$(MAKE) -f CMakeFiles/GameBoy_Emulator.dir/build.make CMakeFiles/GameBoy_Emulator.dir/src/OpCodes.cpp.o.provides.build
.PHONY : CMakeFiles/GameBoy_Emulator.dir/src/OpCodes.cpp.o.provides

CMakeFiles/GameBoy_Emulator.dir/src/OpCodes.cpp.o.provides.build: CMakeFiles/GameBoy_Emulator.dir/src/OpCodes.cpp.o


CMakeFiles/GameBoy_Emulator.dir/main.cpp.o: CMakeFiles/GameBoy_Emulator.dir/flags.make
CMakeFiles/GameBoy_Emulator.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Flox Ajuro/GBE/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/GameBoy_Emulator.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GameBoy_Emulator.dir/main.cpp.o -c "/mnt/c/Users/Flox Ajuro/GBE/main.cpp"

CMakeFiles/GameBoy_Emulator.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GameBoy_Emulator.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Flox Ajuro/GBE/main.cpp" > CMakeFiles/GameBoy_Emulator.dir/main.cpp.i

CMakeFiles/GameBoy_Emulator.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GameBoy_Emulator.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Flox Ajuro/GBE/main.cpp" -o CMakeFiles/GameBoy_Emulator.dir/main.cpp.s

CMakeFiles/GameBoy_Emulator.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/GameBoy_Emulator.dir/main.cpp.o.requires

CMakeFiles/GameBoy_Emulator.dir/main.cpp.o.provides: CMakeFiles/GameBoy_Emulator.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/GameBoy_Emulator.dir/build.make CMakeFiles/GameBoy_Emulator.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/GameBoy_Emulator.dir/main.cpp.o.provides

CMakeFiles/GameBoy_Emulator.dir/main.cpp.o.provides.build: CMakeFiles/GameBoy_Emulator.dir/main.cpp.o


CMakeFiles/GameBoy_Emulator.dir/src/RAM.cpp.o: CMakeFiles/GameBoy_Emulator.dir/flags.make
CMakeFiles/GameBoy_Emulator.dir/src/RAM.cpp.o: ../src/RAM.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Flox Ajuro/GBE/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/GameBoy_Emulator.dir/src/RAM.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GameBoy_Emulator.dir/src/RAM.cpp.o -c "/mnt/c/Users/Flox Ajuro/GBE/src/RAM.cpp"

CMakeFiles/GameBoy_Emulator.dir/src/RAM.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GameBoy_Emulator.dir/src/RAM.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Flox Ajuro/GBE/src/RAM.cpp" > CMakeFiles/GameBoy_Emulator.dir/src/RAM.cpp.i

CMakeFiles/GameBoy_Emulator.dir/src/RAM.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GameBoy_Emulator.dir/src/RAM.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Flox Ajuro/GBE/src/RAM.cpp" -o CMakeFiles/GameBoy_Emulator.dir/src/RAM.cpp.s

CMakeFiles/GameBoy_Emulator.dir/src/RAM.cpp.o.requires:

.PHONY : CMakeFiles/GameBoy_Emulator.dir/src/RAM.cpp.o.requires

CMakeFiles/GameBoy_Emulator.dir/src/RAM.cpp.o.provides: CMakeFiles/GameBoy_Emulator.dir/src/RAM.cpp.o.requires
	$(MAKE) -f CMakeFiles/GameBoy_Emulator.dir/build.make CMakeFiles/GameBoy_Emulator.dir/src/RAM.cpp.o.provides.build
.PHONY : CMakeFiles/GameBoy_Emulator.dir/src/RAM.cpp.o.provides

CMakeFiles/GameBoy_Emulator.dir/src/RAM.cpp.o.provides.build: CMakeFiles/GameBoy_Emulator.dir/src/RAM.cpp.o


CMakeFiles/GameBoy_Emulator.dir/src/ROM.cpp.o: CMakeFiles/GameBoy_Emulator.dir/flags.make
CMakeFiles/GameBoy_Emulator.dir/src/ROM.cpp.o: ../src/ROM.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Flox Ajuro/GBE/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/GameBoy_Emulator.dir/src/ROM.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GameBoy_Emulator.dir/src/ROM.cpp.o -c "/mnt/c/Users/Flox Ajuro/GBE/src/ROM.cpp"

CMakeFiles/GameBoy_Emulator.dir/src/ROM.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GameBoy_Emulator.dir/src/ROM.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Flox Ajuro/GBE/src/ROM.cpp" > CMakeFiles/GameBoy_Emulator.dir/src/ROM.cpp.i

CMakeFiles/GameBoy_Emulator.dir/src/ROM.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GameBoy_Emulator.dir/src/ROM.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Flox Ajuro/GBE/src/ROM.cpp" -o CMakeFiles/GameBoy_Emulator.dir/src/ROM.cpp.s

CMakeFiles/GameBoy_Emulator.dir/src/ROM.cpp.o.requires:

.PHONY : CMakeFiles/GameBoy_Emulator.dir/src/ROM.cpp.o.requires

CMakeFiles/GameBoy_Emulator.dir/src/ROM.cpp.o.provides: CMakeFiles/GameBoy_Emulator.dir/src/ROM.cpp.o.requires
	$(MAKE) -f CMakeFiles/GameBoy_Emulator.dir/build.make CMakeFiles/GameBoy_Emulator.dir/src/ROM.cpp.o.provides.build
.PHONY : CMakeFiles/GameBoy_Emulator.dir/src/ROM.cpp.o.provides

CMakeFiles/GameBoy_Emulator.dir/src/ROM.cpp.o.provides.build: CMakeFiles/GameBoy_Emulator.dir/src/ROM.cpp.o


CMakeFiles/GameBoy_Emulator.dir/src/Loader.cpp.o: CMakeFiles/GameBoy_Emulator.dir/flags.make
CMakeFiles/GameBoy_Emulator.dir/src/Loader.cpp.o: ../src/Loader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Flox Ajuro/GBE/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/GameBoy_Emulator.dir/src/Loader.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GameBoy_Emulator.dir/src/Loader.cpp.o -c "/mnt/c/Users/Flox Ajuro/GBE/src/Loader.cpp"

CMakeFiles/GameBoy_Emulator.dir/src/Loader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GameBoy_Emulator.dir/src/Loader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Flox Ajuro/GBE/src/Loader.cpp" > CMakeFiles/GameBoy_Emulator.dir/src/Loader.cpp.i

CMakeFiles/GameBoy_Emulator.dir/src/Loader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GameBoy_Emulator.dir/src/Loader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Flox Ajuro/GBE/src/Loader.cpp" -o CMakeFiles/GameBoy_Emulator.dir/src/Loader.cpp.s

CMakeFiles/GameBoy_Emulator.dir/src/Loader.cpp.o.requires:

.PHONY : CMakeFiles/GameBoy_Emulator.dir/src/Loader.cpp.o.requires

CMakeFiles/GameBoy_Emulator.dir/src/Loader.cpp.o.provides: CMakeFiles/GameBoy_Emulator.dir/src/Loader.cpp.o.requires
	$(MAKE) -f CMakeFiles/GameBoy_Emulator.dir/build.make CMakeFiles/GameBoy_Emulator.dir/src/Loader.cpp.o.provides.build
.PHONY : CMakeFiles/GameBoy_Emulator.dir/src/Loader.cpp.o.provides

CMakeFiles/GameBoy_Emulator.dir/src/Loader.cpp.o.provides.build: CMakeFiles/GameBoy_Emulator.dir/src/Loader.cpp.o


CMakeFiles/GameBoy_Emulator.dir/src/Debug.cpp.o: CMakeFiles/GameBoy_Emulator.dir/flags.make
CMakeFiles/GameBoy_Emulator.dir/src/Debug.cpp.o: ../src/Debug.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Flox Ajuro/GBE/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/GameBoy_Emulator.dir/src/Debug.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GameBoy_Emulator.dir/src/Debug.cpp.o -c "/mnt/c/Users/Flox Ajuro/GBE/src/Debug.cpp"

CMakeFiles/GameBoy_Emulator.dir/src/Debug.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GameBoy_Emulator.dir/src/Debug.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Flox Ajuro/GBE/src/Debug.cpp" > CMakeFiles/GameBoy_Emulator.dir/src/Debug.cpp.i

CMakeFiles/GameBoy_Emulator.dir/src/Debug.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GameBoy_Emulator.dir/src/Debug.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Flox Ajuro/GBE/src/Debug.cpp" -o CMakeFiles/GameBoy_Emulator.dir/src/Debug.cpp.s

CMakeFiles/GameBoy_Emulator.dir/src/Debug.cpp.o.requires:

.PHONY : CMakeFiles/GameBoy_Emulator.dir/src/Debug.cpp.o.requires

CMakeFiles/GameBoy_Emulator.dir/src/Debug.cpp.o.provides: CMakeFiles/GameBoy_Emulator.dir/src/Debug.cpp.o.requires
	$(MAKE) -f CMakeFiles/GameBoy_Emulator.dir/build.make CMakeFiles/GameBoy_Emulator.dir/src/Debug.cpp.o.provides.build
.PHONY : CMakeFiles/GameBoy_Emulator.dir/src/Debug.cpp.o.provides

CMakeFiles/GameBoy_Emulator.dir/src/Debug.cpp.o.provides.build: CMakeFiles/GameBoy_Emulator.dir/src/Debug.cpp.o


CMakeFiles/GameBoy_Emulator.dir/src/CPU.cpp.o: CMakeFiles/GameBoy_Emulator.dir/flags.make
CMakeFiles/GameBoy_Emulator.dir/src/CPU.cpp.o: ../src/CPU.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Flox Ajuro/GBE/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/GameBoy_Emulator.dir/src/CPU.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GameBoy_Emulator.dir/src/CPU.cpp.o -c "/mnt/c/Users/Flox Ajuro/GBE/src/CPU.cpp"

CMakeFiles/GameBoy_Emulator.dir/src/CPU.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GameBoy_Emulator.dir/src/CPU.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Flox Ajuro/GBE/src/CPU.cpp" > CMakeFiles/GameBoy_Emulator.dir/src/CPU.cpp.i

CMakeFiles/GameBoy_Emulator.dir/src/CPU.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GameBoy_Emulator.dir/src/CPU.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Flox Ajuro/GBE/src/CPU.cpp" -o CMakeFiles/GameBoy_Emulator.dir/src/CPU.cpp.s

CMakeFiles/GameBoy_Emulator.dir/src/CPU.cpp.o.requires:

.PHONY : CMakeFiles/GameBoy_Emulator.dir/src/CPU.cpp.o.requires

CMakeFiles/GameBoy_Emulator.dir/src/CPU.cpp.o.provides: CMakeFiles/GameBoy_Emulator.dir/src/CPU.cpp.o.requires
	$(MAKE) -f CMakeFiles/GameBoy_Emulator.dir/build.make CMakeFiles/GameBoy_Emulator.dir/src/CPU.cpp.o.provides.build
.PHONY : CMakeFiles/GameBoy_Emulator.dir/src/CPU.cpp.o.provides

CMakeFiles/GameBoy_Emulator.dir/src/CPU.cpp.o.provides.build: CMakeFiles/GameBoy_Emulator.dir/src/CPU.cpp.o


CMakeFiles/GameBoy_Emulator.dir/src/Disasm.cpp.o: CMakeFiles/GameBoy_Emulator.dir/flags.make
CMakeFiles/GameBoy_Emulator.dir/src/Disasm.cpp.o: ../src/Disasm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Flox Ajuro/GBE/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/GameBoy_Emulator.dir/src/Disasm.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GameBoy_Emulator.dir/src/Disasm.cpp.o -c "/mnt/c/Users/Flox Ajuro/GBE/src/Disasm.cpp"

CMakeFiles/GameBoy_Emulator.dir/src/Disasm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GameBoy_Emulator.dir/src/Disasm.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Flox Ajuro/GBE/src/Disasm.cpp" > CMakeFiles/GameBoy_Emulator.dir/src/Disasm.cpp.i

CMakeFiles/GameBoy_Emulator.dir/src/Disasm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GameBoy_Emulator.dir/src/Disasm.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Flox Ajuro/GBE/src/Disasm.cpp" -o CMakeFiles/GameBoy_Emulator.dir/src/Disasm.cpp.s

CMakeFiles/GameBoy_Emulator.dir/src/Disasm.cpp.o.requires:

.PHONY : CMakeFiles/GameBoy_Emulator.dir/src/Disasm.cpp.o.requires

CMakeFiles/GameBoy_Emulator.dir/src/Disasm.cpp.o.provides: CMakeFiles/GameBoy_Emulator.dir/src/Disasm.cpp.o.requires
	$(MAKE) -f CMakeFiles/GameBoy_Emulator.dir/build.make CMakeFiles/GameBoy_Emulator.dir/src/Disasm.cpp.o.provides.build
.PHONY : CMakeFiles/GameBoy_Emulator.dir/src/Disasm.cpp.o.provides

CMakeFiles/GameBoy_Emulator.dir/src/Disasm.cpp.o.provides.build: CMakeFiles/GameBoy_Emulator.dir/src/Disasm.cpp.o


CMakeFiles/GameBoy_Emulator.dir/src/GPU.cpp.o: CMakeFiles/GameBoy_Emulator.dir/flags.make
CMakeFiles/GameBoy_Emulator.dir/src/GPU.cpp.o: ../src/GPU.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Flox Ajuro/GBE/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/GameBoy_Emulator.dir/src/GPU.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GameBoy_Emulator.dir/src/GPU.cpp.o -c "/mnt/c/Users/Flox Ajuro/GBE/src/GPU.cpp"

CMakeFiles/GameBoy_Emulator.dir/src/GPU.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GameBoy_Emulator.dir/src/GPU.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Flox Ajuro/GBE/src/GPU.cpp" > CMakeFiles/GameBoy_Emulator.dir/src/GPU.cpp.i

CMakeFiles/GameBoy_Emulator.dir/src/GPU.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GameBoy_Emulator.dir/src/GPU.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Flox Ajuro/GBE/src/GPU.cpp" -o CMakeFiles/GameBoy_Emulator.dir/src/GPU.cpp.s

CMakeFiles/GameBoy_Emulator.dir/src/GPU.cpp.o.requires:

.PHONY : CMakeFiles/GameBoy_Emulator.dir/src/GPU.cpp.o.requires

CMakeFiles/GameBoy_Emulator.dir/src/GPU.cpp.o.provides: CMakeFiles/GameBoy_Emulator.dir/src/GPU.cpp.o.requires
	$(MAKE) -f CMakeFiles/GameBoy_Emulator.dir/build.make CMakeFiles/GameBoy_Emulator.dir/src/GPU.cpp.o.provides.build
.PHONY : CMakeFiles/GameBoy_Emulator.dir/src/GPU.cpp.o.provides

CMakeFiles/GameBoy_Emulator.dir/src/GPU.cpp.o.provides.build: CMakeFiles/GameBoy_Emulator.dir/src/GPU.cpp.o


CMakeFiles/GameBoy_Emulator.dir/src/Display.cpp.o: CMakeFiles/GameBoy_Emulator.dir/flags.make
CMakeFiles/GameBoy_Emulator.dir/src/Display.cpp.o: ../src/Display.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Flox Ajuro/GBE/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/GameBoy_Emulator.dir/src/Display.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GameBoy_Emulator.dir/src/Display.cpp.o -c "/mnt/c/Users/Flox Ajuro/GBE/src/Display.cpp"

CMakeFiles/GameBoy_Emulator.dir/src/Display.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GameBoy_Emulator.dir/src/Display.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Flox Ajuro/GBE/src/Display.cpp" > CMakeFiles/GameBoy_Emulator.dir/src/Display.cpp.i

CMakeFiles/GameBoy_Emulator.dir/src/Display.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GameBoy_Emulator.dir/src/Display.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Flox Ajuro/GBE/src/Display.cpp" -o CMakeFiles/GameBoy_Emulator.dir/src/Display.cpp.s

CMakeFiles/GameBoy_Emulator.dir/src/Display.cpp.o.requires:

.PHONY : CMakeFiles/GameBoy_Emulator.dir/src/Display.cpp.o.requires

CMakeFiles/GameBoy_Emulator.dir/src/Display.cpp.o.provides: CMakeFiles/GameBoy_Emulator.dir/src/Display.cpp.o.requires
	$(MAKE) -f CMakeFiles/GameBoy_Emulator.dir/build.make CMakeFiles/GameBoy_Emulator.dir/src/Display.cpp.o.provides.build
.PHONY : CMakeFiles/GameBoy_Emulator.dir/src/Display.cpp.o.provides

CMakeFiles/GameBoy_Emulator.dir/src/Display.cpp.o.provides.build: CMakeFiles/GameBoy_Emulator.dir/src/Display.cpp.o


CMakeFiles/GameBoy_Emulator.dir/src/Input.cpp.o: CMakeFiles/GameBoy_Emulator.dir/flags.make
CMakeFiles/GameBoy_Emulator.dir/src/Input.cpp.o: ../src/Input.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Flox Ajuro/GBE/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/GameBoy_Emulator.dir/src/Input.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GameBoy_Emulator.dir/src/Input.cpp.o -c "/mnt/c/Users/Flox Ajuro/GBE/src/Input.cpp"

CMakeFiles/GameBoy_Emulator.dir/src/Input.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GameBoy_Emulator.dir/src/Input.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Flox Ajuro/GBE/src/Input.cpp" > CMakeFiles/GameBoy_Emulator.dir/src/Input.cpp.i

CMakeFiles/GameBoy_Emulator.dir/src/Input.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GameBoy_Emulator.dir/src/Input.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Flox Ajuro/GBE/src/Input.cpp" -o CMakeFiles/GameBoy_Emulator.dir/src/Input.cpp.s

CMakeFiles/GameBoy_Emulator.dir/src/Input.cpp.o.requires:

.PHONY : CMakeFiles/GameBoy_Emulator.dir/src/Input.cpp.o.requires

CMakeFiles/GameBoy_Emulator.dir/src/Input.cpp.o.provides: CMakeFiles/GameBoy_Emulator.dir/src/Input.cpp.o.requires
	$(MAKE) -f CMakeFiles/GameBoy_Emulator.dir/build.make CMakeFiles/GameBoy_Emulator.dir/src/Input.cpp.o.provides.build
.PHONY : CMakeFiles/GameBoy_Emulator.dir/src/Input.cpp.o.provides

CMakeFiles/GameBoy_Emulator.dir/src/Input.cpp.o.provides.build: CMakeFiles/GameBoy_Emulator.dir/src/Input.cpp.o


CMakeFiles/GameBoy_Emulator.dir/src/Audio.cpp.o: CMakeFiles/GameBoy_Emulator.dir/flags.make
CMakeFiles/GameBoy_Emulator.dir/src/Audio.cpp.o: ../src/Audio.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Flox Ajuro/GBE/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/GameBoy_Emulator.dir/src/Audio.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GameBoy_Emulator.dir/src/Audio.cpp.o -c "/mnt/c/Users/Flox Ajuro/GBE/src/Audio.cpp"

CMakeFiles/GameBoy_Emulator.dir/src/Audio.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GameBoy_Emulator.dir/src/Audio.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Flox Ajuro/GBE/src/Audio.cpp" > CMakeFiles/GameBoy_Emulator.dir/src/Audio.cpp.i

CMakeFiles/GameBoy_Emulator.dir/src/Audio.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GameBoy_Emulator.dir/src/Audio.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Flox Ajuro/GBE/src/Audio.cpp" -o CMakeFiles/GameBoy_Emulator.dir/src/Audio.cpp.s

CMakeFiles/GameBoy_Emulator.dir/src/Audio.cpp.o.requires:

.PHONY : CMakeFiles/GameBoy_Emulator.dir/src/Audio.cpp.o.requires

CMakeFiles/GameBoy_Emulator.dir/src/Audio.cpp.o.provides: CMakeFiles/GameBoy_Emulator.dir/src/Audio.cpp.o.requires
	$(MAKE) -f CMakeFiles/GameBoy_Emulator.dir/build.make CMakeFiles/GameBoy_Emulator.dir/src/Audio.cpp.o.provides.build
.PHONY : CMakeFiles/GameBoy_Emulator.dir/src/Audio.cpp.o.provides

CMakeFiles/GameBoy_Emulator.dir/src/Audio.cpp.o.provides.build: CMakeFiles/GameBoy_Emulator.dir/src/Audio.cpp.o


CMakeFiles/GameBoy_Emulator.dir/gb_apu/Blip_Buffer.cpp.o: CMakeFiles/GameBoy_Emulator.dir/flags.make
CMakeFiles/GameBoy_Emulator.dir/gb_apu/Blip_Buffer.cpp.o: ../gb_apu/Blip_Buffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Flox Ajuro/GBE/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/GameBoy_Emulator.dir/gb_apu/Blip_Buffer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GameBoy_Emulator.dir/gb_apu/Blip_Buffer.cpp.o -c "/mnt/c/Users/Flox Ajuro/GBE/gb_apu/Blip_Buffer.cpp"

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Blip_Buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GameBoy_Emulator.dir/gb_apu/Blip_Buffer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Flox Ajuro/GBE/gb_apu/Blip_Buffer.cpp" > CMakeFiles/GameBoy_Emulator.dir/gb_apu/Blip_Buffer.cpp.i

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Blip_Buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GameBoy_Emulator.dir/gb_apu/Blip_Buffer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Flox Ajuro/GBE/gb_apu/Blip_Buffer.cpp" -o CMakeFiles/GameBoy_Emulator.dir/gb_apu/Blip_Buffer.cpp.s

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Blip_Buffer.cpp.o.requires:

.PHONY : CMakeFiles/GameBoy_Emulator.dir/gb_apu/Blip_Buffer.cpp.o.requires

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Blip_Buffer.cpp.o.provides: CMakeFiles/GameBoy_Emulator.dir/gb_apu/Blip_Buffer.cpp.o.requires
	$(MAKE) -f CMakeFiles/GameBoy_Emulator.dir/build.make CMakeFiles/GameBoy_Emulator.dir/gb_apu/Blip_Buffer.cpp.o.provides.build
.PHONY : CMakeFiles/GameBoy_Emulator.dir/gb_apu/Blip_Buffer.cpp.o.provides

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Blip_Buffer.cpp.o.provides.build: CMakeFiles/GameBoy_Emulator.dir/gb_apu/Blip_Buffer.cpp.o


CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Apu.cpp.o: CMakeFiles/GameBoy_Emulator.dir/flags.make
CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Apu.cpp.o: ../gb_apu/Gb_Apu.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Flox Ajuro/GBE/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Apu.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Apu.cpp.o -c "/mnt/c/Users/Flox Ajuro/GBE/gb_apu/Gb_Apu.cpp"

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Apu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Apu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Flox Ajuro/GBE/gb_apu/Gb_Apu.cpp" > CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Apu.cpp.i

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Apu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Apu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Flox Ajuro/GBE/gb_apu/Gb_Apu.cpp" -o CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Apu.cpp.s

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Apu.cpp.o.requires:

.PHONY : CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Apu.cpp.o.requires

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Apu.cpp.o.provides: CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Apu.cpp.o.requires
	$(MAKE) -f CMakeFiles/GameBoy_Emulator.dir/build.make CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Apu.cpp.o.provides.build
.PHONY : CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Apu.cpp.o.provides

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Apu.cpp.o.provides.build: CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Apu.cpp.o


CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Oscs.cpp.o: CMakeFiles/GameBoy_Emulator.dir/flags.make
CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Oscs.cpp.o: ../gb_apu/Gb_Oscs.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Flox Ajuro/GBE/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Oscs.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Oscs.cpp.o -c "/mnt/c/Users/Flox Ajuro/GBE/gb_apu/Gb_Oscs.cpp"

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Oscs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Oscs.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Flox Ajuro/GBE/gb_apu/Gb_Oscs.cpp" > CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Oscs.cpp.i

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Oscs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Oscs.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Flox Ajuro/GBE/gb_apu/Gb_Oscs.cpp" -o CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Oscs.cpp.s

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Oscs.cpp.o.requires:

.PHONY : CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Oscs.cpp.o.requires

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Oscs.cpp.o.provides: CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Oscs.cpp.o.requires
	$(MAKE) -f CMakeFiles/GameBoy_Emulator.dir/build.make CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Oscs.cpp.o.provides.build
.PHONY : CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Oscs.cpp.o.provides

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Oscs.cpp.o.provides.build: CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Oscs.cpp.o


CMakeFiles/GameBoy_Emulator.dir/gb_apu/Multi_Buffer.cpp.o: CMakeFiles/GameBoy_Emulator.dir/flags.make
CMakeFiles/GameBoy_Emulator.dir/gb_apu/Multi_Buffer.cpp.o: ../gb_apu/Multi_Buffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Flox Ajuro/GBE/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/GameBoy_Emulator.dir/gb_apu/Multi_Buffer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GameBoy_Emulator.dir/gb_apu/Multi_Buffer.cpp.o -c "/mnt/c/Users/Flox Ajuro/GBE/gb_apu/Multi_Buffer.cpp"

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Multi_Buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GameBoy_Emulator.dir/gb_apu/Multi_Buffer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Flox Ajuro/GBE/gb_apu/Multi_Buffer.cpp" > CMakeFiles/GameBoy_Emulator.dir/gb_apu/Multi_Buffer.cpp.i

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Multi_Buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GameBoy_Emulator.dir/gb_apu/Multi_Buffer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Flox Ajuro/GBE/gb_apu/Multi_Buffer.cpp" -o CMakeFiles/GameBoy_Emulator.dir/gb_apu/Multi_Buffer.cpp.s

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Multi_Buffer.cpp.o.requires:

.PHONY : CMakeFiles/GameBoy_Emulator.dir/gb_apu/Multi_Buffer.cpp.o.requires

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Multi_Buffer.cpp.o.provides: CMakeFiles/GameBoy_Emulator.dir/gb_apu/Multi_Buffer.cpp.o.requires
	$(MAKE) -f CMakeFiles/GameBoy_Emulator.dir/build.make CMakeFiles/GameBoy_Emulator.dir/gb_apu/Multi_Buffer.cpp.o.provides.build
.PHONY : CMakeFiles/GameBoy_Emulator.dir/gb_apu/Multi_Buffer.cpp.o.provides

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Multi_Buffer.cpp.o.provides.build: CMakeFiles/GameBoy_Emulator.dir/gb_apu/Multi_Buffer.cpp.o


CMakeFiles/GameBoy_Emulator.dir/gb_apu/Sound_Queue.cpp.o: CMakeFiles/GameBoy_Emulator.dir/flags.make
CMakeFiles/GameBoy_Emulator.dir/gb_apu/Sound_Queue.cpp.o: ../gb_apu/Sound_Queue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Flox Ajuro/GBE/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/GameBoy_Emulator.dir/gb_apu/Sound_Queue.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GameBoy_Emulator.dir/gb_apu/Sound_Queue.cpp.o -c "/mnt/c/Users/Flox Ajuro/GBE/gb_apu/Sound_Queue.cpp"

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Sound_Queue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GameBoy_Emulator.dir/gb_apu/Sound_Queue.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Flox Ajuro/GBE/gb_apu/Sound_Queue.cpp" > CMakeFiles/GameBoy_Emulator.dir/gb_apu/Sound_Queue.cpp.i

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Sound_Queue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GameBoy_Emulator.dir/gb_apu/Sound_Queue.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Flox Ajuro/GBE/gb_apu/Sound_Queue.cpp" -o CMakeFiles/GameBoy_Emulator.dir/gb_apu/Sound_Queue.cpp.s

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Sound_Queue.cpp.o.requires:

.PHONY : CMakeFiles/GameBoy_Emulator.dir/gb_apu/Sound_Queue.cpp.o.requires

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Sound_Queue.cpp.o.provides: CMakeFiles/GameBoy_Emulator.dir/gb_apu/Sound_Queue.cpp.o.requires
	$(MAKE) -f CMakeFiles/GameBoy_Emulator.dir/build.make CMakeFiles/GameBoy_Emulator.dir/gb_apu/Sound_Queue.cpp.o.provides.build
.PHONY : CMakeFiles/GameBoy_Emulator.dir/gb_apu/Sound_Queue.cpp.o.provides

CMakeFiles/GameBoy_Emulator.dir/gb_apu/Sound_Queue.cpp.o.provides.build: CMakeFiles/GameBoy_Emulator.dir/gb_apu/Sound_Queue.cpp.o


# Object files for target GameBoy_Emulator
GameBoy_Emulator_OBJECTS = \
"CMakeFiles/GameBoy_Emulator.dir/src/OpCodes.cpp.o" \
"CMakeFiles/GameBoy_Emulator.dir/main.cpp.o" \
"CMakeFiles/GameBoy_Emulator.dir/src/RAM.cpp.o" \
"CMakeFiles/GameBoy_Emulator.dir/src/ROM.cpp.o" \
"CMakeFiles/GameBoy_Emulator.dir/src/Loader.cpp.o" \
"CMakeFiles/GameBoy_Emulator.dir/src/Debug.cpp.o" \
"CMakeFiles/GameBoy_Emulator.dir/src/CPU.cpp.o" \
"CMakeFiles/GameBoy_Emulator.dir/src/Disasm.cpp.o" \
"CMakeFiles/GameBoy_Emulator.dir/src/GPU.cpp.o" \
"CMakeFiles/GameBoy_Emulator.dir/src/Display.cpp.o" \
"CMakeFiles/GameBoy_Emulator.dir/src/Input.cpp.o" \
"CMakeFiles/GameBoy_Emulator.dir/src/Audio.cpp.o" \
"CMakeFiles/GameBoy_Emulator.dir/gb_apu/Blip_Buffer.cpp.o" \
"CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Apu.cpp.o" \
"CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Oscs.cpp.o" \
"CMakeFiles/GameBoy_Emulator.dir/gb_apu/Multi_Buffer.cpp.o" \
"CMakeFiles/GameBoy_Emulator.dir/gb_apu/Sound_Queue.cpp.o"

# External object files for target GameBoy_Emulator
GameBoy_Emulator_EXTERNAL_OBJECTS =

GameBoy_Emulator: CMakeFiles/GameBoy_Emulator.dir/src/OpCodes.cpp.o
GameBoy_Emulator: CMakeFiles/GameBoy_Emulator.dir/main.cpp.o
GameBoy_Emulator: CMakeFiles/GameBoy_Emulator.dir/src/RAM.cpp.o
GameBoy_Emulator: CMakeFiles/GameBoy_Emulator.dir/src/ROM.cpp.o
GameBoy_Emulator: CMakeFiles/GameBoy_Emulator.dir/src/Loader.cpp.o
GameBoy_Emulator: CMakeFiles/GameBoy_Emulator.dir/src/Debug.cpp.o
GameBoy_Emulator: CMakeFiles/GameBoy_Emulator.dir/src/CPU.cpp.o
GameBoy_Emulator: CMakeFiles/GameBoy_Emulator.dir/src/Disasm.cpp.o
GameBoy_Emulator: CMakeFiles/GameBoy_Emulator.dir/src/GPU.cpp.o
GameBoy_Emulator: CMakeFiles/GameBoy_Emulator.dir/src/Display.cpp.o
GameBoy_Emulator: CMakeFiles/GameBoy_Emulator.dir/src/Input.cpp.o
GameBoy_Emulator: CMakeFiles/GameBoy_Emulator.dir/src/Audio.cpp.o
GameBoy_Emulator: CMakeFiles/GameBoy_Emulator.dir/gb_apu/Blip_Buffer.cpp.o
GameBoy_Emulator: CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Apu.cpp.o
GameBoy_Emulator: CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Oscs.cpp.o
GameBoy_Emulator: CMakeFiles/GameBoy_Emulator.dir/gb_apu/Multi_Buffer.cpp.o
GameBoy_Emulator: CMakeFiles/GameBoy_Emulator.dir/gb_apu/Sound_Queue.cpp.o
GameBoy_Emulator: CMakeFiles/GameBoy_Emulator.dir/build.make
GameBoy_Emulator: CMakeFiles/GameBoy_Emulator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/Flox Ajuro/GBE/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_18) "Linking CXX executable GameBoy_Emulator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GameBoy_Emulator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GameBoy_Emulator.dir/build: GameBoy_Emulator

.PHONY : CMakeFiles/GameBoy_Emulator.dir/build

CMakeFiles/GameBoy_Emulator.dir/requires: CMakeFiles/GameBoy_Emulator.dir/src/OpCodes.cpp.o.requires
CMakeFiles/GameBoy_Emulator.dir/requires: CMakeFiles/GameBoy_Emulator.dir/main.cpp.o.requires
CMakeFiles/GameBoy_Emulator.dir/requires: CMakeFiles/GameBoy_Emulator.dir/src/RAM.cpp.o.requires
CMakeFiles/GameBoy_Emulator.dir/requires: CMakeFiles/GameBoy_Emulator.dir/src/ROM.cpp.o.requires
CMakeFiles/GameBoy_Emulator.dir/requires: CMakeFiles/GameBoy_Emulator.dir/src/Loader.cpp.o.requires
CMakeFiles/GameBoy_Emulator.dir/requires: CMakeFiles/GameBoy_Emulator.dir/src/Debug.cpp.o.requires
CMakeFiles/GameBoy_Emulator.dir/requires: CMakeFiles/GameBoy_Emulator.dir/src/CPU.cpp.o.requires
CMakeFiles/GameBoy_Emulator.dir/requires: CMakeFiles/GameBoy_Emulator.dir/src/Disasm.cpp.o.requires
CMakeFiles/GameBoy_Emulator.dir/requires: CMakeFiles/GameBoy_Emulator.dir/src/GPU.cpp.o.requires
CMakeFiles/GameBoy_Emulator.dir/requires: CMakeFiles/GameBoy_Emulator.dir/src/Display.cpp.o.requires
CMakeFiles/GameBoy_Emulator.dir/requires: CMakeFiles/GameBoy_Emulator.dir/src/Input.cpp.o.requires
CMakeFiles/GameBoy_Emulator.dir/requires: CMakeFiles/GameBoy_Emulator.dir/src/Audio.cpp.o.requires
CMakeFiles/GameBoy_Emulator.dir/requires: CMakeFiles/GameBoy_Emulator.dir/gb_apu/Blip_Buffer.cpp.o.requires
CMakeFiles/GameBoy_Emulator.dir/requires: CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Apu.cpp.o.requires
CMakeFiles/GameBoy_Emulator.dir/requires: CMakeFiles/GameBoy_Emulator.dir/gb_apu/Gb_Oscs.cpp.o.requires
CMakeFiles/GameBoy_Emulator.dir/requires: CMakeFiles/GameBoy_Emulator.dir/gb_apu/Multi_Buffer.cpp.o.requires
CMakeFiles/GameBoy_Emulator.dir/requires: CMakeFiles/GameBoy_Emulator.dir/gb_apu/Sound_Queue.cpp.o.requires

.PHONY : CMakeFiles/GameBoy_Emulator.dir/requires

CMakeFiles/GameBoy_Emulator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GameBoy_Emulator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GameBoy_Emulator.dir/clean

CMakeFiles/GameBoy_Emulator.dir/depend:
	cd "/mnt/c/Users/Flox Ajuro/GBE/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/Flox Ajuro/GBE" "/mnt/c/Users/Flox Ajuro/GBE" "/mnt/c/Users/Flox Ajuro/GBE/build" "/mnt/c/Users/Flox Ajuro/GBE/build" "/mnt/c/Users/Flox Ajuro/GBE/build/CMakeFiles/GameBoy_Emulator.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/GameBoy_Emulator.dir/depend
