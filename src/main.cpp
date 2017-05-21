#include <stdio.h>
#include <bitset>
#include "Opcodes.hpp"
#include "ROMLoader.hpp"
#include "Boot.hpp"
#include "RAM.hpp"

void RegDump(CPU::Z80 *cpu) {
  dprintf(1, "[DEBUG] : AF Register : 0x%04X\n", cpu->af);
  dprintf(1, "[DEBUG] : \tFlags set :\n");
  dprintf(1, "[DEBUG] : \t\tZero flag : %s\n", ((((cpu->af & 0xFF) >> 7) & 1) == 1) ? "SET" : "NOT SET");
  dprintf(1, "[DEBUG] : \t\tOperation flag : %s\n", ((((cpu->af & 0xFF) >> 6) & 1) == 1) ? "SET" : "NOT SET");
  dprintf(1, "[DEBUG] : \t\tHalf Carry flag : %s\n", ((((cpu->af & 0xFF) >> 5) & 1) == 1) ? "SET" : "NOT SET");
  dprintf(1, "[DEBUG] : \t\tCarry flag : %s\n", ((((cpu->af & 0xFF) >> 4) & 1) == 1) ? "SET" : "NOT SET");
  dprintf(1, "[DEBUG] : BC Register : 0x%04X\n", cpu->bc);
  dprintf(1, "[DEBUG] : DE Register : 0x%04X\n", cpu->de);
  dprintf(1, "[DEBUG] : HL Register : 0x%04X\n", cpu->hl);
  dprintf(1, "[DEBUG] : SP Register : 0x%04X\n", cpu->sp);
  dprintf(1, "[DEBUG] : PC Register : 0x%04X\n", cpu->pc);  
}

int main(int ac, char **av) {

  Loader::ROM *rom;
  CPU::Z80 *cpu;
  int i;
  bool found;
  
  if (ac == 2) {
    
    cpu = CPU::Z80::Instance();
    Engine::Boot::BootInit();
    rom = Loader::ROM::Instance();
    rom->Load(av[1]);
    Engine::RAM::Initialize();
    HexDump(Engine::RAM::GetRAM(), 0x0000, 0x3FFF);

    while (cpu->pc < 0x100) {
      i = 0;
      found = false;
      while (opcodes[i].byteLength != 0 && !found) {
	if (Engine::RAM::GetByte(cpu->pc) == opcodes[i].code) {
	  dprintf(1, "\n[DEBUG] : ------------------------------START---------------------------------\n");
	  dprintf(1, "[DEBUG] : Program Counter value : 0x%04X\n", cpu->pc);
	  dprintf(1, "[DEBUG] : Instruction 0x%02X found\n", opcodes[i].code);
	  opcodes[i].fptr(cpu);
	  RegDump(cpu);
	  cpu->pc += opcodes[i].byteLength;
	  dprintf(1, "[DEBUG] : ---------------------------------END----------------------------------\n");
	  found = true;
	  getchar();
	}
	i++;
      }
    }
  }
  return (0);
}
