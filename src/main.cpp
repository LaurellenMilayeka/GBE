#include <stdio.h>
#include "Z80.hpp"
#include "Disasm.hpp"
#include "ROMLoader.hpp"
#include "BIOS.hpp"

int main(int ac, char **av) {

  Loader::ROM *rom;
  /*CPU::Z80 *cpu;
  
  cpu = CPU::Z80::Instance();
  CPU::Disasm::Dis0x01();
  dprintf(1, "AF : 0x%04X\n", cpu->af);
  dprintf(1, "BC : 0x%04X\n", cpu->bc);
  dprintf(1, "DE : 0x%04X\n", cpu->de);
  dprintf(1, "HL : 0x%04X\n", cpu->hl);
  dprintf(1, "SP : 0x%04X\n", cpu->sp);
  dprintf(1, "PC : 0x%04X\n", cpu->pc);*/

  if (ac == 2) {
    rom = Loader::ROM::Instance();
    rom->Load(av[1]);
    //Engine::RAM::Initialize();
    //HexDump(Engine::RAM::GetRAM(), 0x0000, 0x3FFF);
    Engine::BIOS::CheckBIOSIntegrity();
  }
  return (0);
}
