//
// Created by Flox Ajuro on 08/09/2018.
//

#include <cstring>
#include <cstdio>
#include "RAM.hpp"

using namespace GBE;

Byte RAM::_ram[65535];

Byte RAM::Read8(Word whereTo) {
    return (RAM::_ram[whereTo]);
}

Word RAM::Read16(Word whereTo) {
    Word toReturn;

    toReturn = RAM::_ram[whereTo + 1] << 8;
    toReturn += RAM::_ram[whereTo];
    return (toReturn);
}

void RAM::Write8(Byte toWrite, Word whereTo) {
    if (whereTo == 0xFF46) {
        RAM::DMATransfer(toWrite);
    } else if ((whereTo >= 0xE000) && (whereTo < 0xFE00)) {
        RAM::_ram[whereTo] = toWrite;
        RAM::_ram[whereTo - 0x2000] = toWrite;
    } else if (whereTo == 0xFF44) {
        RAM::_ram[0xFF44] = 0;
    } else if (whereTo == 0xFF00) {
        RAM::_ram[0xFF00] = (Byte)((toWrite & 0xF0) + 0xF);
    } else {
        RAM::_ram[whereTo] = toWrite;
    }
}

void RAM::Write16(Word toWrite, Word whereTo) {
    RAM::_ram[whereTo] = (Byte)(toWrite & 0xFF);
    RAM::_ram[whereTo] = (Byte)(toWrite >> 8);
}

void RAM::DMATransfer(Byte data) {
    Word address = (data << 8);
    for (Byte i = 0; i < 0xA0; i++) {
        RAM::Write8(RAM::Read8((Word)(address + i)), (Word)(0xFE00 + i));
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