//
// Created by Flox Ajuro on 08/09/2018.
//

#include <cstring>
#include <cstdio>
#include "RAM.hpp"

using namespace GBE;

Byte RAM::_ram[65535];

Byte RAM::Read8(Word whereTo) {
    switch (whereTo) {
        case 0xFF00:
            if ((RAM::_ram[0xFF00] & 0x10) == 0) {
                return ((RAM::_ram[0xFF00] & 0xF0) + (Input::GetDirectionInputs() & 0x0F));
            } else if ((RAM::_ram[0xFF00] & 0x20) == 0) {
                return ((RAM::_ram[0xFF00] & 0xF0) + (Input::GetButtonInputs() & 0x0F));
            }
            break;
        default:
            return (RAM::_ram[whereTo]);
            break;
    }
    return (0x00);
}

Word RAM::Read16(Word whereTo) {
    Word toReturn;

    toReturn = RAM::_ram[whereTo + 1] << 8;
    toReturn += RAM::_ram[whereTo];
    return (toReturn);
}

void RAM::Write8(Byte toWrite, Word whereTo) {
    //char buffer[512];

    switch (whereTo) {
        case 0x0000 ... 0x7FFF:
            break;
        case 0xFF46:
            RAM::_ram[whereTo] = toWrite;
            RAM::DMATransfer(toWrite);
            break;
        case 0xE000 ... 0xFE00:
            RAM::_ram[whereTo] = toWrite;
            RAM::_ram[whereTo - 0x2000] = toWrite;
            break;
        case 0xC000 ... 0xDE00:
            RAM::_ram[whereTo] = toWrite;
            RAM::_ram[whereTo + 0x2000] = toWrite;
            break;
        case 0xFF44:
            RAM::_ram[0xFF44] = 0;
            break;
        case 0xFF47:
            RAM::_ram[whereTo] = toWrite;
            printf("Palette : 0x%02X\n", toWrite);
            break;
        case 0xFF00:
            RAM::_ram[0xFF00] = (Byte)((0xC0 + (toWrite & 0xF0)) + (RAM::Read8(0xFF00) & 0x0F));
            break;
        case 0xFF50:
            RAM::_ram[whereTo] = toWrite;
            RAM::TurnOffDMG();
            break;
        case 0xFF04:
            RAM::_ram[0xFF04] = 0x00;
            RAM::_ram[0xFF05] = 0x00;
            break;
        default:
            RAM::_ram[whereTo] = toWrite;
            break;
    }
    //sprintf(buffer, "[0x%04X] = 0x%02X\n", whereTo, RAM::Read8(whereTo));
    //Debug::LogWrite(buffer);
}

void RAM::Write16(Word toWrite, Word whereTo) {
    //char buffer[512];
    RAM::_ram[whereTo] = (Byte)(toWrite & 0xFF);
    RAM::_ram[whereTo] = (Byte)(toWrite >> 8);
    /*sprintf(buffer, "[0x%04X] = 0x%04X\n", whereTo, RAM::Read16(whereTo));
    Debug::LogWrite(buffer);*/
}

void RAM::DMATransfer(Byte data) {
    Word address = (data << 8);
    for (Byte i = 0; i < 0xA0; i++) {
        RAM::_ram[0xFE00 + i] = RAM::_ram[address + i];
    }
}

Byte* RAM::GetChunk(Word from, Word to) {
    unsigned int size;
    Byte *chunk;

    size = to - from;
    chunk = new Byte[size + 1];
    std::memcpy(chunk, &(RAM::_ram[from]), size);
    return (chunk);
}

void RAM::FillChunk(Byte value, Word from, Word to) {
    for (; from <= to; from++) {
        RAM::_ram[from] = value;
    }
}

Byte* RAM::GetRAM() {
    return (RAM::_ram);
}

void RAM::TurnOffDMG() {
    for (int i = 0; i <= 255; i++) {
        RAM::GetRAM()[i] = ROM::first256[i];
    }
}