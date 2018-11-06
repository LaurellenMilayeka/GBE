cmake_minimum_required(VERSION 3.5)
project(GameBoy_Emulator)

set(CMAKE_CXX_STANDARD 14)

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g -O0 -lmingw32")
endif (WIN32)
if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
endif (UNIX)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/)

add_executable(GameBoy_Emulator include/OpCodes.hpp src/OpCodes.cpp main.cpp include/RAM.hpp include/GBE.hpp src/RAM.cpp include/Loader.hpp include/ROM.hpp src/ROM.cpp src/Loader.cpp include/Debug.hpp src/Debug.cpp include/CPU.hpp src/CPU.cpp include/Disasm.hpp src/Disasm.cpp include/GPU.hpp src/GPU.cpp include/Display.hpp src/Display.cpp include/Input.hpp src/Input.cpp include/Audio.hpp src/Audio.cpp gb_apu/blargg_common.h gb_apu/blargg_source.h gb_apu/Blip_Buffer.cpp gb_apu/Blip_Buffer.h gb_apu/Blip_Synth.h gb_apu/Gb_Apu.cpp gb_apu/Gb_Apu.h gb_apu/Gb_Oscs.cpp gb_apu/Gb_Oscs.h gb_apu/Multi_Buffer.cpp gb_apu/Multi_Buffer.h boost/config.hpp boost/cstdint.hpp boost/static_assert.hpp gb_apu/Sound_Queue.h gb_apu/Sound_Queue.cpp)

target_link_libraries(GameBoy_Emulator SDL2main SDL2 SDL2_image)