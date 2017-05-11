#include <stdio.h>
#include "Disasm.hpp"
#include "ROMLoader.hpp"
#include "BIOS.hpp"
#include "Boot.hpp"

int main(int ac, char **av) {

  Loader::ROM *rom;
  CPU::Z80 *cpu;
  
  if (ac == 2) {
    cpu = CPU::Z80::Instance();
    Engine::Boot::BootInit();
    rom = Loader::ROM::Instance();
    rom->Load(av[1]);
    Engine::RAM::Initialize();
    //HexDump(Engine::RAM::GetRAM(), 0x0000, 0x0140);
    Engine::BIOS::CheckBIOSIntegrity();
    CPU::Disasm::Dis0x07(cpu);
  }
  return (0);
}
