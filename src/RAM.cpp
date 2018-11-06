//
// Created by Flox Ajuro on 08/09/2018.
//

#include <cstring>
#include <cstdio>
#include "RAM.hpp"
#include "ROM.hpp"

using namespace GBE;

Byte RAM::_ram[65535];
MemoryChip RAM::_memType;
RAMChip RAM::_ramChip;

bool RAM::_isRAMEnabled = false;
bool RAM::_saveRAM = false;
Byte RAM::_mode = 0;
Byte RAM::_selectedRAMBank = 0;
Byte RAM::_ramBanks[16][8192];

Byte RAM::Read8(Word whereTo) {
	if (whereTo == 0xFF00) {
		if ((RAM::_ram[0xFF00] & 0x10) == 0) {
			return ((RAM::_ram[0xFF00] & 0xF0) + (Input::GetDirectionInputs() & 0x0F));
		}
		else if ((RAM::_ram[0xFF00] & 0x20) == 0) {
			return ((RAM::_ram[0xFF00] & 0xF0) + (Input::GetButtonInputs() & 0x0F));
		}
	}
	else if (whereTo >= 0xFF10 && whereTo <= 0xFF3F) {
		Audio::GetAPU()->read_register(CPU::clock, whereTo);
	} else {
    	return (RAM::_ram[whereTo]);
	}
}

Word RAM::Read16(Word whereTo) {
    Word toReturn;

    toReturn = RAM::_ram[whereTo + 1] << 8;
    toReturn += RAM::_ram[whereTo];
    return (toReturn);
}

void RAM::Write8(Byte toWrite, Word whereTo) {
	if (whereTo <= 0x7FFF) {
		if (whereTo <= 0x1FFF) {
			RAM::_isRAMEnabled = ((toWrite & 0x0A) == 0x0A);
		}
		else if (whereTo >= 0x2000 && whereTo <= 0x3FFF) {
			if (RAM::_memType == MemoryChip::MBC1 || RAM::_memType == MemoryChip::MBC3) {
				if (RAM::_memType == MemoryChip::MBC1) {
					ROM::_loROMBank = toWrite & 0x7F;
					if (((ROM::_hiROMBank << 5) | ROM::_loROMBank) == 0x00 || ((ROM::_hiROMBank << 5) | ROM::_loROMBank) == 0x20
						|| ((ROM::_hiROMBank << 5) | ROM::_loROMBank) == 0x40 || ((ROM::_hiROMBank << 5) | ROM::_loROMBank) == 0x60) {
						ROM::_loROMBank++;
					}
				}
				else {
					ROM::_loROMBank = toWrite & 0x7F;
					if (((ROM::_hiROMBank << 5) | ROM::_loROMBank) == 0x00) {
						ROM::_loROMBank++;
					}
				}
				ROM::SwitchROMBank((ROM::_hiROMBank << 5) | ROM::_loROMBank);
			}
			else if (RAM::_memType == MemoryChip::MBC5) {
				if (whereTo < 0x3000) {
					ROM::_loROMBank = toWrite;
				}
				else {
					ROM::_hiROMBank = toWrite & 0x01;
				}
				ROM::SwitchROMBank((ROM::_hiROMBank << 8) | ROM::_loROMBank);
			}
		}
		else if (whereTo >= 0x4000 && whereTo <= 0x5FFF) {
			if (RAM::_mode == 1) {
				Word bank;

				if (RAM::_memType == MemoryChip::MBC1) {
					bank = toWrite & 0x03;
				}
				else if (RAM::_memType == MemoryChip::MBC5 || RAM::_memType == MemoryChip::MBC3) {
					bank = toWrite & 0x0F;
				}
				RAM::SwitchRAMBank(bank);
			}
			else {
				if (RAM::_memType == MemoryChip::MBC1) {
					ROM::_hiROMBank = toWrite & 0x03;
					ROM::SwitchROMBank((ROM::_hiROMBank << 5) | ROM::_loROMBank);
				}
			}
		}
		else {
			RAM::_mode = toWrite & 0x01;
		}
	}
	else if (whereTo >= 0xC000 && whereTo <= 0xDE00) {
		RAM::_ram[whereTo] = toWrite;
		RAM::_ram[whereTo + 0x2000] = toWrite;
	}
	else if (whereTo >= 0xE000 && whereTo <= 0xFE00) {
		RAM::_ram[whereTo] = toWrite;
		RAM::_ram[whereTo - 0x2000] = toWrite;
	}
	else if (whereTo == 0xFF04) {
		RAM::_ram[0xFF04] = 0x00;
		RAM::_ram[0xFF05] = 0x00;
	}
	else if (whereTo >= 0xFF10 && whereTo <= 0xFF3F) {
		Audio::GetAPU()->write_register(CPU::clock, whereTo, toWrite);
	}
	else if (whereTo == 0xFF44) {
		RAM::_ram[0xFF44] = 0;
	}
	else if (whereTo == 0xFF46) {
		RAM::_ram[whereTo] = toWrite;
		RAM::DMATransfer(toWrite);
	}
	else if (whereTo == 0xFF50) {
		//RAM::_ram[whereTo] = toWrite;
		RAM::TurnOffDMG();
	}
	else {
		RAM::_ram[whereTo] = toWrite;
	}
}

void RAM::Write16(Word toWrite, Word whereTo) {
    RAM::_ram[whereTo] = (Byte)(toWrite & 0xFF);
    RAM::_ram[whereTo + 1] = (Byte)(toWrite >> 8);
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
        RAM::GetRAM()[i] = ROM::_romContent[i];
    }
}

MemoryChip RAM::GetMemoryType() {
    return (RAM::_memType);
}

RAMChip RAM::GetRAMChipType() {
    return (RAM::_ramChip);
}

void RAM::SetMemoryType(MemoryChip type) {
    RAM::_memType = type;
}

void RAM::SetRAMType(RAMChip type) {
    RAM::_ramChip = type;
}

void RAM::SwitchRAMBank(Byte newBankIndex) {
    memcpy(RAM::_ramBanks[RAM::_selectedRAMBank], &(RAM::_ram[0xA000]), 0x2000);
    memcpy(&(RAM::_ram[0xA000]), RAM::_ramBanks[newBankIndex], 0x2000);
    RAM::_selectedRAMBank = newBankIndex;
}

void RAM::SaveRAM() {
    RAM::_saveRAM = true;
}

bool RAM::SavingRAM() {
    return (RAM::_saveRAM);
}