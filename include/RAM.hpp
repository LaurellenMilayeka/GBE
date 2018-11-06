//
// Created by Flox Ajuro on 08/09/2018.
//

#ifndef GAMEBOY_EMULATOR_RAM_HPP
#define GAMEBOY_EMULATOR_RAM_HPP

#include "GBE.hpp"
#include "Input.hpp"
#include "Audio.hpp"
#include "Debug.hpp"

namespace GBE {

    typedef enum {
        NORMAL,
        RTC_SECONDS,
        RTC_MINUTES,
        RTC_HOURS,
        DAY_COUNTER
    } ReadReturn;

    typedef enum {
        ROMONLY = 0x0000,
        MBC1 = 0x0001,
        MBC2 = 0x0002,
        MBC3 = 0x0004,
        MMM01 = 0x0008,
        MBC5 = 0x0010,
        MBC6 = 0x0020,
        MBC7 = 0x0040,
        HuC3 = 0x0080,
        TAMA5 = 0x0100
    } MemoryChip;

    typedef enum {
        KB2,
        KB8,
        KB32,
        KB64,
        KB128
    } RAMChip;

    class RAM {

        private:

            static Byte _ram[65535];

            static Byte _boot[256];

            static MemoryChip _memType;
            static RAMChip _ramChip;

            static bool _isRAMEnabled;
            static bool _saveRAM;
            static Byte _mode;
            static Byte _selectedRAMBank;

        public:
            static Byte _ramBanks[16][8192];

            static void Write8(Byte toWrite, Word whereTo);
            static void Write16(Word toWrite, Word whereTo);

            static Byte Read8(Word whereTo);
            static Word Read16(Word whereTo);

            static void DMATransfer(Byte data);

            static void FillChunk(Byte value, Word from, Word to);
            static Byte* GetChunk(Word from, Word to);

            static void TurnOffDMG();

            static Byte* GetRAM();

            static MemoryChip GetMemoryType();
            static RAMChip GetRAMChipType();

            static void SetMemoryType(MemoryChip type);
            static void SetRAMType(RAMChip type);

            static bool SavingRAM();
            static void SaveRAM();
            static void SwitchRAMBank(Byte newBankIndex);

    };

};

#endif //GAMEBOY_EMULATOR_ROM_HPP
