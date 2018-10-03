//
// Created by Flox Ajuro on 08/09/2018.
//

#include <ROM.hpp>
#include <RAM.hpp>
#include <iostream>
#include <fstream>
#include <GPU.hpp>
#include "Debug.hpp"

using namespace GBE;

void Debug::Dump(Byte *toDump) {
    std::cout << "ROM TITLE : " << ROM::name << std::endl;
    std::cout << "ROM SIZE : " << ROM::size << std::endl;
    for (unsigned int i = 0; i < ROM::size; i++) {
        if ((i % 16) == 0 && i != 0) {
            printf("\n");
        }
        printf("0x%02X ", toDump[i]);
    }
}

void Debug::DumpFromTo(Byte *toDump, Word from, Word to) {
    unsigned int cnt = 0;

    printf("Dump from 0x%04X to 0x%04X\n", from, to);
    for (unsigned int i = from; i <= to; i++) {
        if ((cnt % 16) == 0 && cnt != 0) {
            printf("\n0x%04X : ", i);
        }
        printf("0x%02X ", toDump[i]);
        cnt++;
    }
}

void Debug::DebugJoypad() {
    Byte joypad = RAM::Read8(0xFF00);

    if (((joypad >> 4) & 1) == 0) {
        if (((joypad >> 3) & 1) == 0) {
            printf("Down button pressed\n");
        }
        if (((joypad >> 2) & 1) == 0) {
            printf("Up button pressed\n");
        }
        if (((joypad >> 1) & 1) == 0) {
            printf("Left button pressed\n");
        }
        if (((joypad >> 0) & 1) == 0) {
            printf("Right button pressed\n");
        }
    }
    if (((joypad >> 5) & 1) == 0) {
        if (((joypad >> 3) & 1) == 0) {
            printf("Start button pressed\n");
        }
        if (((joypad >> 2) & 1) == 0) {
            printf("Select button pressed\n");
        }
        if (((joypad >> 1) & 1) == 0) {
            printf("B button pressed\n");
        }
        if (((joypad >> 0) & 1) == 0) {
            printf("A button pressed\n");
        }
    }
}

void Debug::DumpRAMRegistries() {
    char buffer[1024];

    sprintf(buffer, "LY : 0x%02X\n", RAM::Read8(LY));
    //printf("%s", buffer);
    Debug::LogWrite(buffer);
}

void Debug::DumpRegistries(const GBE::CPU &cpu) {
    char buffer[1024];

    sprintf(buffer, "Dump CPU registries : \n\tAF : 0x%04X\tBC : 0x%04X\tDE : 0x%04X\tHL : 0x%04X\tSP : 0x%04X\tPC : 0x%04X\n",
            cpu.GetRegistry16Value(Registry16::AF), cpu.GetRegistry16Value(Registry16::BC), cpu.GetRegistry16Value(Registry16::DE),
            cpu.GetRegistry16Value(Registry16::HL), cpu.GetRegistry16Value(Registry16::SP), cpu.GetProgramCounter() - 1);
    //printf("%s", buffer);
    Debug::LogWrite(buffer);
}

void Debug::DumpFlags(const GBE::CPU &cpu) {
    char buffer[1024];

    sprintf(buffer, "Dump CPU Flags : \n\tZERO : %s\tHALF : %s\tOPERATION : %s\tCARRY : %s\n",
            (cpu.IsFlagSet(Flags::ZERO) ? "true" : "false"), (cpu.IsFlagSet(Flags::HALF_CARRY) ? "true" : "false"),
            (cpu.IsFlagSet(Flags::OPERATION) ? "true" : "false"), (cpu.IsFlagSet(Flags::CARRY) ? "true" : "false"));
    //printf("%s", buffer);
    Debug::LogWrite(buffer);
}

void Debug::LogWrite(std::string const& toWrite) {
    std::fstream log("log.txt", std::ios::out | std::ios::app);

    log.write(toWrite.c_str(), toWrite.size());
    log.close();
}