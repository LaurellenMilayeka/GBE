//
// Created by Flox Ajuro on 08/09/2018.
//

#ifndef GAMEBOY_EMULATOR_OPCODES_HPP
#define GAMEBOY_EMULATOR_OPCODES_HPP

#include <string>

#include "GBE.hpp"
#include "CPU.hpp"

typedef struct {
    std::string mnemo;
    Byte opCode;
    Byte length;
    char cycles;
    void (*f)(GBE::CPU&);
} OpCode;

extern OpCode opCodes[];
extern OpCode extOpCodes[];

#endif //GAMEBOY_EMULATOR_OPCODES_HPP
