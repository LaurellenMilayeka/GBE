//
// Created by Flox Ajuro on 08/09/2018.
//

#ifndef GAMEBOY_EMULATOR_RAM_HPP
#define GAMEBOY_EMULATOR_RAM_HPP

#include "GBE.hpp"
#include "ROM.hpp"
#include "Input.hpp"
#include "Debug.hpp"

namespace GBE {

    class RAM {

        private:

            static Byte _ram[65535];

        public:

            static void Write8(Byte toWrite, Word whereTo);
            static void Write16(Word toWrite, Word whereTo);

            static Byte Read8(Word whereTo);
            static Word Read16(Word whereTo);

            static void DMATransfer(Byte data);

            static void FillChunk(Byte value, Word from, Word to);
            static Byte* GetChunk(Word from, Word to);

            static void TurnOffDMG();

            static Byte* GetRAM();

    };

};

#endif //GAMEBOY_EMULATOR_ROM_HPP
