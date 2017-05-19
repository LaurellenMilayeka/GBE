#include <stdio.h>
#include <bitset>
#include "Disasm.hpp"
#include "ROMLoader.hpp"
#include "BIOS.hpp"
#include "Boot.hpp"

int main(int ac, char **av) {

  av = av;
  //Loader::ROM *rom;
  CPU::Z80 *cpu;
  //uint8_t tmp = 0xFF;

  if (ac == 2) {
    
    cpu = CPU::Z80::Instance();
    cpu->af = 0xAA00;
    cpu->bc = 0x02EF;
    cpu->hl = 0xFF00;
    dprintf(1, "HL before : 0x%04X\n", cpu->hl);
    dprintf(1, "BC before : 0x%04X\n", cpu->bc);
    std::cout << "Before instruction : " << std::bitset<8>(cpu->af >> 8);
    std::cout << " ;; " << std::bitset<8>(cpu->af & 0xFF) << std::endl;
    CPU::Disasm::Dis0x09(cpu);
    dprintf(1, "HL before : 0x%04X\n", cpu->hl);
    dprintf(1, "BC after : 0x%04X\n", cpu->bc);
    std::cout << "After instruction : " << std::bitset<8>(cpu->af >> 8);
    std::cout << " ;; " << std::bitset<8>(cpu->af & 0xFF) << std::endl;
    /*Engine::Boot::BootInit();
    rom = Loader::ROM::Instance();
    rom->Load(av[1]);
    Engine::RAM::Initialize();
    HexDump(Engine::RAM::GetRAM(), 0x0000, 0x0140);
    Engine::BIOS::CheckBIOSIntegrity();
    CPU::Disasm::Dis0x07(cpu);*/
  }
  return (0);
}
