//
// Created by Flox Ajuro on 08/09/2018.
//

#ifndef GAMEBOY_EMULATOR_DEBUG_HPP
#define GAMEBOY_EMULATOR_DEBUG_HPP

#include "GBE.hpp"
#include "CPU.hpp"

#include "OpCodes.hpp"

namespace GBE {

    class Debug {

        private:

            static std::string const& ReplaceInString(std::string const& src, std::string const& haystack, std::string const& toInsert);

            static std::fstream log;

        public:

            static void Dump(Byte* toDump);
            static void DumpFromTo(Byte* toDump, Word from, Word to);
            static void DebugInstr(OpCode instr, CPU &cpu);
            static void DumpRegistries(CPU const& cpu);
            static void DumpRAMRegistries();
            static void DebugJoypad();
            static void DumpFlags(CPU const& cpu);

            static void LogWrite(std::string const& toWrite);

    };

};

#endif //GAMEBOY_EMULATOR_DEBUG_HPP
