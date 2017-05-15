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

// JRNZ Instruction
// TODO ????

void CPU::Disasm::Dis0x30(CPU::Z80 *cpu) {
  cpu->pc++;
}

// LD Instruction
// Load the value of 16bits direct in 16-bits register SP

void CPU::Disasm::Dis0x31(CPU::Z80 *cpu) {
  uint16_t tmp;

  tmp = (Engine::RAM::GetByte(++cpu->pc) << 8);
  tmp += Engine::RAM::GetByte(++cpu->pc);
  cpu->sp = (tmp >> 8) | (tmp << 8);
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits register A at the address pointed by 16-bits register HL
// Decrement HL

void CPU::Disasm::Dis0x32(CPU::Z80 *cpu) {
  Engine::RAM::SetByte(cpu->hl, (cpu->af >> 8));
  cpu->hl--;
  cpu->pc++;
}

// INC Instruction
// Increment the value of 16-bits register SP

void CPU::Disasm::Dis0x33(CPU::Z80 *cpu) {
  cpu->sp++;
  cpu->pc++;
}

// INC Instruction
// Increment the value of 8-bits direct at the address pointed by HL

void CPU::Disasm::Dis0x34(CPU::Z80 *cpu) {
  Engine::RAM::SetByte(cpu->hl, Engine::RAM::GetByte(cpu->hl) + 1);
  cpu->pc++;
}

// DEC Instruction
// Decrement the value of 8-bits direct at the address pointed by HL

void CPU::Disasm::Dis0x35(CPU::Z80 *cpu) {
  Engine::RAM::SetByte(cpu->hl, Engine::RAM::GetByte(cpu->hl) - 1);
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits direct to the address pointed by HL

void CPU::Disasm::Dis0x36(CPU::Z80 *cpu) {
  Engine::RAM::SetByte(cpu->hl, Engine::RAM::GetByte(++cpu->pc));
  cpu->pc++;
}

// SCF Instruction
// TODO ????

void CPU::Disasm::Dis0x37(CPU::Z80 *cpu) {
  cpu->pc++;
}

// JRC Instruction
// TODO ????

void CPU::Disasm::Dis0x38(CPU::Z80 *cpu) {
  cpu->pc++;
}

// ADD Instruction
// Add the value of 16-bits register SP to the value of 16-bits register HL
// Store the result in HL

void CPU::Disasm::Dis0x39(CPU::Z80 *cpu) {
  cpu->hl += cpu->sp;
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits direct pointed by 16-bits register HL in 8-bits register A
// Decrement HL

void CPU::Disasm::Dis0x3A(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->hl);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
  cpu->hl--;
  cpu->pc++;
}

// DEC Instruction
// Decrement the value of 16-bits register SP

void CPU::Disasm::Dis0x3B(CPU::Z80 *cpu) {
  cpu->sp--;
  cpu->pc++;
}

// INC Instruction
// Increment the value of 8-bits register A

void CPU::Disasm::Dis0x3C(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af >> 8) + 1;
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
  cpu->pc++;
}

// DEC Instruction
// Decrement the value of 8-bits register

void CPU::Disasm::Dis0x3D(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af >> 8) - 1;
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits direct in 8-bits register A

void CPU::Disasm::Dis0x3E(CPU::Z80 *cpu) {
  cpu->af = (Engine::RAM::GetByte(++cpu->pc) << 8) + (cpu->af & 0xFF);
  cpu->pc++;
}

// CCF Instruction
// TODO ????

void CPU::Disasm::Dis0x3F(CPU::Z80 *cpu) {
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits register B in 8-bits register B

void CPU::Disasm::Dis0x40(CPU::Z80 *cpu) {
  // Nothing to do ?
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits register C in 8-bits register B

void CPU::Disasm::Dis0x41(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->bc & 0xFF) << 8) + (cpu->bc & 0xFF);
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits register D in 8-bits register B

void CPU::Disasm::Dis0x42(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->de >> 8) << 8) + (cpu->bc & 0xFF);
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits register E in 8-bits register B

void CPU::Disasm::Dis0x43(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->de & 0xFF) << 8) + (cpu->bc & 0xFF);
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits register H in 8-bits register B

void CPU::Disasm::Dis0x44(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->hl >> 8) << 8) + (cpu->bc & 0xFF);
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits register L in 8-bits register B

void CPU::Disasm::Dis0x45(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->hl & 0xFF) << 8) + (cpu->bc & 0xFF);
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits direct located by the address pointed by HL in 8-bits register B

void CPU::Disasm::Dis0x46(CPU::Z80 *cpu) {
  cpu->bc = (Engine::RAM::GetByte(cpu->hl) << 8) + (cpu->bc & 0xFF);
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits register A in 8-bits register B

void CPU::Disasm::Dis0x47(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->af >> 8) << 8) + (cpu->bc & 0xFF);
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits register B in 8-bits register C

void CPU::Disasm::Dis0x48(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->bc >> 8) << 8) + (cpu->bc >> 8);
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits register C in 8-bits register C

void CPU::Disasm::Dis0x49(CPU::Z80 *cpu) {
  // Nothing to do ?
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits register D in 8-bits register C

void CPU::Disasm::Dis0x4A(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->bc >> 8) << 8) + (cpu->de >> 8);
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits register E in 8-bits register C

void CPU::Disasm::Dis0x4B(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->bc >> 8) << 8) + (cpu->de & 0xFF);
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits register H in 8-bits register C

void CPU::Disasm::Dis0x4C(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->bc >> 8) << 8) + (cpu->hl >> 8);
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits register L in 8-bits register C

void CPU::Disasm::Dis0x4D(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->bc >> 8) << 8) + (cpu->hl & 0xFF);
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits direct located by the address of 16-bits register HL in 8-bits register C

void CPU::Disasm::Dis0x4E(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->bc >> 8) << 8) + Engine::RAM::GetByte(cpu->hl);
  cpu->pc++;
}

// LD Instruction
// Load the value of 8-bits register A in 8-bits register C

void CPU::Disasm::Dis0x4F(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->bc >> 8) << 8) + (cpu->af >> 8);
  cpu->pc++;
}

void CPU::Disasm::Dis0x50(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x51(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x52(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x53(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x54(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x55(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x56(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x57(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x58(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x59(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x5A(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x5B(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x5C(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x5D(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x5E(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x5F(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x60(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x61(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x62(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x63(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x64(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x65(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x66(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x67(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x68(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x69(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x6A(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x6B(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x6C(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x6D(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x6E(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x6F(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x70(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x71(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x72(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x73(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x74(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x75(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x76(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x77(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x78(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x79(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x7A(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x7B(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x7C(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x7D(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x7E(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x7F(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x80(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x81(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x82(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x83(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x84(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x85(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x86(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x87(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x88(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x89(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x8A(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x8B(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x8C(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x8D(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x8E(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x8F(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x90(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x91(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x92(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x93(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x94(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x95(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x96(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x97(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x98(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x99(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x9A(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x9B(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x9C(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x9D(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x9E(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0x9F(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xA0(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xA1(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xA2(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xA3(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xA4(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xA5(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xA6(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xA7(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xA8(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xA9(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xAA(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xAB(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xAC(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xAD(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xAE(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xAF(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xB0(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xB1(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xB2(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xB3(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xB4(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xB5(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xB6(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xB7(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xB8(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xB9(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xBA(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xBB(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xBC(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xBD(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xBE(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xBF(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xC0(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xC1(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xC2(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xC3(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xC4(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xC5(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xC6(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xC7(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xC8(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xC9(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xCA(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xCB(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xCC(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xCD(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xCE(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xCF(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xD0(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xD1(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xD2(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xD3(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xD4(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xD5(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xD6(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xD7(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xD8(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xD9(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xDA(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xDB(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xDC(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xDD(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xDE(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xDF(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xE0(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xE1(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xE2(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xE3(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xE4(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xE5(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xE6(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xE7(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xE8(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xE9(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xEA(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xEB(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xEC(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xED(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xEE(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xEF(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xF0(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xF1(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xF2(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xF3(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xF4(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xF5(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xF6(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xF7(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xF8(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xF9(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xFA(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xFB(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xFC(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xFD(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xFE(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::Dis0xFF(CPU::Z80 *cpu) {
  cpu->pc++;
}


/* CB Extension Instructions */


void CPU::Disasm::DisCB0x00(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x01(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x02(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x03(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x04(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x05(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x06(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x07(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x08(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x09(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x0A(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x0B(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x0C(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x0D(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x0E(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x0F(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x10(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x11(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x12(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x13(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x14(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x15(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x16(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x17(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x18(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x19(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x1A(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x1B(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x1C(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x1D(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x1E(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x1F(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x20(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x21(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x22(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x23(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x24(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x25(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x26(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x27(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x28(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x29(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x2A(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x2B(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x2C(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x2D(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x2E(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x2F(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x30(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x31(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x32(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x33(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x34(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x35(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x36(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x37(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x38(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x39(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x3A(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x3B(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x3C(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x3D(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x3E(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x3F(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x40(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x41(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x42(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x43(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x44(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x45(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x46(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x47(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x48(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x49(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x4A(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x4B(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x4C(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x4D(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x4E(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x4F(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x50(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x51(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x52(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x53(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x54(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x55(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x56(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x57(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x58(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x59(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x5A(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x5B(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x5C(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x5D(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x5E(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x5F(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x60(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x61(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x62(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x63(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x64(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x65(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x66(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x67(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x68(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x69(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x6A(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x6B(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x6C(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x6D(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x6E(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x6F(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x70(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x71(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x72(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x73(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x74(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x75(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x76(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x77(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x78(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x79(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x7A(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x7B(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x7C(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x7D(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x7E(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x7F(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x80(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x81(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x82(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x83(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x84(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x85(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x86(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x87(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x88(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x89(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x8A(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x8B(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x8C(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x8D(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x8E(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x8F(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x90(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x91(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x92(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x93(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x94(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x95(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x96(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x97(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x98(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x99(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x9A(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x9B(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x9C(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x9D(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x9E(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0x9F(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xA0(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xA1(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xA2(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xA3(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xA4(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xA5(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xA6(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xA7(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xA8(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xA9(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xAA(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xAB(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xAC(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xAD(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xAE(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xAF(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xB0(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xB1(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xB2(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xB3(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xB4(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xB5(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xB6(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xB7(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xB8(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xB9(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xBA(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xBB(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xBC(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xBD(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xBE(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xBF(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xC0(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xC1(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xC2(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xC3(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xC4(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xC5(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xC6(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xC7(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xC8(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xC9(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xCA(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xCB(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xCC(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xCD(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xCE(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xCF(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xD0(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xD1(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xD2(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xD3(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xD4(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xD5(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xD6(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xD7(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xD8(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xD9(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xDA(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xDB(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xDC(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xDD(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xDE(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xDF(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xE0(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xE1(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xE2(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xE3(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xE4(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xE5(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xE6(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xE7(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xE8(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xE9(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xEA(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xEB(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xEC(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xED(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xEE(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xEF(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xF0(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xF1(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xF2(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xF3(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xF4(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xF5(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xF6(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xF7(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xF8(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xF9(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xFA(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xFB(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xFC(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xFD(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xFE(CPU::Z80 *cpu) {
  cpu->pc++;
}

void CPU::Disasm::DisCB0xFF(CPU::Z80 *cpu) {
  cpu->pc++;
}
