#include <iomanip>
#include "Disasm.hpp"

// NOP Instruction
// Do nothing...
// Wait 4 cycles
void CPU::Disasm::Dis0x00() {

}

// LD Instruction
// Load the value of 16bytes-direct in BC
void CPU::Disasm::Dis0x01() {
  CPU::Z80 *cpu = CPU::Z80::Instance();
  cpu->bc = Engine::RAM::GetByte(cpu->pc++);
  std::cout << "BC register status : " << std::hex << std::setw(4) << cpu->bc << std::endl;
  cpu->bc <<= 8;
  std::cout << "BC register status : " << std::hex << std::setw(4) << cpu->bc << std::endl;
  cpu->bc += Engine::RAM::GetByte(cpu->pc++);
  std::cout << "BC register status : " << std::hex << std::setw(4) << cpu->bc << std::endl;
  cpu->pc++;
}

void CPU::Disasm::Dis0x02() {

}

void CPU::Disasm::Dis0x03() {

}

void CPU::Disasm::Dis0x04() {

}

void CPU::Disasm::Dis0x05() {

}

void CPU::Disasm::Dis0x06() {

}

void CPU::Disasm::Dis0x07() {

}

void CPU::Disasm::Dis0x08() {

}

void CPU::Disasm::Dis0x09() {

}

void CPU::Disasm::Dis0x0A() {

}

void CPU::Disasm::Dis0x0B() {

}

void CPU::Disasm::Dis0x0C() {

}

void CPU::Disasm::Dis0x0D() {

}

void CPU::Disasm::Dis0x0E() {

}

void CPU::Disasm::Dis0x0F() {

}
