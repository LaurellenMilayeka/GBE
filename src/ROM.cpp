//
// Created by Flox Ajuro on 08/09/2018.
//

#include "ROM.hpp"
#include "RAM.hpp"

using namespace GBE;

char ROM::name[16];

std::string ROM::romPath;
unsigned int ROM::size;
unsigned int ROM::ramSize;
Byte ROM::_hiROMBank;
Byte ROM::_loROMBank;
Word ROM::_currentBank;

std::fstream ROM::externRAM;

Byte *ROM::_romContent;

bool ROM::ExternalRAMExists() {
    struct stat st;
    std::string filename = std::string(ROM::romPath) + ".sav";

    if (stat(filename.c_str(), &st) != 0) {
        return (false);
    }
    return (true);
}

void ROM::SetExternalRAMSize(Byte data) {
    switch (data) {
        case 0x01:
            ROM::ramSize = (2 * 1024);
            break;
        case 0x02:
            ROM::ramSize = (8 * 1024);
            break;
        case 0x03:
            ROM::ramSize = (32 * 1024);
            break;
        case 0x04:
            ROM::ramSize = (128 * 1024);
            break;
        case 0x05:
            ROM::ramSize = (64 * 1024);
            break;
    }
} 

void ROM::SwitchROMBank(Word newBankIndex) {
    unsigned int i = 0;
    memcpy(&(RAM::GetRAM()[0x4000]), &(ROM::_romContent[(0x4000 * newBankIndex)]), 0x4000);
    ROM::_currentBank = newBankIndex;
}

void ROM::SaveExternalRAM() {
    std::string filename = std::string(ROM::romPath) + ".sav";

    ROM::externRAM.open(filename.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
    for (unsigned int j = 0; j < (ROM::ramSize / 8192); j++) {
        ROM::externRAM.write((char*)RAM::_ramBanks[j], 0x2000);
    }
    ROM::externRAM.close();
}

void ROM::LoadExternalRAM() {
    std::string filename = std::string(ROM::romPath) + ".sav";

    ROM::externRAM.open(filename.c_str(), std::ios::in | std::ios::binary);
    for (unsigned int j = 0; j < (ROM::ramSize / 8192); j++) {
        ROM::externRAM.read((char*)RAM::_ramBanks[j], 8192);
    }
    ROM::externRAM.close();
}
