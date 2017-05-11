#include <iomanip>
#include "Disasm.hpp"
#include <bitset>

// NOP Instruction
// Do nothing...
// Wait 4 cycles

void CPU::Disasm::Dis0x00(CPU::Z80 *) {

}

// LD Instruction
// Load the value of 16-bits direct in 16-bits register BC

void CPU::Disasm::Dis0x01(CPU::Z80 *cpu) {
  cpu->bc = Engine::RAM::GetByte(++cpu->pc);
  cpu->bc <<= 8;
  cpu->bc += Engine::RAM::GetByte(++cpu->pc);
  cpu->bc = (cpu->bc >> 8) | (cpu->bc << 8);
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits register A at the address pointed by 16-bits register BC

void CPU::Disasm::Dis0x02(CPU::Z80 *cpu) {
  Engine::RAM::SetByte(cpu->bc, (cpu->af >> 8));
}

// INC Instruction
// Increment 16-bits register BC

void CPU::Disasm::Dis0x03(CPU::Z80 *cpu) {
  cpu->bc++;
}

// INC Instruction
// Increment 8-bits register B

void CPU::Disasm::Dis0x04(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc >> 8) + 1;
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
}

// DEC Instruction
// Decrement 8-bits register B

void CPU::Disasm::Dis0x05(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc >> 8) - 1;
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
}

// LD Instruction
// Load the value of 8-bits direct in 8-bits register B

void CPU::Disasm::Dis0x06(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = cpu->bc >> 8;
  tmp = Engine::RAM::GetByte(cpu->pc++);
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
  cpu->pc++;
}

// RLCA Instruction
// TODO ????

void CPU::Disasm::Dis0x07(CPU::Z80 *cpu) {
  uint8_t tmp;
  
  tmp = cpu->af >> 8;
  tmp = (tmp << 1) |
    ((tmp & (1 << (sizeof(uint8_t)*8-1))) >> ((sizeof(uint8_t)*8-1) - 1)) |
    (tmp & (1 << (sizeof(uint8_t)*8-1)));
  tmp ^= (-8 ^ tmp) & (1 << 0);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
}

// LD Instruction
// Load the value of 16-bits register SP at the address pointed by 16-bits direct

void CPU::Disasm::Dis0x08(CPU::Z80 *cpu) {
  uint16_t address;
  
  address = Engine::RAM::GetByte(++cpu->pc);
  address = address << 8;
  address += Engine::RAM::GetByte(++cpu->pc);
  address = (address >> 8) | (address << 8);
  Engine::RAM::SetByte(address, (cpu->sp & 0xFF));
  Engine::RAM::SetByte(address + 1, (cpu->sp >> 8));
}

// ADD Instruction
// Add 16-bits register BC to 16-bits register HL

void CPU::Disasm::Dis0x09(CPU::Z80 *cpu) {
  cpu->hl += cpu->bc;
}

// LD Instruction
// Load the value of 8-bits direct at the address pointed by 16-bits register BC in 8-bits register A

void CPU::Disasm::Dis0x0A(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->bc);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
}

// DEC Instruction
// Decrement 16-bits register BC

void CPU::Disasm::Dis0x0B(CPU::Z80 *cpu) {
  cpu->bc--;
}

// INC Instruction
// Increment 8-bits register C

void CPU::Disasm::Dis0x0C(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc & 0xFF) + 1;
  cpu->bc = ((cpu->bc >> 8) << 8) + (tmp & 0xFF);
}

// DEC Instruction
// Decrement 8-bits register C

void CPU::Disasm::Dis0x0D(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc & 0xFF) - 1;
  cpu->bc = ((cpu->bc >> 8) << 8) + (tmp & 0xFF);
}

// LD Instruction
// Load the value of 8-bits direct in 8-bits register C

void CPU::Disasm::Dis0x0E(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(++cpu->pc);
  cpu->bc = ((cpu->bc >> 8) << 8) + (tmp & 0xFF);
}

// RRCA Instruction
// TODO ????
void CPU::Disasm::Dis0x0F(CPU::Z80 *) {
  /* RRCA */
}
