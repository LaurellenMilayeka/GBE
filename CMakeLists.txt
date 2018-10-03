cmake_minimum_required(VERSION 3.5)
project(GameBoy_Emulator)

set(CMAKE_CXX_STANDARD 14)

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g3 -lmingw32")
endif (WIN32)
if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g3")
endif (UNIX)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(GameBoy_Emulator include/OpCodes.hpp src/OpCodes.cpp main.cpp include/RAM.hpp include/GBE.hpp src/RAM.cpp include/Loader.hpp include/ROM.hpp src/ROM.cpp src/Loader.cpp include/Debug.hpp src/Debug.cpp include/CPU.hpp src/CPU.cpp include/Disasm.hpp src/Disasm.cpp include/GPU.hpp src/GPU.cpp include/Display.hpp src/Display.cpp)

target_link_libraries(GameBoy_Emulator SDL2main SDL2 SDL2_image)