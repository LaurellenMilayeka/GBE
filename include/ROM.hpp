//
// Created by Flox Ajuro on 08/09/2018.
//

#ifndef GAMEBOY_EMULATOR_ROM_HPP
#define GAMEBOY_EMULATOR_ROM_HPP

#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>

#include "GBE.hpp"

namespace GBE {

    class ROM {

        private:

            static bool ExternalRAMExists();

        public:

            static std::string romPath;
            static char name[16];
            static unsigned int size;
            static unsigned int ramSize;

            static Byte *_romContent;
            static Byte _hiROMBank;
            static Byte _loROMBank;
            static Word _currentBank;

            static std::fstream externRAM;

            static void SwitchROMBank(Word newBankIndex);

            static void SetExternalRAMSize(Byte data);

            static void LoadExternalRAM();
            static void SaveExternalRAM();

    };

};

#endif //GAMEBOY_EMULATOR_ROM_HPP
