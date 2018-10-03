//
// Created by Flox Ajuro on 08/09/2018.
//

#ifndef GAMEBOY_EMULATOR_GBE_HPP
#define GAMEBOY_EMULATOR_GBE_HPP

#include <SDL2/SDL.h>

using Byte = unsigned char;
using Word = unsigned short;
using SignedByte = char;
using SignedWord = short;

typedef struct {
    int r;
    int g;
    int b;
    int a;
} Color;

#endif //GAMEBOY_EMULATOR_GBE_HPP
