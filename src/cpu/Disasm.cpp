#include <iomanip>
#include "Disasm.hpp"
#include <bitset>

// NOP Instruction
// Do nothing...
// Wait 4 cycles

void CPU::Disasm::Dis0x00(CPU::Z80 *cpu) {
  cpu->pc++;
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
  cpu->pc++;
}

// INC Instruction
// Increment 16-bits register BC

void CPU::Disasm::Dis0x03(CPU::Z80 *cpu) {
  cpu->bc++;
  cpu->pc++;
}

// INC Instruction
// Increment 8-bits register B

void CPU::Disasm::Dis0x04(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc >> 8) + 1;
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
  cpu->pc++;
}

// DEC Instruction
// Decrement 8-bits register B

void CPU::Disasm::Dis0x05(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc >> 8) - 1;
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
  cpu->pc++;
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
  tmp = (tmp << 1) | (tmp >> (sizeof(uint8_t) * 8 - 1));
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
  cpu->pc++;
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
  cpu->pc++;
}

// ADD Instruction
// Add 16-bits register BC to 16-bits register HL

void CPU::Disasm::Dis0x09(CPU::Z80 *cpu) {
  cpu->hl += cpu->bc;
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits direct at the address pointed by 16-bits register BC in 8-bits register A

void CPU::Disasm::Dis0x0A(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->bc);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
  cpu->pc++;
}

// DEC Instruction
// Decrement 16-bits register BC

void CPU::Disasm::Dis0x0B(CPU::Z80 *cpu) {
  cpu->bc--;
  cpu->pc++;
}

// INC Instruction
// Increment 8-bits register C

void CPU::Disasm::Dis0x0C(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc & 0xFF) + 1;
  cpu->bc = ((cpu->bc >> 8) << 8) + (tmp & 0xFF);
  cpu->pc++;
}

// DEC Instruction
// Decrement 8-bits register C

void CPU::Disasm::Dis0x0D(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc & 0xFF) - 1;
  cpu->bc = ((cpu->bc >> 8) << 8) + (tmp & 0xFF);
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits direct in 8-bits register C

void CPU::Disasm::Dis0x0E(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(++cpu->pc);
  cpu->bc = ((cpu->bc >> 8) << 8) + (tmp & 0xFF);
  cpu->pc++;
}

// RRCA Instruction
// Rotate 8-bits register A bits to the right

void CPU::Disasm::Dis0x0F(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = cpu->af >> 8;
  tmp = (tmp >> 1) | (tmp << (sizeof(uint8_t)*8 - 1));
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
  cpu->pc++;
}

// STOP Instruction
// Halt the program execution until a button is pressed

void CPU::Disasm::Dis0x10(CPU::Z80 *cpu) {
  cpu->pc++;
}

// LD Instruction
// Load the value of 16-bits direct in 16-bits register DE

void CPU::Disasm::Dis0x11(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(++cpu->pc);
  cpu->de = (tmp << 8) + Engine::RAM::GetByte(++cpu->pc);
  cpu->de = (cpu->de >> 8) | (cpu->de << 8);
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits register A at the address pointed by 16-bits register DE

void CPU::Disasm::Dis0x12(CPU::Z80 *cpu) {
  Engine::RAM::SetByte(cpu->de, (cpu->af >> 8));
  cpu->pc++;
}

// INC Instruction
// Increment 16-bits register DE

void CPU::Disasm::Dis0x13(CPU::Z80 *cpu) {
  cpu->de++;
  cpu->pc++;
}

// INC Instruction
// Increment 8-bits register D

void CPU::Disasm::Dis0x14(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de >> 8) + 1;
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
  cpu->pc++;
}

// DEC Instruction
// Decrement 8-bits register D

void CPU::Disasm::Dis0x15(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de >> 8) - 1;
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits direct in 8-bits register D

void CPU::Disasm::Dis0x16(CPU::Z80 *cpu) {
  cpu->de = (Engine::RAM::GetByte(++cpu->pc) << 8) + (cpu->de & 0xFF);
  cpu->pc++;
}

// RLA Instruction
// TODO ????

void CPU::Disasm::Dis0x17(CPU::Z80 *cpu) {
  cpu->pc++;
}

// JR Instruction
// TODO ????

void CPU::Disasm::Dis0x18(CPU::Z80 *cpu) {
  cpu->pc++;
}

// ADD Instruction
// Add the value of 16-bits register DE to 16-bits register HL

void CPU::Disasm::Dis0x19(CPU::Z80 *cpu) {
  cpu->hl += cpu->de;
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits direct at the address pointed by 16-bits register DE in 8-bits register A

void CPU::Disasm::Dis0x1A(CPU::Z80 *cpu) {
  cpu->af = (Engine::RAM::GetByte(cpu->de) << 8) + (cpu->af & 0xFF);
  cpu->pc++;
}

// DEC Instruction
// Decrement 16-bits register DE

void CPU::Disasm::Dis0x1B(CPU::Z80 *cpu) {
  cpu->de--;
  cpu->pc++;
}

// INC Instruction
// Increment the value of 8-bits register E

void CPU::Disasm::Dis0x1C(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de & 0xFF) + 1;
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
  cpu->pc++;
}

// DEC Instruction
// Decrement 8-bits register E

void CPU::Disasm::Dis0x1D(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de & 0xFF) - 1;
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits direct in 8-bits register E

void CPU::Disasm::Dis0x1E(CPU::Z80 *cpu) {
  cpu->de = ((cpu->de >> 8) << 8) + Engine::RAM::GetByte(++cpu->pc);
  cpu->pc++;
}

// RRA Instruction
// TODO ????

void CPU::Disasm::Dis0x1F(CPU::Z80 *cpu) {
  cpu->pc++;
}

// JR Instruction
// TODO ????

void CPU::Disasm::Dis0x20(CPU::Z80 *cpu) {
  cpu->pc++;
}

// LD Instruction
// Load the value of 16-bits direct in 16-bits register HL

void CPU::Disasm::Dis0x21(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(++cpu->pc);
  cpu->hl = (tmp << 8) + Engine::RAM::GetByte(++cpu->pc);
  cpu->hl = (cpu->hl >> 8) | (cpu->hl << 8);
  cpu->pc++;
}

// LD+ Instruction
// Load the value of 8-bits register A at the address pointed by 16-bits register HL
// Increment the value of 16-bits register HL

void CPU::Disasm::Dis0x22(CPU::Z80 *cpu) {
  Engine::RAM::SetByte(cpu->hl, (cpu->af >> 8));
  cpu->hl++;
  cpu->pc++;
}

// INC Instruction
// Increment the value of 16-bits register HL

void CPU::Disasm::Dis0x23(CPU::Z80 *cpu) {
  cpu->hl++;
  cpu->pc++;
}

// INC Instruction
// Increment the value of 8-bits register H

void CPU::Disasm::Dis0x24(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl >> 8) + 1;
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
  cpu->pc++;
}

// DEC Instruction
// Decrement the value of 8-bits register H

void CPU::Disasm::Dis0x25(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl >> 8) - 1;
  cpu->hl = (tmp << 8) + (cpu->hl & 0XFF);
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits direct in 8-bits register H

void CPU::Disasm::Dis0x26(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(++cpu->pc);
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
  cpu->pc++;
}

// DAA Instruction
// TODO ????

void CPU::Disasm::Dis0x27(CPU::Z80 *cpu) {
  cpu->pc++;
}

// JR Z Instruction
// TODO ????

void CPU::Disasm::Dis0x28(CPU::Z80 *cpu) {
  cpu->pc++;
}

// ADD Instruction
// Add the value of 16-bits register HL to 16-bits register HL

void CPU::Disasm::Dis0x29(CPU::Z80 *cpu) {
  cpu->hl += cpu->hl;
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits direct at the address pointed by 16-bits register HL in 8-bits register A
// Increment the value of 16-bits register HL

void CPU::Disasm::Dis0x2A(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af >> 8);
  tmp = Engine::RAM::GetByte(cpu->hl);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
  cpu->hl++;
  cpu->pc++;
}

// DEC Instruction
// Decrement the value of 16-bits register HL

void CPU::Disasm::Dis0x2B(CPU::Z80 *cpu) {
  cpu->hl--;
  cpu->pc++;
}

// INC Instruction
// Increment the value of 8-bits register L

void CPU::Disasm::Dis0x2C(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl & 0xFF) + 1;
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
  cpu->pc++;
}

// DEC Instruction
// Decrement the value of 8-bits register L

void CPU::Disasm::Dis0x2D(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl & 0xFF) - 1;
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits direct in 8-bits register L

void CPU::Disasm::Dis0x2E(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(++cpu->pc);
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
  cpu->pc++;
}

// CPL Instruction
// Flips all bits of 8-bits register A

void CPU::Disasm::Dis0x2F(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = ~(cpu->af >> 8);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
  cpu->pc++;
}
