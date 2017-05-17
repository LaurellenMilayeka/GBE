#include <stdio.h>
#include <bitset>
#include "Disasm.hpp"
#include "ROMLoader.hpp"
#include "BIOS.hpp"
#include "Boot.hpp"

int main(int ac, char **av) {

  Loader::ROM *rom;
  CPU::Z80 *cpu;
  uint8_t tmp = 0xF0;

  std::cout << "Before swap : " << std::bitset<8>(tmp) << std::endl;
  tmp = (tmp >> 4) | (tmp << 4);
  std::cout << "After swap : " << std::bitset<8>(tmp) << std::endl;  
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
