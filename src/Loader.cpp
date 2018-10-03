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
    std::ifstream file("data/DMG_ROM.bin", std::ios::binary);
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
    file.read((char*)RAM::GetRAM(), size);

    file.close();

    ROM::name = romPath;
    ROM::size = size;
}

void Loader::UnloadROM() {

}