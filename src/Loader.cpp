//
// Created by Flox Ajuro on 08/09/2018.
//

#include <iostream>
#include <fstream>
#include <RAM.hpp>
#include "ROM.hpp"
#include "Loader.hpp"

using namespace GBE;

void Loader::LoadBootloader() {
    std::ifstream file("../data/DMG_ROM.bin", std::ios::binary);
    unsigned int size;

    if (!file.is_open()) {
        std::cerr << "[LOADER] : Could not open file " << "DMG_ROM.bin" << std::endl;
        return;
    }

    file.seekg(0, std::ios_base::end);
    size = (unsigned int)file.tellg();
    file.seekg(0, std::ios_base::beg);
    file.read((char*)RAM::GetRAM(), size);

    file.close();
}

void Loader::LoadROM(std::string const &romPath) {
    std::ifstream file(romPath, std::ios::binary);
    unsigned int size;

    if (!file.is_open()) {
        std::cerr << "[LOADER] : Could not open file " << romPath << std::endl;
        return;
    }

    file.seekg(0, std::ios_base::end);
    size = (unsigned int)file.tellg();
    file.seekg(0, std::ios_base::beg);
    ROM::_romContent = new Byte[size];
    file.read((char*)ROM::_romContent, size);
    file.close();

    ROM::romPath = romPath.substr(0, romPath.length() - 3);
    ROM::size = size;
    for (unsigned int i = 0; i < 16; i++) { ROM::name[i] = ROM::_romContent[i + 0x134]; }
    
    switch (ROM::_romContent[0x147]) {
        case 0x00: RAM::SetMemoryType(MemoryChip::ROMONLY); break;
        case 0x01 ... 0x03:
            if (ROM::_romContent[0x147] == 0x03) RAM::SaveRAM();
            RAM::SetMemoryType(MemoryChip::MBC1); break;
        case 0x05 ... 0x06:
            if (ROM::_romContent[0x147] == 0x06) RAM::SaveRAM();
            RAM::SetMemoryType(MemoryChip::MBC2); break;
        case 0x0B ... 0x0D:
            if (ROM::_romContent[0x147] == 0x0D) RAM::SaveRAM();
            RAM::SetMemoryType(MemoryChip::MMM01); break;
        case 0x0F ... 0x13:
            if (ROM::_romContent[0x147] == 0x13 || ROM::_romContent[0x147] == 0x0F || ROM::_romContent[0x147] == 0x10) RAM::SaveRAM();
            RAM::SetMemoryType(MemoryChip::MBC3); break;
        case 0x19 ... 0x1E:
            if (ROM::_romContent[0x147] == 0x1B || ROM::_romContent[0x147] == 0x1E) RAM::SaveRAM();
            RAM::SetMemoryType(MemoryChip::MBC5); break;
        case 0x20: RAM::SetMemoryType(MemoryChip::MBC6); break;
        case 0x22:
            if (ROM::_romContent[0x147] == 0x22) RAM::SaveRAM();
            RAM::SetMemoryType(MemoryChip::MBC7); break;
        case 0xFD: RAM::SetMemoryType(MemoryChip::TAMA5); break;
        case 0xFE: RAM::SetMemoryType(MemoryChip::HuC3); break;
    }

    switch (ROM::_romContent[0x149]) {
        case 0x01: RAM::SetRAMType(RAMChip::KB2); break;
        case 0x02: RAM::SetRAMType(RAMChip::KB8); break;
        case 0x03: RAM::SetRAMType(RAMChip::KB32); break;
        case 0x04: RAM::SetRAMType(RAMChip::KB128); break;
        case 0x05: RAM::SetRAMType(RAMChip::KB64); break;
    }
    
    if (RAM::GetMemoryType() != MemoryChip::ROMONLY) {
        for (unsigned int i = 0; i < 0x8000; i++) {
            RAM::GetRAM()[i] = ROM::_romContent[i];
        }
    } else {
        memcpy(RAM::GetRAM(), ROM::_romContent, ROM::size);
    }

    ROM::SetExternalRAMSize(ROM::_romContent[0x149]);
    if (RAM::SavingRAM()) {
        ROM::LoadExternalRAM();
    }
}

void Loader::UnloadROM() {
    delete (ROM::_romContent);
}