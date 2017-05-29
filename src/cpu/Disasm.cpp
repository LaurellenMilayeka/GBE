#include <iomanip>
#include "Opcodes.hpp"
#include "Disasm.hpp"
#include <bitset>

void RegDump(CPU::Z80 *);

// NOP Instruction
// Do nothing...
// Wait 4 cycles

void CPU::Disasm::Dis0x00(CPU::Z80 *) {

}

// LD Instruction
// Load the value of 16-bits direct in 16-bits register BC

void CPU::Disasm::Dis0x01(CPU::Z80 *cpu) {
  uint16_t tmp;

  tmp = Engine::RAM::GetByte(cpu->pc + 1);
  tmp <<= 8;
  tmp += Engine::RAM::GetByte(cpu->pc + 2);
  tmp = (tmp >> 8) | (tmp << 8);  
  cpu->bc = tmp;
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
  uint8_t flags;
  
  tmp = (cpu->bc >> 8) + 1;
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if (((((cpu->bc >> 8) & 0xF) + (1 & 0xF)) & 0x10) == 0x10) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if (!tmp) {
    flags |= 1 << 7;
  } else {
    flags &= ~(1 << 7);
  }
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// DEC Instruction
// Decrement 8-bits register B

void CPU::Disasm::Dis0x05(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->bc >> 8) - 1;
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if (((((cpu->bc >> 8) & 0xF) - (1 & 0xF))) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if (!tmp) {
    flags |= 1 << 7;
  } else {
    flags &= ~(1 << 7);
  }
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// LD Instruction
// Load the value of 8-bits direct in 8-bits register B

void CPU::Disasm::Dis0x06(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = cpu->bc >> 8;
  tmp = Engine::RAM::GetByte(cpu->pc + 1);
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
}

// RLCA Instruction
// Rotate bits left and place bit 7 of 8-bits register A in Carry

void CPU::Disasm::Dis0x07(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->af >> 8;
  flags = (cpu->af & 0xFF);
  tmp = (tmp << 1);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(0 << 6);
  flags &= ~(0 << 5);
  if (((tmp >> 0) & 1) == 0) {
    flags &= ~(1 << 4);
  } else {
    flags |= (1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// LD Instruction
// Load the value of 16-bits register SP at the address pointed by 16-bits direct

void CPU::Disasm::Dis0x08(CPU::Z80 *cpu) {
  uint16_t address;
  
  address = Engine::RAM::GetByte(cpu->pc + 1);
  address = address << 8;
  address += Engine::RAM::GetByte(cpu->pc + 2);
  address = (address >> 8) | (address << 8);
  Engine::RAM::SetByte(address, (cpu->sp & 0xFF));
  Engine::RAM::SetByte(address + 1, (cpu->sp >> 8));
}

// ADD Instruction
// Add 16-bits register BC to 16-bits register HL

void CPU::Disasm::Dis0x09(CPU::Z80 *cpu) {
  uint8_t flags;
  
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if (((((cpu->hl >> 8) & 0xF) + ((cpu->bc >> 8) & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (((((cpu->hl >> 8) & 0xFF) + ((cpu->bc >> 8) & 0xFF)) & 0x100) == 0x100) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->hl += cpu->bc;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
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
  uint8_t flags;
  
  tmp = (cpu->bc & 0xFF) + 1;
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if (((((cpu->bc & 0xFF) & 0xF) + (1 & 0xF)) & 0x10) == 0x10) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if (!tmp) {
    flags |= 1 << 7;
  } else {
    flags &= ~(1 << 7);
  }
  cpu->bc = ((cpu->bc >> 8) << 8) + (tmp & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// DEC Instruction
// Decrement 8-bits register C

void CPU::Disasm::Dis0x0D(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = (cpu->bc & 0xFF) - 1;
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if ((((cpu->bc & 0xFF) & 0xF) - (1 & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if (!tmp) {
    flags |= 1 << 7;
  } else {
    flags &= ~(1 << 7);
  }
  cpu->bc = ((cpu->bc >> 8) << 8) + (tmp & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// LD Instruction
// Load the value of 8-bits direct in 8-bits register C

void CPU::Disasm::Dis0x0E(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->pc + 1);
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
}

// RRCA Instruction
// Rotate 8-bits register A bits to the right

void CPU::Disasm::Dis0x0F(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->af >> 8;
  flags = (cpu->af & 0xFF);
  tmp = (tmp >> 1) | (tmp << (sizeof(uint8_t)*8 - 1));
  flags &= ~(0 << 7);
  flags &= ~(0 << 6);
  flags &= ~(0 << 5);
  if (((tmp >> 7) & 1) == 0) {
    flags &= ~(1 << 4);
  } else {
    flags |= (1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// STOP Instruction
// Halt the program execution until a button is pressed

void CPU::Disasm::Dis0x10(CPU::Z80 *) {

}

// LD Instruction
// Load the value of 16-bits direct in 16-bits register DE

void CPU::Disasm::Dis0x11(CPU::Z80 *cpu) {
  uint16_t tmp;

  tmp = Engine::RAM::GetByte(cpu->pc + 1);
  tmp = (tmp << 8) + Engine::RAM::GetByte(cpu->pc + 2);
  tmp = (tmp >> 8) | (tmp << 8);
  cpu->de = tmp;
}

// LD Instruction
// Load the value of 8-bits register A at the address pointed by 16-bits register DE

void CPU::Disasm::Dis0x12(CPU::Z80 *cpu) {
  Engine::RAM::SetByte(cpu->de, (cpu->af >> 8));
}

// INC Instruction
// Increment 16-bits register DE

void CPU::Disasm::Dis0x13(CPU::Z80 *cpu) {
  cpu->de++;
}

// INC Instruction
// Increment 8-bits register D

void CPU::Disasm::Dis0x14(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->de >> 8) + 1;
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if (((((cpu->de >> 8) & 0xF) + (1 & 0xF)) & 0x10) == 0x10) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if (!tmp) {
    flags |= 1 << 7;
  } else {
    flags &= ~(1 << 7);
  }
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// DEC Instruction
// Decrement 8-bits register D

void CPU::Disasm::Dis0x15(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->de >> 8) - 1;
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if ((((cpu->de >> 8) & 0xF) - (1 & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if (!tmp) {
    flags |= 1 << 7;
  } else {
    flags &= ~(1 << 7);
  }
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// LD Instruction
// Load the value of 8-bits direct in 8-bits register D

void CPU::Disasm::Dis0x16(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->pc + 1);
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
}

// RLA Instruction
// Rotate 8-bits register A left

void CPU::Disasm::Dis0x17(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->af >> 8;
  tmp = (tmp << 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if (((flags >> 4) & 1) == 1) {
    tmp |= (1 << 0);
  } else {
    tmp &= ~(1 << 0);
  }
  if ((((cpu->af >> 8) >> 7) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// JR Instruction
// Relative jump to 16-bits register PC + 8-bits direct

void CPU::Disasm::Dis0x18(CPU::Z80 *cpu) {
  char i;

  i = Engine::RAM::GetByte(cpu->pc + 1);
  cpu->pc += i;
}

// ADD Instruction
// Add the value of 16-bits register DE to 16-bits register HL

void CPU::Disasm::Dis0x19(CPU::Z80 *cpu) {
  uint8_t flags;
  
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if (((((cpu->hl >> 8) & 0xF) + ((cpu->de >> 8) & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (((((cpu->hl >> 8) & 0xFF) + ((cpu->de >> 8) & 0xFF)) & 0x100) == 0x100) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->hl += cpu->de;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// LD Instruction
// Load the value of 8-bits direct at the address pointed by 16-bits register DE in 8-bits register A

void CPU::Disasm::Dis0x1A(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->de);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
}

// DEC Instruction
// Decrement 16-bits register DE

void CPU::Disasm::Dis0x1B(CPU::Z80 *cpu) {
  cpu->de--;
}

// INC Instruction
// Increment the value of 8-bits register E

void CPU::Disasm::Dis0x1C(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->de & 0xFF) + 1;
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if (((((cpu->de & 0xFF) & 0xF) + (1 & 0xF)) & 0x10) == 0x10) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if (!tmp) {
    flags |= 1 << 7;
  } else {
    flags &= ~(1 << 7);
  }
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// DEC Instruction
// Decrement 8-bits register E

void CPU::Disasm::Dis0x1D(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->de & 0xFF) - 1;
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if ((((cpu->de & 0xFF) & 0xF) - (1 & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if (!tmp) {
    flags |= 1 << 7;
  } else {
    flags &= ~(1 << 7);
  }
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// LD Instruction
// Load the value of 8-bits direct in 8-bits register E

void CPU::Disasm::Dis0x1E(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->pc + 1);
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
}

// RRA Instruction
// Rotate 8-bits register to the right

void CPU::Disasm::Dis0x1F(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->af >> 8;
  tmp = (tmp >> 1) | (tmp << (sizeof(uint8_t)*8 - 1));
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 7);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if ((((cpu->af >> 8) >> 0) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  if (((flags >> 4) & 1) == 1) {
    tmp |= (1 << 7);
  } else {
    tmp &= ~(1 << 0);
  }
  cpu->af = (tmp << 8) + flags;
}

// JR Instruction
// Relative jump to the address 16-bits register + 8-bits direct if Zero flag == 0

void CPU::Disasm::Dis0x20(CPU::Z80 *cpu) {
  char i;

  i = (char)Engine::RAM::GetByte(cpu->pc + 1);
  if ((((cpu->af & 0xFF) >> 7) & 1) != 1) {
    cpu->pc += i;
    //cpu->pc -= 2;
  }
}

// LD Instruction
// Load the value of 16-bits direct in 16-bits register HL

void CPU::Disasm::Dis0x21(CPU::Z80 *cpu) {
  uint16_t tmp;

  tmp = Engine::RAM::GetByte(cpu->pc + 1);
  tmp = (tmp << 8) + Engine::RAM::GetByte(cpu->pc + 2);
  tmp = (tmp >> 8) | (tmp << 8);
  cpu->hl = tmp;
}

// LD+ Instruction
// Load the value of 8-bits register A at the address pointed by 16-bits register HL
// Increment the value of 16-bits register HL

void CPU::Disasm::Dis0x22(CPU::Z80 *cpu) {
  Engine::RAM::SetByte(cpu->hl, (cpu->af >> 8));
  cpu->hl++;
}

// INC Instruction
// Increment the value of 16-bits register HL

void CPU::Disasm::Dis0x23(CPU::Z80 *cpu) {
  cpu->hl++;
}

// INC Instruction
// Increment the value of 8-bits register H

void CPU::Disasm::Dis0x24(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->hl >> 8) + 1;
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if (((((cpu->hl >> 8) & 0xF) + (1 & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// DEC Instruction
// Decrement the value of 8-bits register H

void CPU::Disasm::Dis0x25(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->hl >> 8) - 1;
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if ((((cpu->hl & 0xFF) & 0xF) - (1 & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if (!tmp) {
    flags |= 1 << 7;
  } else {
    flags &= ~(1 << 7);
  }
  cpu->hl = (tmp << 8) + (cpu->hl & 0XFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// LD Instruction
// Load the value of 8-bits direct in 8-bits register H

void CPU::Disasm::Dis0x26(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->pc + 1);
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
}

// DAA Instruction
// Decimal adjust 8-bits register A

void CPU::Disasm::Dis0x27(CPU::Z80 *cpu) {
  uint8_t flags;
  bool res_c = true;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 5);
  if (((cpu->af >> 8) & 0xF) > 0x09) {
    cpu->af = ((cpu->af >> 8) + 0x06) + (cpu->af & 0xFF);
  } else if (((cpu->af >> 8) & 0xF0) > 0x09) {
    cpu->af = ((cpu->af >> 8) + 0x60) + (cpu->af & 0xFF);
    flags |= (1 << 4);
    res_c = false;
  }
  if (!(cpu->af >> 8)) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if (res_c) {
    flags &= ~(1 << 4);
  }
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// JR Z Instruction
// Relative jump to the address 16-bits register PC + 8-bits direct if Zero flag = 1 

void CPU::Disasm::Dis0x28(CPU::Z80 *cpu) {
  char i;

  i = Engine::RAM::GetByte(cpu->pc + 1);
  if ((((cpu->af & 0xFF) >> 7) & 1) == 1) {
    cpu->pc += i;
  }
}

// ADD Instruction
// Add the value of 16-bits register HL to 16-bits register HL

void CPU::Disasm::Dis0x29(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if (((((cpu->hl >> 8) & 0xF) + ((cpu->hl >> 8) & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (((((cpu->hl >> 8) & 0xFF) + ((cpu->hl >> 8) & 0xFF)) & 0x100) == 0x100) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->hl += cpu->hl;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
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
}

// DEC Instruction
// Decrement the value of 16-bits register HL

void CPU::Disasm::Dis0x2B(CPU::Z80 *cpu) {
  cpu->hl--;
}

// INC Instruction
// Increment the value of 8-bits register L

void CPU::Disasm::Dis0x2C(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->hl & 0xFF) + 1;
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if (((((cpu->hl & 0xFF) & 0xF) + (1 & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// DEC Instruction
// Decrement the value of 8-bits register L

void CPU::Disasm::Dis0x2D(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->hl & 0xFF) - 1;
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if ((((cpu->hl & 0xFF) & 0xF) - (1 & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if (!tmp) {
    flags |= 1 << 7;
  } else {
    flags &= ~(1 << 7);
  }
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// LD Instruction
// Load the value of 8-bits direct in 8-bits register L

void CPU::Disasm::Dis0x2E(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->pc + 1);
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
}

// CPL Instruction
// Flips all bits of 8-bits register A

void CPU::Disasm::Dis0x2F(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = ~(cpu->af >> 8);
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  flags |= (1 << 5);
  cpu->af = (tmp << 8) + flags;
}

// JRNC Instruction
// Relative jump to the address 16-bits register PC + 8-bits direct if Carry flag = 0

void CPU::Disasm::Dis0x30(CPU::Z80 *cpu) {
  char i;

  i = Engine::RAM::GetByte(cpu->pc + 1);
  if ((((cpu->af & 0xFF) >> 4) & 1) != 1) {
    cpu->pc += i;
  }
}

// LD Instruction
// Load the value of 16bits direct in 16-bits register SP

void CPU::Disasm::Dis0x31(CPU::Z80 *cpu) {
  uint16_t tmp;

  tmp = (Engine::RAM::GetByte(cpu->pc + 1) << 8);
  tmp += Engine::RAM::GetByte(cpu->pc + 2);
  cpu->sp = (tmp >> 8) | (tmp << 8);
}

// LD Instruction
// Load the value of 8-bits register A at the address pointed by 16-bits register HL
// Decrement HL

void CPU::Disasm::Dis0x32(CPU::Z80 *cpu) {
  Engine::RAM::SetByte(cpu->hl, (cpu->af >> 8));
  cpu->hl--;
}

// INC Instruction
// Increment the value of 16-bits register SP

void CPU::Disasm::Dis0x33(CPU::Z80 *cpu) {
  cpu->sp++;
}

// INC Instruction
// Increment the value of 8-bits direct at the address pointed by HL

void CPU::Disasm::Dis0x34(CPU::Z80 *cpu) {
  uint8_t flags;
  
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if ((((Engine::RAM::GetByte(cpu->hl) & 0xF) + (1 & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  Engine::RAM::SetByte(cpu->hl, Engine::RAM::GetByte(cpu->hl) + 1);
  if (!Engine::RAM::GetByte(cpu->hl)) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// DEC Instruction
// Decrement the value of 8-bits direct at the address pointed by HL

void CPU::Disasm::Dis0x35(CPU::Z80 *cpu) {
  uint8_t flags;
  
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if (((Engine::RAM::GetByte(cpu->hl) & 0xF) - (1 & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  Engine::RAM::SetByte(cpu->hl, Engine::RAM::GetByte(cpu->hl) - 1);
  if (!Engine::RAM::GetByte(cpu->hl)) {
    flags |= 1 << 7;
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// LD Instruction
// Load the value of 8-bits direct to the address pointed by HL

void CPU::Disasm::Dis0x36(CPU::Z80 *cpu) {
  Engine::RAM::SetByte(cpu->hl, Engine::RAM::GetByte(cpu->pc + 1));
}

// SCF Instruction
// Set Carry flag

void CPU::Disasm::Dis0x37(CPU::Z80 *cpu) {
  uint8_t tmp;
  
  tmp = (cpu->af & 0xFF);
  tmp |= 1 << 4;
  tmp &= ~(1 << 5);
  tmp &= ~(1 << 6);
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// JRC Instruction
// Relative jump to the address 16-bits register PC + 8-bits direct if Carry flag = 1

void CPU::Disasm::Dis0x38(CPU::Z80 *cpu) {
  char i;

  i = Engine::RAM::GetByte(cpu->pc + 1);
  if ((((cpu->af & 0xFF) >> 4) & 1) == 1) {
    cpu->pc += i;
  }
}

// ADD Instruction
// Add the value of 16-bits register SP to the value of 16-bits register HL
// Store the result in HL

void CPU::Disasm::Dis0x39(CPU::Z80 *cpu) {
  uint8_t flags;
  
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if (((((cpu->hl >> 8) & 0xF) + ((cpu->sp >> 8) & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (((((cpu->hl >> 8) & 0xFF) + ((cpu->sp >> 8) & 0xFF)) & 0x100) == 0x100) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->hl += cpu->sp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// LD Instruction
// Load the value of 8-bits direct pointed by 16-bits register HL in 8-bits register A
// Decrement HL

void CPU::Disasm::Dis0x3A(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->hl);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
  cpu->hl--;
}

// DEC Instruction
// Decrement the value of 16-bits register SP

void CPU::Disasm::Dis0x3B(CPU::Z80 *cpu) {
  cpu->sp--;
}

// INC Instruction
// Increment the value of 8-bits register A

void CPU::Disasm::Dis0x3C(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->af >> 8) + 1;
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if (((((cpu->af >> 8) & 0xF) + (1 & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (tmp << 8) + flags;
}

// DEC Instruction
// Decrement the value of 8-bits register A

void CPU::Disasm::Dis0x3D(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->af >> 8) - 1;
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if ((((cpu->af >> 8) & 0xF) - (1 & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if (!tmp) {
    flags |= 1 << 7;
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (tmp << 8) + flags;
}

// LD Instruction
// Load the value of 8-bits direct in 8-bits register A

void CPU::Disasm::Dis0x3E(CPU::Z80 *cpu) {
  cpu->af = (Engine::RAM::GetByte(cpu->pc + 1) << 8) + (cpu->af & 0xFF);
}

// CCF Instruction
// Invert carry flag

void CPU::Disasm::Dis0x3F(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  tmp &= ~(1 << 5);
  tmp &= ~(1 << 6);
  if ((((cpu->af & 0xFF) >> 4) & 1) == 1) {
    tmp &= ~(1 << 4);
  } else {
    tmp |= (1 << 4);
  }
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// LD Instruction
// Load the value of 8-bits register B in 8-bits register B

void CPU::Disasm::Dis0x40(CPU::Z80 *) {
  // Nothing to do ?
}

// LD Instruction
// Load the value of 8-bits register C in 8-bits register B

void CPU::Disasm::Dis0x41(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->bc & 0xFF) << 8) + (cpu->bc & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register D in 8-bits register B

void CPU::Disasm::Dis0x42(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->de >> 8) << 8) + (cpu->bc & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register E in 8-bits register B

void CPU::Disasm::Dis0x43(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->de & 0xFF) << 8) + (cpu->bc & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register H in 8-bits register B

void CPU::Disasm::Dis0x44(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->hl >> 8) << 8) + (cpu->bc & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register L in 8-bits register B

void CPU::Disasm::Dis0x45(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->hl & 0xFF) << 8) + (cpu->bc & 0xFF);
}

// LD Instruction
// Load the value of 8-bits direct located by the address pointed by HL in 8-bits register B

void CPU::Disasm::Dis0x46(CPU::Z80 *cpu) {
  cpu->bc = (Engine::RAM::GetByte(cpu->hl) << 8) + (cpu->bc & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register A in 8-bits register B

void CPU::Disasm::Dis0x47(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->af >> 8) << 8) + (cpu->bc & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register B in 8-bits register C

void CPU::Disasm::Dis0x48(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->bc >> 8) << 8) + (cpu->bc >> 8);
}

// LD Instruction
// Load the value of 8-bits register C in 8-bits register C

void CPU::Disasm::Dis0x49(CPU::Z80 *) {
  // Nothing to do ?
}

// LD Instruction
// Load the value of 8-bits register D in 8-bits register C

void CPU::Disasm::Dis0x4A(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->bc >> 8) << 8) + (cpu->de >> 8);
}

// LD Instruction
// Load the value of 8-bits register E in 8-bits register C

void CPU::Disasm::Dis0x4B(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->bc >> 8) << 8) + (cpu->de & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register H in 8-bits register C

void CPU::Disasm::Dis0x4C(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->bc >> 8) << 8) + (cpu->hl >> 8);
}

// LD Instruction
// Load the value of 8-bits register L in 8-bits register C

void CPU::Disasm::Dis0x4D(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->bc >> 8) << 8) + (cpu->hl & 0xFF);
}

// LD Instruction
// Load the value of 8-bits direct located by the address of 16-bits register HL in 8-bits register C

void CPU::Disasm::Dis0x4E(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->bc >> 8) << 8) + Engine::RAM::GetByte(cpu->hl);
}

// LD Instruction
// Load the value of 8-bits register A in 8-bits register C

void CPU::Disasm::Dis0x4F(CPU::Z80 *cpu) {
  cpu->bc = ((cpu->bc >> 8) << 8) + (cpu->af >> 8);
}

// LD Instruction
// Load the value of 8-bits register B in 8-bits register D

void CPU::Disasm::Dis0x50(CPU::Z80 *cpu) {
  cpu->de = ((cpu->bc >> 8) << 8) + (cpu->bc & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register C in 8-bits register D

void CPU::Disasm::Dis0x51(CPU::Z80 *cpu) {
  cpu->de = ((cpu->bc & 0xFF) << 8) + (cpu->de & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register D in 8-bits register D

void CPU::Disasm::Dis0x52(CPU::Z80 *) {
  // Nothing to do ?
}

// LD Instruction
// Load the value of 8-bits register E in 8-bits register D

void CPU::Disasm::Dis0x53(CPU::Z80 *cpu) {
  cpu->de = ((cpu->de & 0xFF) << 8) + (cpu->de & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register H in 8-bits register D

void CPU::Disasm::Dis0x54(CPU::Z80 *cpu) {
  cpu->de = ((cpu->hl >> 8) << 8) + (cpu->de & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register L in 8-bits register D

void CPU::Disasm::Dis0x55(CPU::Z80 *cpu) {
  cpu->de = ((cpu->hl & 0xFF) << 8) + (cpu->de & 0xFF);
}

// LD Instruction
// Load the value of 8-bits direct located at the address pointed by 16-bits register HL in 8-bits register D

void CPU::Disasm::Dis0x56(CPU::Z80 *cpu) {
  cpu->de = (Engine::RAM::GetByte(cpu->hl) << 8) + (cpu->de & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register A in 8-bits register D

void CPU::Disasm::Dis0x57(CPU::Z80 *cpu) {
  cpu->de = ((cpu->af >> 8) << 8) + (cpu->de & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register B in 8-bits register E

void CPU::Disasm::Dis0x58(CPU::Z80 *cpu) {
  cpu->de = ((cpu->de >> 8) << 8) + (cpu->bc >> 8);
}

// LD Instruction
// Load the value of 8-bits register C in 8-bits register E

void CPU::Disasm::Dis0x59(CPU::Z80 *cpu) {
  cpu->de = ((cpu->de >> 8) << 8) + (cpu->bc & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register D in 8-bits register E

void CPU::Disasm::Dis0x5A(CPU::Z80 *cpu) {
  cpu->de = ((cpu->de >> 8) << 8) + (cpu->de >> 8);
}

// LD Instruction
// Load the value of 8-bits register E in 8-bits register E

void CPU::Disasm::Dis0x5B(CPU::Z80 *) {
  // Nothing to do ?
}

// LD Instruction
// Load the value of 8-bits register H in 8-bits register E

void CPU::Disasm::Dis0x5C(CPU::Z80 *cpu) {
  cpu->de = ((cpu->de >> 8) << 8) + (cpu->hl >> 8);
}

// LD Instruction
// Load the value of 8-bits register L in 8-bits register E

void CPU::Disasm::Dis0x5D(CPU::Z80 *cpu) {
  cpu->de = ((cpu->de >> 8) << 8) + (cpu->hl & 0xFF);
}

// LD Instruction
// Load the value of 8-bits direct located at the address pointed by 16-bits register HL in 8-bits register E

void CPU::Disasm::Dis0x5E(CPU::Z80 *cpu) {
  cpu->de = ((cpu->de >> 8) << 8) + Engine::RAM::GetByte(cpu->hl);
}

// LD Instruction
// Load the value of 8-bits register A in 8-bits register E

void CPU::Disasm::Dis0x5F(CPU::Z80 *cpu) {
  cpu->de = ((cpu->de >> 8) << 8) + (cpu->af >> 8);
}

// LD Instruction
// Load the value of 8-bits register B in 8-bits register H

void CPU::Disasm::Dis0x60(CPU::Z80 *cpu) {
  cpu->hl = ((cpu->bc >> 8) << 8) + (cpu->hl & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register C in 8-bits register H

void CPU::Disasm::Dis0x61(CPU::Z80 *cpu) {
  cpu->hl = ((cpu->bc & 0xFF) << 8) + (cpu->hl & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register D in 8-bits register H

void CPU::Disasm::Dis0x62(CPU::Z80 *cpu) {
  cpu->hl = ((cpu->de >> 8) << 8) + (cpu->hl & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register E in 8-bits register H

void CPU::Disasm::Dis0x63(CPU::Z80 *cpu) {
  cpu->hl = ((cpu->de & 0xFF) << 8) + (cpu->hl & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register H in 8-bits register H

void CPU::Disasm::Dis0x64(CPU::Z80 *) {
  // Nothing to do ?
}

// LD Instruction
// Load the value of 8-bits register L in 8-bits register H

void CPU::Disasm::Dis0x65(CPU::Z80 *cpu) {
  cpu->hl = ((cpu->hl & 0xFF) << 8) + (cpu->hl & 0xFF);
}

// LD Instruction
// Load the value of 8-bits direct located at the address pointed by 16-bits register HL in 8-bits register H

void CPU::Disasm::Dis0x66(CPU::Z80 *cpu) {
  cpu->hl = (Engine::RAM::GetByte(cpu->hl) << 8) + (cpu->hl & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register A in 8-bits register H

void CPU::Disasm::Dis0x67(CPU::Z80 *cpu) {
  cpu->hl = ((cpu->af >> 8) << 8) + (cpu->hl & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register B in 8-bits register L

void CPU::Disasm::Dis0x68(CPU::Z80 *cpu) {
  cpu->hl = ((cpu->hl >> 8) << 8) + (cpu->bc >> 8);
}

// LD Instruction
// Load the value of 8-bits register C in 8-bits register L

void CPU::Disasm::Dis0x69(CPU::Z80 *cpu) {
  cpu->hl = ((cpu->hl >> 8) << 8) + (cpu->bc & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register D in 8-bits register L

void CPU::Disasm::Dis0x6A(CPU::Z80 *cpu) {
  cpu->hl = ((cpu->hl >> 8) << 8) + (cpu->de >> 8);
}

// LD Instruction
// Load the value of 8-bits register E in 8-bits register L

void CPU::Disasm::Dis0x6B(CPU::Z80 *cpu) {
  cpu->hl = ((cpu->hl >> 8) << 8) + (cpu->de & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register H in 8-bits register L

void CPU::Disasm::Dis0x6C(CPU::Z80 *cpu) {
  cpu->hl = ((cpu->hl >> 8) << 8) + (cpu->hl >> 8);
}

// LD Instruction
// Load the value of 8-bits register L in 8-bits register L

void CPU::Disasm::Dis0x6D(CPU::Z80 *) {
  // Nothing to do ?
}

// LD Instruction
// Load the value of 8-bits direct located at the address pointed by 16-bits register HL in 8-bits register L

void CPU::Disasm::Dis0x6E(CPU::Z80 *cpu) {
  cpu->hl = ((cpu->hl >> 8) << 8) + Engine::RAM::GetByte(cpu->hl);
}

// LD Instruction
// Load the value of 8-bits register A in 8-bits register L

void CPU::Disasm::Dis0x6F(CPU::Z80 *cpu) {
  cpu->hl = ((cpu->hl >> 8) << 8) + (cpu->af >> 8);
}

// LD Instruction
// Load the value of 8-bits register B at the address pointed by 16-bits register HL

void CPU::Disasm::Dis0x70(CPU::Z80 *cpu) {
  Engine::RAM::SetByte(cpu->hl, (cpu->bc >> 8));
}

// LD Instruction
// Load the value of 8-bits register C at the address pointed by 16-bits register HL

void CPU::Disasm::Dis0x71(CPU::Z80 *cpu) {
  Engine::RAM::SetByte(cpu->hl, (cpu->bc & 0xFF));
}

// LD Instruction
// Load the value of 8-bits register D at the address pointed by 16-bits register HL

void CPU::Disasm::Dis0x72(CPU::Z80 *cpu) {
  Engine::RAM::SetByte(cpu->hl, (cpu->de >> 8));
}

// LD Instruction
// Load the value of 8-bits register E at the address pointed by 16bits register HL

void CPU::Disasm::Dis0x73(CPU::Z80 *cpu) {
  Engine::RAM::SetByte(cpu->hl, (cpu->de & 0xFF));
}

// LD Instruction
// Load the value of 8-bits register H at the address pointed by 16-bits register HL

void CPU::Disasm::Dis0x74(CPU::Z80 *cpu) {
  Engine::RAM::SetByte(cpu->hl, (cpu->hl >> 8));
}

// LD Instruction
// Load the value of 8-bits register L at the address pointed by 16-bits register HL

void CPU::Disasm::Dis0x75(CPU::Z80 *cpu) {
  Engine::RAM::SetByte(cpu->hl, (cpu->hl & 0xFF));
}

// HALT Instruction
// TODO ????

void CPU::Disasm::Dis0x76(CPU::Z80 *) {
  std::cerr << "[ERROR] Error occured. Quitting... HALT" << std::endl;
  DEBUG_PRINT("Instruction 0x76 : HALT : Not Implemented");
  exit(EXIT_FAILURE);
}

// LD Instruction
// Load the value of 8-bits register A at the address pointed by 16-bits register HL

void CPU::Disasm::Dis0x77(CPU::Z80 *cpu) {
  Engine::RAM::SetByte(cpu->hl, (cpu->af >> 8));
}

// LD Instruction
// Load the value of 8-bits register B in 8-bits register A

void CPU::Disasm::Dis0x78(CPU::Z80 *cpu) {
  cpu->af = ((cpu->bc >> 8) << 8) + (cpu->af & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register C in 8-bits register A

void CPU::Disasm::Dis0x79(CPU::Z80 *cpu) {
  cpu->af = ((cpu->bc & 0xFF) << 8) + (cpu->af & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register D in 8-bits register A

void CPU::Disasm::Dis0x7A(CPU::Z80 *cpu) {
  cpu->af = ((cpu->de >> 8) << 8) + (cpu->af & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register E in 8-bits register A

void CPU::Disasm::Dis0x7B(CPU::Z80 *cpu) {
  cpu->af = ((cpu->de & 0xFF) << 8) + (cpu->af & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register H in 8-bits register A

void CPU::Disasm::Dis0x7C(CPU::Z80 *cpu) {
  cpu->af = ((cpu->hl >> 8) << 8) + (cpu->af & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register L in 8-bits register A

void CPU::Disasm::Dis0x7D(CPU::Z80 *cpu) {
  cpu->af = ((cpu->hl & 0xFF) << 8) + (cpu->af & 0xFF);
}

// LD Instruction
// Load the value of 8-bits direct located at the address pointed by 16-bits register HL in 8-bits register A

void CPU::Disasm::Dis0x7E(CPU::Z80 *cpu) {
  cpu->af = (Engine::RAM::GetByte(cpu->hl) << 8) + (cpu->af & 0xFF);
}

// LD Instruction
// Load the value of 8-bits register A in 8-bits register A

void CPU::Disasm::Dis0x7F(CPU::Z80 *) {
  // Nothing to do ?
}

// ADD Instruction
// Add the value of 8-bits register B and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x80(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if (((((cpu->af >> 8) & 0xF) + ((cpu->bc >> 8) & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (((((cpu->af >> 8) & 0xFF) + ((cpu->bc >> 8) & 0xFF)) & 0x100) == 0x100) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (((cpu->af >> 8) + (cpu->bc >> 8)) << 8) + (cpu->af & 0xFF);
  if (!(cpu->af >> 8)) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// ADD Instruction
// Add the value of 8-bits register C and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x81(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if (((((cpu->af >> 8) & 0xF) + ((cpu->bc & 0xFF) & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (((((cpu->af >> 8) & 0xFF) + ((cpu->bc & 0xFF) & 0xFF)) & 0x100) == 0x100) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (((cpu->af >> 8) + (cpu->bc & 0xFF)) << 8) + (cpu->af & 0xFF);
  if (!(cpu->af >> 8)) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// ADD Instruction
// Add the value of 8-bits register D and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x82(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if (((((cpu->af >> 8) & 0xF) + ((cpu->de >> 8) & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (((((cpu->af >> 8) & 0xFF) + ((cpu->de >> 8) & 0xFF)) & 0x100) == 0x100) {
    flags |= (1 << 4);
  } else {
    flags &= (1 << 4);
  }
  cpu->af = (((cpu->af >> 8) + (cpu->de >> 8)) << 8) + (cpu->af & 0xFF);
  if (!(cpu->af >> 8)) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// ADD Instruction
// Add the value of 8-bits register E and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x83(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if (((((cpu->af >> 8) & 0xF) + ((cpu->de & 0xFF) & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (((((cpu->af >> 8) & 0xFF) + ((cpu->de & 0xFF) & 0xFF)) & 0x100) == 0x100) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (((cpu->af >> 8) + (cpu->de & 0xFF)) << 8) + (cpu->af & 0xFF);
  if (!(cpu->af >> 8)) {
    flags |= (1 << 7);
  } else {
    flags &= (1 << 7);
  }
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// ADD Instruction
// Add the value of 8-bits register H and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x84(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if (((((cpu->af >> 8) & 0xF) + ((cpu->hl >> 8) & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (((((cpu->af >> 8) & 0xFF) + ((cpu->hl >> 8) & 0xFF)) & 0x100) == 0x100) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (((cpu->af >> 8) + (cpu->hl >> 8)) << 8) + (cpu->af & 0xFF);
  if (!(cpu->af >> 8)) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// ADD Instruction
// Add the value of 8-bits register L and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x85(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if (((((cpu->af >> 8) & 0xF) + ((cpu->hl & 0xFF) & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (((((cpu->af >> 8) & 0xFF) + ((cpu->hl & 0xFF) & 0xFF)) & 0x100) == 0x100) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (((cpu->af >> 8) + (cpu->hl & 0xFF)) << 8) + (cpu->af & 0xFF);
  if (!(cpu->af >> 8)) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// ADD Instruction
// Add the value of 8-bits direct located at the address pointed by HL and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x86(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if (((((cpu->af >> 8) & 0xF) + (Engine::RAM::GetByte(cpu->hl) & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (((((cpu->af >> 8) & 0xFF) + (Engine::RAM::GetByte(cpu->hl)  & 0xFF)) & 0x100) == 0x100) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (((cpu->af >> 8) + Engine::RAM::GetByte(cpu->hl)) << 8) + (cpu->af & 0xFF);
  if (!(cpu->af >> 8)) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// ADD Instruction
// Add the value of 8-bits register A and 8-bits register A
// Store the result in A

void CPU::Disasm::Dis0x87(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if (((((cpu->af >> 8) & 0xF) + ((cpu->af >> 8) & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (((((cpu->af >> 8) & 0xFF) + ((cpu->af >> 8) & 0xFF)) & 0x100) == 0x100) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (((cpu->af >> 8) + (cpu->af >> 8)) << 8) + (cpu->af & 0xFF);
  if (!(cpu->af >> 8)) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// ADC Instruction
// Add the value of 8-bits register B and 8-bits register A
// Then add the carry flag (0 or 1)
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x88(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->af >> 8) + (cpu->bc >> 8);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if ((((cpu->af & 0xFF) >> 4) & 1) == 1)
    tmp++;
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if (((((cpu->af >> 8) & 0xF) + ((cpu->bc >> 8) & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (((((cpu->af >> 8) & 0xFF) + ((cpu->bc >> 8) & 0xFF)) & 0x100) == 0x100) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// ADC Instruction
// Add the value of 8-bits register C and 8-bits register A
// Then add the carry flag (0 or 1)
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x89(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->af >> 8) + (cpu->bc & 0xFF);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if ((((cpu->af & 0xFF) >> 4) & 1) == 1)
    tmp++;
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if (((((cpu->af >> 8) & 0xF) + ((cpu->bc & 0xFF) & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (((((cpu->af >> 8) & 0xFF) + ((cpu->bc & 0xFF) & 0xFF)) & 0x100) == 0x100) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// ADC Instruction
// Add the value of 8-bits register D and 8-bits register A
// Then add the carry flag (0 or 1)
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x8A(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->af >> 8) + (cpu->de >> 8);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if ((((cpu->af & 0xFF) >> 4) & 1) == 1)
    tmp++;
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if (((((cpu->af >> 8) & 0xF) + ((cpu->de >> 8) & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (((((cpu->af >> 8) & 0xFF) + ((cpu->de >> 8) & 0xFF)) & 0x100) == 0x100) {
    flags |= (1 << 4);
  } else {
    flags &= (1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// ADC Instruction
// Add the value of 8-bits register E and 8-bits register A
// Then add the carry flag (0 or 1)
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x8B(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = (cpu->af >> 8) + (cpu->de & 0xFF);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if ((((cpu->af & 0xFF) >> 4) & 1) == 1)
    tmp++;
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if (((((cpu->af >> 8) & 0xF) + ((cpu->de & 0xFF) & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (((((cpu->af >> 8) & 0xFF) + ((cpu->de & 0xFF) & 0xFF)) & 0x100) == 0x100) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// ADC Instruction
// Add the value of 8-bits register H and 8-bits register A
// Then add the carry flag (0 or 1)
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x8C(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->af >> 8) + (cpu->hl >> 8);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if ((((cpu->af & 0xFF) >> 4) & 1) == 1)
    tmp++;
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if (((((cpu->af >> 8) & 0xF) + ((cpu->hl >> 8) & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (((((cpu->af >> 8) & 0xFF) + ((cpu->hl >> 8) & 0xFF)) & 0x100) == 0x100) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// ADC Instruction
// Add the value of 8-bits register L and 8-bits register A
// Then add the carry flag (0 or 1)
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x8D(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->af >> 8) + (cpu->hl & 0xFF);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if ((((cpu->af & 0xFF) >> 4) & 1) == 1)
    tmp++;
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if (((((cpu->af >> 8) & 0xF) + ((cpu->hl & 0xFF) & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (((((cpu->af >> 8) & 0xFF) + ((cpu->hl & 0xFF) & 0xFF)) & 0x100) == 0x100) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// ADC Instruction
// Add the value of 8-bits direct located at the address pointed by 16-bits register HL and 8-bits register A
// Then add the carry flag (0 or 1)
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x8E(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->af >> 8) + Engine::RAM::GetByte(cpu->hl);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if ((((cpu->af & 0xFF) >> 4) & 1) == 1)
    tmp++;
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if (((((cpu->af >> 8) & 0xF) + (Engine::RAM::GetByte(cpu->hl) & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (((((cpu->af >> 8) & 0xFF) + (Engine::RAM::GetByte(cpu->hl) & 0xFF)) & 0x100) == 0x100) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// ADC Instruction
// Add the value of 8-bits register A and 8-bits register A
// Then add the carry flag (0 or 1)
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x8F(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->af >> 8) + (cpu->af >> 8);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if ((((cpu->af & 0xFF) >> 4) & 1) == 1)
    tmp++;
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if (((((cpu->af >> 8) & 0xF) + ((cpu->af >> 8) & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (((((cpu->af >> 8) & 0xFF) + ((cpu->af >> 8) & 0xFF)) & 0x100) == 0x100) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// SUB Instruction
// Substract 8-bits register B from 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x90(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->af >> 8) - (cpu->bc >> 8));
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - ((cpu->bc >> 8) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - ((cpu->bc >> 8) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// SUB Instruction
// Substract 8-bits register C from 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x91(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->af >> 8) - (cpu->bc & 0xFF));
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - ((cpu->bc & 0xFF) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - ((cpu->bc & 0xFF) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// SUB Instruction
// Substract 8-bits register D from 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x92(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->af >> 8) - (cpu->de >> 8));
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - ((cpu->de >> 8) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - ((cpu->de >> 8) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// SUB Instruction
// Substract 8-bits register E from 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x93(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->af >> 8) - (cpu->de & 0xFF));
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - ((cpu->de & 0xFF) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - ((cpu->de & 0xFF) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// SUB Instruction
// Substract 8-bits register H from 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x94(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->af >> 8) - (cpu->hl >> 8));
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - ((cpu->hl >> 8) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - ((cpu->hl >> 8) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// SUB Instruction
// Substract 8-bits register L from 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x95(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->af >> 8) - (cpu->hl & 0xFF));
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - ((cpu->hl & 0xFF) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - ((cpu->hl & 0xFF) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// SUB Instruction
// Substract 8-bits direct located at the address pointed by 16-bits register HL from 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x96(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->af >> 8) - Engine::RAM::GetByte(cpu->hl));
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - (Engine::RAM::GetByte(cpu->hl) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - (Engine::RAM::GetByte(cpu->hl) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// SUB Instruction
// Substract 8-bits register A from 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x97(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->af >> 8) - (cpu->af >> 8));
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - ((cpu->af >> 8) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - ((cpu->af >> 8) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// SBC Instruction
// Substract 8-bits register B from 8-bits register A
// Then substract the carry flag (0 or 1)
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x98(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->af >> 8) - (cpu->bc >> 8);
  if ((((cpu->af & 0xFF) >> 4) & 1) == 1)
    tmp--;
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - ((cpu->bc >> 8) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - ((cpu->bc >> 8) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// SBC Instruction
// Substract 8-bits register C from 8-bits register A
// Then substract the carry flag (0 or 1)
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x99(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->af >> 8) - (cpu->bc & 0xFF);
  if ((((cpu->af & 0xFF) >> 4) & 1) == 1)
    tmp--;
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - ((cpu->bc & 0xFF) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - ((cpu->bc & 0xFF) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// SBC Instruction
// Substract 8-bits register D from 8-bits register A
// Then substract the carry flag (0 or 1)
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x9A(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->af >> 8) - (cpu->de >> 8);
  if ((((cpu->af & 0xFF) >> 4) & 1) == 1)
    tmp--;
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - ((cpu->de >> 8) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - ((cpu->de >> 8) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// SBC Instruction
// Substract 8-bits register E from 8-bits register A
// Then substract the carry flag (0 or 1)
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x9B(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->af >> 8) - (cpu->de & 0xFF);
  if ((((cpu->af & 0xFF) >> 4) & 1) == 1)
    tmp--;
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - ((cpu->de & 0xFF) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - ((cpu->de & 0xFF) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// SBC Instruction
// Substract 8-bits register H from 8-bits register A
// Then substract the carry flag (0 or 1)
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x9C(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->af >> 8) - (cpu->hl >> 8);
  if ((((cpu->af & 0xFF) >> 4) & 1) == 1)
    tmp--;
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - ((cpu->hl >> 8) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - ((cpu->hl >> 8) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// SBC Instruction
// Substract 8-bits register L from 8-bits register A
// Then substract the carry flag (0 or 1)
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x9D(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->af >> 8) - (cpu->hl & 0xFF);
  if ((((cpu->af & 0xFF) >> 4) & 1) == 1)
    tmp--;
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - ((cpu->hl & 0xFF) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - ((cpu->hl & 0xFF) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// SBC Instruction
// Substract 8-bits direct located at the address pointed by 16-bits register HL from 8-bits register A
// Then substract the carry flag (0 or 1)
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x9E(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->af >> 8) - Engine::RAM::GetByte(cpu->hl);
  if ((((cpu->af & 0xFF) >> 4) & 1) == 1)
    tmp--;
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - (Engine::RAM::GetByte(cpu->hl) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - (Engine::RAM::GetByte(cpu->hl) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// SBC Instruction
// Substract 8-bits register A from 8-bits register A
// Then substract the carry flag (0 or 1)
// Store the result in 8-bits register A

void CPU::Disasm::Dis0x9F(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->af >> 8) - (cpu->af >> 8);
  if ((((cpu->af & 0xFF) >> 4) & 1) == 1)
    tmp--;
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - ((cpu->af >> 8) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - ((cpu->af >> 8) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// AND Instruction
// Logically AND 8-bits register B and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xA0(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 4);
  flags |= (1 << 5);
  if (!(((cpu->af >> 8) & (cpu->bc >> 8)))) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (((cpu->af >> 8) & (cpu->bc >> 8)) << 8) + flags;
}

// AND Instruction
// Logically AND 8-bits register C and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xA1(CPU::Z80 *cpu) {
  uint8_t flags;
  
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 4);
  flags |= (1 << 5);
  if (!(((cpu->af >> 8) & (cpu->bc & 0xFF)))) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (((cpu->af >> 8) & (cpu->bc & 0xFF)) << 8) + flags;
}

// AND Instruction
// Logically AND 8-bits register D and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xA2(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 4);
  flags |= (1 << 5);
  if (!(((cpu->af >> 8) & (cpu->de >> 8)))) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (((cpu->af >> 8) & (cpu->de >> 8)) << 8) + flags;
}

// AND Instruction
// Logically AND 8-bits register E and 8-bits register A
// Store the value in 8-bits register A

void CPU::Disasm::Dis0xA3(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 4);
  flags |= (1 << 5);
  if (!(((cpu->af >> 8) & (cpu->de & 0xFF)))) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (((cpu->af >> 8) & (cpu->de & 0xFF)) << 8) + flags;
}

// AND Instruction
// Logically AND 8-bits register H and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xA4(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 4);
  flags |= (1 << 5);
  if (!(((cpu->af >> 8) & (cpu->hl >> 8)))) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (((cpu->af >> 8) & (cpu->hl >> 8)) << 8) + flags;
}

// AND Instruction
// Logically AND 8-bits register L and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xA5(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 4);
  flags |= (1 << 5);
  if (!(((cpu->af >> 8) & (cpu->hl & 0xFF)))) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (((cpu->af >> 8) & (cpu->hl & 0xFF)) << 8) + (cpu->af & 0xFF);
}

// AND Instruction
// Logically AND 8-bits direct located at the address pointed by 16-bits register HL and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xA6(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 4);
  flags |= (1 << 5);
  if (!(((cpu->af >> 8) & Engine::RAM::GetByte(cpu->hl)))) {
    flags |= (1 << 7);
  } else {
    flags &= (1 << 7);
  }
  cpu->af = (((cpu->af >> 8) & Engine::RAM::GetByte(cpu->hl)) << 8) + flags;
}

// AND Instruction
// Logically AND 8-bits register A and 8-bits register A
// Store the results in 8-bits register A

void CPU::Disasm::Dis0xA7(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 4);
  flags |= (1 << 5);
  if (!(((cpu->af >> 8) & (cpu->af >> 8)))) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (((cpu->af >> 8) & (cpu->af >> 8)) << 8) + flags;
}

// XOR Instruction
// Logically XOR 8-bits register B and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xA8(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 4);
  flags &= ~(1 << 5);
  flags &= ~(1 << 6);
  if (!((cpu->af >> 8) ^ (cpu->bc >> 8))) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (((cpu->af >> 8) ^ (cpu->bc >> 8)) << 8) + flags;
}

// XOR Instruction
// Logically XOR 8-bits register C and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xA9(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 4);
  flags &= ~(1 << 5);
  flags &= ~(1 << 6);
  if (!((cpu->af >> 8) ^ (cpu->bc & 0xFF))) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (((cpu->af >> 8) ^ (cpu->bc & 0xFF)) << 8) + flags;
}

// XOR Instruction
// Logically XOR 8-bits register D and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xAA(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 4);
  flags &= ~(1 << 5);
  flags &= ~(1 << 6);
  if (!((cpu->af >> 8) ^ (cpu->de >> 8))) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (((cpu->af >> 8) ^ (cpu->de >> 8)) << 8) + flags;
}

// XOR Instruction
// Logically XOR 8-bits register E and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xAB(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 4);
  flags &= ~(1 << 5);
  flags &= ~(1 << 6);
  if (!((cpu->af >> 8) ^ (cpu->de & 0xFF))) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (((cpu->af >> 8) ^ (cpu->de & 0xFF)) << 8) + flags;
}

// XOR Instruction
// Logically XOR 8-bits register H and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xAC(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 4);
  flags &= ~(1 << 5);
  flags &= ~(1 << 6);
  if (!((cpu->af >> 8) ^ (cpu->hl >> 8))) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (((cpu->af >> 8) ^ (cpu->hl >> 8)) << 8) + flags;
}

// XOR Instruction
// Logically XOR 8-bits register L and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xAD(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 4);
  flags &= ~(1 << 5);
  flags &= ~(1 << 6);
  if (!((cpu->af >> 8) ^ (cpu->hl & 0xFF))) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (((cpu->af >> 8) ^ (cpu->hl & 0xFF)) << 8) + flags;
}

// XOR Instruction
// Logically XOR 8-bits direct located at the address pointed by 16-bits register HL and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xAE(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 4);
  flags &= ~(1 << 5);
  flags &= ~(1 << 6);
  if (!((cpu->af >> 8) ^ Engine::RAM::GetByte(cpu->hl))) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (((cpu->af >> 8) ^ Engine::RAM::GetByte(cpu->hl)) << 8) + flags;
}

// XOR Instruction
// Logically XOR 8-bits register A and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xAF(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 4);
  flags &= ~(1 << 5);
  flags &= ~(1 << 6);
  if (!((cpu->af >> 8) ^ (cpu->af >> 8))) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (((cpu->af >> 8) ^ (cpu->af >> 8)) << 8) + flags;
}

// OR Instruction
// Logically OR 8-bits register B and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xB0(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 4);
  flags &= ~(1 << 5);
  flags &= ~(1 << 6);
  if (!((cpu->af >> 8) | (cpu->bc >> 8))) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (((cpu->af >> 8) | (cpu->bc >> 8)) << 8) + flags;
}

// OR Instruction
// Logically OR 8-bits register C and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xB1(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 4);
  flags &= ~(1 << 5);
  flags &= ~(1 << 6);
  if (!((cpu->af >> 8) | (cpu->bc & 0xFF))) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (((cpu->af >> 8) | (cpu->bc & 0xFF)) << 8) + flags;
}

// OR Instruction
// Logically OR 8-bits register D and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xB2(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 4);
  flags &= ~(1 << 5);
  flags &= ~(1 << 6);
  if (!((cpu->af >> 8) | (cpu->de >> 8))) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (((cpu->af >> 8) | (cpu->de >> 8)) << 8) + flags;
}

// OR Instruction
// Logically OR 8-bits register E and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xB3(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  flags &= ~(1 << 4);
  if (!((cpu->af >> 8) | (cpu->de & 0xFF))) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (((cpu->af >> 8) | (cpu->de & 0xFF)) << 8) + flags;
}

// OR Instruction
// Logically OR 8-bits register H and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xB4(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  flags &= ~(1 << 4);
  if (!((cpu->af >> 8) | (cpu->hl >> 8))) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (((cpu->af >> 8) | (cpu->hl >> 8)) << 8) + flags;
}

// OR Instruction
// Logically OR 8-bits register L and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xB5(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  flags &= ~(1 << 4);
  if (!((cpu->af >> 8) | (cpu->hl & 0xFF))) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (((cpu->af >> 8) | (cpu->hl & 0xFF)) << 8) + flags;
}

// OR Instruction
// Logically OR 8-bits direct located at the address pointed by 16-bits register HL and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xB6(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  flags &= ~(1 << 4);
  if (!((cpu->af >> 8) | Engine::RAM::GetByte(cpu->hl))) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (((cpu->af >> 8) | Engine::RAM::GetByte(cpu->hl)) << 8) + flags;
}

// OR Instruction
// Logically OR 8-bits register A and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xB7(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  flags &= ~(1 << 4);
  if (!((cpu->af >> 8) | (cpu->af & 0xFF))) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (((cpu->af >> 8) | (cpu->af >> 8)) << 8) + flags;
}

// CP Instruction
// Compare 8-bits register B and 8-bits register A

void CPU::Disasm::Dis0xB8(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = ((cpu->af >> 8) - (cpu->bc >> 8));
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - ((cpu->bc >> 8) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - ((cpu->bc >> 8) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// CP Instruction
// Compare 8-bits register C and 8-bits register A

void CPU::Disasm::Dis0xB9(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = ((cpu->af >> 8) - (cpu->bc & 0xFF));
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - ((cpu->bc & 0xFF) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - ((cpu->bc & 0xFF) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// CP Instruction
// Compare 8-bits register D and 8-bits register A

void CPU::Disasm::Dis0xBA(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = ((cpu->af >> 8) - (cpu->de >> 8));
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - ((cpu->de >> 8) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - ((cpu->de >> 8) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// CP Instruction
// Compare 8-bits register E and 8-bits register A

void CPU::Disasm::Dis0xBB(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = ((cpu->af >> 8) - (cpu->de & 0xFF));
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - ((cpu->de & 0xFF) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - ((cpu->de & 0xFF) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// CP Instruction
// Compare 8-bits register H and 8-bits register A

void CPU::Disasm::Dis0xBC(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = ((cpu->af >> 8) - (cpu->hl >> 8));
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - ((cpu->hl >> 8) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - ((cpu->hl >> 8) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// CP Instruction
// Compare 8-bits register L and 8-bits register A

void CPU::Disasm::Dis0xBD(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = ((cpu->af >> 8) - (cpu->hl & 0xFF));
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - ((cpu->hl & 0xFF) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - ((cpu->hl & 0xFF) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// CP Instruction
// Compare 8-bits direct located at the address pointed by 16-bits register HL and 8-bits register A

void CPU::Disasm::Dis0xBE(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = ((cpu->af >> 8) - Engine::RAM::GetByte(cpu->hl));
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - (Engine::RAM::GetByte(cpu->hl) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - (Engine::RAM::GetByte(cpu->hl) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// CP Instruction
// Compare 8-bits register A and 8-bits register A

void CPU::Disasm::Dis0xBF(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = ((cpu->af >> 8) - (cpu->af >> 8));
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - ((cpu->af >> 8) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - ((cpu->af >> 8) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RET NZ Instruction
// Pop last 16-bits value from stack if Z flag = 0
// Store the 16-bits value in 16-bits register PC

void CPU::Disasm::Dis0xC0(CPU::Z80 *cpu) {
  if (((cpu->af & 0xFF) & 1) != 1) {
    cpu->pc = (Engine::RAM::GetByte(cpu->sp + 1) << 8) + Engine::RAM::GetByte(cpu->sp); 
    cpu->pc--;
    cpu->sp += 2;
  }
}

// POP Instruction
// Pop 16-bits from stack
// Store value in 16-bits register BC

void CPU::Disasm::Dis0xC1(CPU::Z80 *cpu) {
  cpu->bc = (Engine::RAM::GetByte(cpu->sp + 1) << 8) + Engine::RAM::GetByte(cpu->sp);
  cpu->sp += 2;
}

// JP Instruction
// Jump to the given address if Z flag = 0
// Reset Z flag

void CPU::Disasm::Dis0xC2(CPU::Z80 *cpu) {
  if (((cpu->af & 0xFF) >> 7) != 1) {
    cpu->pc = (Engine::RAM::GetByte(cpu->pc + 2) << 8) + Engine::RAM::GetByte(cpu->pc + 1);
    cpu->pc -= 3;
  }
}

// JP Instruction
// Jump to the given address

void CPU::Disasm::Dis0xC3(CPU::Z80 *cpu) {
  cpu->pc = (Engine::RAM::GetByte(cpu->pc + 2) << 8) + Engine::RAM::GetByte(cpu->pc + 1);
  cpu->pc -= 3;
}

// CALL Instruction
// Push address of next instruction into stack
// Jump to given address

void CPU::Disasm::Dis0xC4(CPU::Z80 *cpu) {
  if ((((cpu->af & 0xFF) >> 7) & 1) != 1) {
    cpu->sp -= 2;
    Engine::RAM::SetByte(cpu->sp, (cpu->pc + 3) & 0xFF);
    Engine::RAM::SetByte(cpu->sp + 1, (cpu->pc + 3) >> 8);
    cpu->pc = (Engine::RAM::GetByte(cpu->pc + 2) << 8) + Engine::RAM::GetByte(cpu->pc + 1);
    cpu->pc -= 3;
  }
}

// PUSH Instruction
// Push 16-bits register BC onto stack
// Decrement stack twice

void CPU::Disasm::Dis0xC5(CPU::Z80 *cpu) {
  cpu->sp -= 2;
  Engine::RAM::SetByte(cpu->sp, (cpu->bc & 0xFF));
  Engine::RAM::SetByte(cpu->sp + 1, (cpu->bc >> 8));
}

// ADD Instruction
// Add the value of 8-bits direct and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xC6(CPU::Z80 *cpu) {
  uint8_t flags;

  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if (((((cpu->af >> 8) & 0xF) + (Engine::RAM::GetByte(cpu->pc + 1) & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (((((cpu->af >> 8) & 0xFF) + (Engine::RAM::GetByte(cpu->pc + 1) & 0xFF)) & 0x100) == 0x100) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (((cpu->af >> 8) + Engine::RAM::GetByte(cpu->pc + 1)) << 8) + flags;
  if (!(cpu->af >> 8)) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RST Instruction
// 16-bits register PC + 3 is pushed onto the stack
// PC is initialized to 0x0000

void CPU::Disasm::Dis0xC7(CPU::Z80 *cpu) {
  cpu->sp -= 2;
  Engine::RAM::SetByte(cpu->sp, ((cpu->pc + 3) & 0xFF));
  Engine::RAM::SetByte(cpu->sp + 1, ((cpu->pc + 3) >> 8));
  cpu->pc = 0x0000;
  cpu->pc -= 3;
}

// RET Z Instruction
// Pop last 16-bits from stack if Zero flag = 1
// Store the result in 16-bits register PC

void CPU::Disasm::Dis0xC8(CPU::Z80 *cpu) {
  if (((cpu->af & 0xFF) & 1) == 1) {
    cpu->pc = (Engine::RAM::GetByte(cpu->sp + 1) << 8) + Engine::RAM::GetByte(cpu->sp);
    cpu->pc--;
    cpu->sp += 2;
  }
}

// RET Instruction
// Pop last 16-bits from stack
// Store the result in 16-bits register PC

void CPU::Disasm::Dis0xC9(CPU::Z80 *cpu) {
  cpu->pc = (Engine::RAM::GetByte(cpu->sp + 1) << 8) + Engine::RAM::GetByte(cpu->sp);
  cpu->pc--;
  cpu->sp += 2;
}

// JP Instruction
// Jump to given address if Zero flag = 1

void CPU::Disasm::Dis0xCA(CPU::Z80 *cpu) {
  if (((cpu->af & 0xFF) & 1) == 1) {
    cpu->pc = (Engine::RAM::GetByte(cpu->pc + 2) << 8) + Engine::RAM::GetByte(cpu->pc + 1);
    cpu->pc -= 3;
  }
}

// CB PREFIX
// TODO ????

void CPU::Disasm::Dis0xCB(CPU::Z80 *cpu) {
  int i = 0;
  bool found = false;
  
  while (ext_opcodes[i].byteLength != 0 && !found) {
    if (Engine::RAM::GetByte(cpu->pc + 1) == ext_opcodes[i].code) {
#ifdef DEBUG
      dprintf(1, "\n[DEBUG] : ------------------------------START---------------------------------\n");
      dprintf(1, "[DEBUG] : Program Counter value : 0x%04X\n", cpu->pc);
      dprintf(1, "[DEBUG] : Instruction 0x%02X found\n", ext_opcodes[i].code);
#endif
      
      ext_opcodes[i].fptr(cpu);

#ifdef DEBUG
      RegDump(cpu);
      dprintf(1, "[DEBUG] : ---------------------------------END----------------------------------\n\n");
#endif
      
      found = true;
      cpu->pc++;
    }
    i++;
  }
}

// CALL Instruction
// Push next instruction address in stack and jump to given address if Zero flag = 1

void CPU::Disasm::Dis0xCC(CPU::Z80 *cpu) {
  if ((((cpu->af & 0xFF) >> 7) & 1) != 1) {
    cpu->sp -= 2;
    Engine::RAM::SetByte(cpu->sp, (cpu->pc + 3) & 0xFF);
    Engine::RAM::SetByte(cpu->sp + 1, (cpu->pc + 3) >> 8);
    cpu->pc = (Engine::RAM::GetByte(cpu->pc + 2) << 8) + Engine::RAM::GetByte(cpu->pc + 1);
    cpu->pc -= 3;
  }
}

// CALL Instruction
// Push next instruction address in stack and jump to given address

void CPU::Disasm::Dis0xCD(CPU::Z80 *cpu) {
  cpu->sp -= 2;
  Engine::RAM::SetByte(cpu->sp, (cpu->pc + 3) & 0xFF);
  Engine::RAM::SetByte(cpu->sp + 1, (cpu->pc + 3) >> 8);
  cpu->pc = (Engine::RAM::GetByte(cpu->pc + 2) << 8) + Engine::RAM::GetByte(cpu->pc + 1);
  cpu->pc -= 3;
}

// ADC Instruction
// Add the value of 8-bits direct and 8-bits register A
// Then add the carry flag

void CPU::Disasm::Dis0xCE(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (((cpu->af >> 8) + Engine::RAM::GetByte(cpu->pc + 1)) << 8) + (cpu->af & 0xFF);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  if (((flags >> 7) & 1) == 1)
    tmp++;
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if (((((cpu->af >> 8) & 0xF) + (Engine::RAM::GetByte(cpu->pc + 1) & 0xF)) & 0x10) == 0x10) {
    flags |= (1 << 5);
  } else {
    flags &= ~(1 << 5);
  }
  if (((((cpu->af >> 8) & 0xFF) + (Engine::RAM::GetByte(cpu->pc + 1) & 0xFF)) & 0x100) == 0x100) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// RST 08 Instruction
// Push 16-bits register PC + 3 onto stack
// Reset 16-bits register to address 0x0008

void CPU::Disasm::Dis0xCF(CPU::Z80 *cpu) {
  cpu->sp -= 2;
  cpu->pc += 3;
  Engine::RAM::SetByte(cpu->sp, (cpu->pc & 0xFF));
  Engine::RAM::SetByte(cpu->sp + 1, (cpu->pc >> 8));
  cpu->pc = 0x0008;
  cpu->pc--;
}

// RET NC Instruction
// Pop last 16-bits from stack and put it in 16-bits register PC

void CPU::Disasm::Dis0xD0(CPU::Z80 *cpu) {
  if ((((cpu->af & 0xFF) >> 4) & 1) != 1) { 
    cpu->pc = (Engine::RAM::GetByte(cpu->sp + 1) << 8) + Engine::RAM::GetByte(cpu->sp);
    cpu->sp += 2;
    cpu->pc--;
  }
}

// POP Instruction
// Pop last 16-bits from stack and put it in 16-bits register DE

void CPU::Disasm::Dis0xD1(CPU::Z80 *cpu) {
  cpu->de = (Engine::RAM::GetByte(cpu->sp + 1) << 8) + Engine::RAM::GetByte(cpu->sp);
  cpu->sp += 2;
}

// JP Instruction
// Jump to given address if Carry flag = 0

void CPU::Disasm::Dis0xD2(CPU::Z80 *cpu) {
  if ((((cpu->af & 0xFF) >> 4) & 1) != 0) {
    cpu->pc = (Engine::RAM::GetByte(cpu->pc + 2) << 8) + Engine::RAM::GetByte(cpu->pc + 1);
    cpu->pc -= 3;
  }
}

/*
  Unimplemented Instruction

  void CPU::Disasm::Dis0xD3(CPU::Z80 *cpu) {
  }

*/

// CALL Instruction
// Put the address of the next instruction in stack and jump to given address

void CPU::Disasm::Dis0xD4(CPU::Z80 *cpu) {
  if ((((cpu->af & 0xFF) >> 4) & 1) != 1) {
    cpu->sp -= 2;
    Engine::RAM::SetByte(cpu->sp, (cpu->pc + 3) & 0xFF);
    Engine::RAM::SetByte(cpu->sp + 1, (cpu->pc + 3) >> 8);
    cpu->pc = (Engine::RAM::GetByte(cpu->pc + 2) << 8) + Engine::RAM::GetByte(cpu->pc + 1);
    cpu->pc -= 3;
  }
}

// PUSH Instruction
// Push 16-bits register DE in stack

void CPU::Disasm::Dis0xD5(CPU::Z80 *cpu) {
  cpu->sp -= 2;
  Engine::RAM::SetByte(cpu->sp + 1, (cpu->de >> 8));
  Engine::RAM::SetByte(cpu->sp, (cpu->de & 0xFF));
}

// SUB Instruction
// Substract 8-bits direct from 8-bits register A
// Store the result in A

void CPU::Disasm::Dis0xD6(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->af >> 8) - Engine::RAM::GetByte(cpu->pc + 1));
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - (Engine::RAM::GetByte(cpu->pc + 1) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - (Engine::RAM::GetByte(cpu->pc + 1) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// RST Instruction
// Push 16-bits register PC + 3 onto the stack and jump to given address

void CPU::Disasm::Dis0xD7(CPU::Z80 *cpu) {
  cpu->sp -= 2;
  cpu->pc += 3;
  Engine::RAM::SetByte(cpu->sp, (cpu->pc & 0xFF));
  Engine::RAM::SetByte(cpu->sp + 1, (cpu->pc >> 8));
  cpu->pc = 0x0010;
  cpu->pc--;
}

// RET C
// Pop 16-bits from stack and put in 16-bits register PC if Carry flag = 1

void CPU::Disasm::Dis0xD8(CPU::Z80 *cpu) {
  if ((((cpu->af & 0xFF) >> 4) & 1) == 1) {
    cpu->pc = (Engine::RAM::GetByte(cpu->sp + 1) << 8) + Engine::RAM::GetByte(cpu->sp);
    cpu->sp += 2;
    cpu->pc--;
  }
}

// RETI
// Set 16-bits register PC to his old value stocked in stack

void CPU::Disasm::Dis0xD9(CPU::Z80 *cpu) {
  cpu->ime = 1;
  cpu->pc = (Engine::RAM::GetByte(cpu->sp - 1) << 8) + Engine::RAM::GetByte(cpu->sp);
  cpu->pc--;
}

// JP Instruction
// Jump to given address if Carry flag = 1

void CPU::Disasm::Dis0xDA(CPU::Z80 *cpu) {
  if ((((cpu->af & 0xFF) >> 4) & 1) == 1) {
    cpu->pc = (Engine::RAM::GetByte(cpu->pc + 2) << 8) + Engine::RAM::GetByte(cpu->pc + 1);
    cpu->pc -= 3;
  }
}

/*

  Unimplemented instruction

  void CPU::Disasm::Dis0xDB(CPU::Z80 *cpu) {
  }

*/

// CALL Instruction
// Push next instruction address onto stack and jump to given address if Carry flag = 1

void CPU::Disasm::Dis0xDC(CPU::Z80 *cpu) {
  if ((((cpu->af & 0xFF) >> 4) & 1) == 1) {
    cpu->sp -= 2;
    Engine::RAM::SetByte(cpu->sp, (cpu->pc + 3) & 0xFF);
    Engine::RAM::SetByte(cpu->sp + 1, (cpu->pc + 3) >> 8);
    cpu->pc = (Engine::RAM::GetByte(cpu->pc + 2) << 8) + Engine::RAM::GetByte(cpu->pc + 1);
    cpu->pc -= 3;
  }
}

/*

  Unimplemented instruction

  void CPU::Disasm::Dis0xDD(CPU::Z80 *cpu) {
  }

*/

// SBC Instruction
// Substract 8-bits direct and 8-bits register A
// Substract Carry from 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xDE(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->af >> 8) - Engine::RAM::GetByte(cpu->pc + 1);
  if ((((cpu->af & 0xFF) >> 4) & 1) == 1)
    tmp--;
  flags = (cpu->af & 0xFF);
  flags |= (1 << 6);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - (Engine::RAM::GetByte(cpu->pc + 1) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - (Engine::RAM::GetByte(cpu->pc + 1) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// RST Instruction
// Push next insttruction address onto stack and jump to given address

void CPU::Disasm::Dis0xDF(CPU::Z80 *cpu) {
  cpu->sp -= 2;
  cpu->pc += 3;
  Engine::RAM::SetByte(cpu->sp, (cpu->pc & 0xFF));
  Engine::RAM::SetByte(cpu->sp + 1, (cpu->pc >> 8));
  cpu->pc = 0x0018;
  cpu->pc--;
}

// LDH Instruction
// Load 8-bits register A at address 0xFF00 + 8-bits direct

void CPU::Disasm::Dis0xE0(CPU::Z80 *cpu) {
  Engine::RAM::SetByte((0xFF00 + Engine::RAM::GetByte(cpu->pc + 1)), (cpu->af >> 8));
}

// POP HL Instruction
// Pop 16-bits from stack and store it in 16-bits register HL

void CPU::Disasm::Dis0xE1(CPU::Z80 *cpu) {
  cpu->hl = (Engine::RAM::GetByte(cpu->sp + 1) << 8) + Engine::RAM::GetByte(cpu->sp);
  cpu->sp += 2;
}

// LDH Instruction
// Load 8-bits register A at the address 0xFF00 + 8-bits register C

void CPU::Disasm::Dis0xE2(CPU::Z80 *cpu) {
  Engine::RAM::SetByte(0xFF00 + (cpu->bc & 0xFF), (cpu->af >> 8));
  cpu->pc--;
}

/*

// Unimplemented Instruction

void CPU::Disasm::Dis0xE3(CPU::Z80 *cpu) {
}

// Unimplemented Instruction

void CPU::Disasm::Dis0xE4(CPU::Z80 *cpu) {
}

*/

// PUSH Instruction
// Push 16-bits register HL onto stack

void CPU::Disasm::Dis0xE5(CPU::Z80 *cpu) {
  cpu->sp -= 2;
  Engine::RAM::SetByte(cpu->sp + 1, (cpu->hl >> 8));
  Engine::RAM::SetByte(cpu->sp, (cpu->hl & 0xFF));
}

// AND Instruction
// Logically AND 8-bits direct and 8-bits register A
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xE6(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->af >> 8) & Engine::RAM::GetByte(cpu->pc + 1));
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags |= (1 << 5);
  flags &= ~(1 << 4);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (tmp << 8) + flags;
}

// RST Instruction
// Push next instruction address onto stack and jump to given address

void CPU::Disasm::Dis0xE7(CPU::Z80 *cpu) {
  cpu->sp -= 2;
  cpu->pc += 3;
  Engine::RAM::SetByte(cpu->sp, (cpu->pc & 0xFF));
  Engine::RAM::SetByte(cpu->sp + 1, (cpu->pc >> 8));
  cpu->pc = 0x0020;
  cpu->pc--;
}

// ADD Instruction
// Add the value of 16-bits register SP and 8-bits direct

void CPU::Disasm::Dis0xE8(CPU::Z80 *cpu) {
  uint8_t flags;
  char i;

  i = Engine::RAM::GetByte(cpu->pc + 1);
  flags = (cpu->af & 0XFF);
  flags &= ~(1 << 7);
  flags &= ~(1 << 6);
  if (i > 0) {
    if (((((cpu->sp >> 8) & 0xF) + (i & 0xF)) & 0x10) == 0x10) {
      flags |= (1 << 5);
    } else {
      flags &= ~(1 << 5);
    }
    if (((((cpu->sp >> 8) & 0xFF) + (i & 0xFF)) & 0x100) == 0x100) {
      flags |= (1 << 4);
    } else {
      flags &= ~(1 << 4);
    }
  } else if (i < 0) {
    if ((((cpu->sp >> 8) & 0xF) - (i & 0xF)) < 0) {
      flags |= 1 << 5;
    } else {
      flags &= ~(1 << 5);
    }
    if ((((cpu->sp >> 8) & 0xFF) - (i & 0xFF)) < 0) {
      flags |= 1 << 4;
    } else {
      flags &= ~(1 << 4);
    }
  }
  cpu->sp += i;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// JP Instruction
// Jump to the address located by the value of 16-bits register HL

void CPU::Disasm::Dis0xE9(CPU::Z80 *cpu) {
  cpu->pc = (Engine::RAM::GetByte(cpu->hl + 1) << 8) + Engine::RAM::GetByte(cpu->hl);
  cpu->pc--;
}

// LD Instruction
// Load the value of 8-bits register A at address given by 16-bits direct

void CPU::Disasm::Dis0xEA(CPU::Z80 *cpu) {
  Engine::RAM::SetByte((Engine::RAM::GetByte(cpu->pc + 2) << 8) + Engine::RAM::GetByte(cpu->pc + 1), (cpu->af >> 8));
}

/*

// Unimplemented Instruction

void CPU::Disasm::Dis0xEB(CPU::Z80 *cpu) {
}

// Unimplemented Instruction

void CPU::Disasm::Dis0xEC(CPU::Z80 *cpu) {
}

// Unimplemented Instruction

void CPU::Disasm::Dis0xED(CPU::Z80 *cpu) {
}

*/

// XOR Instruction
// Logically XOR 8-bits register A and 8-bits direct
// Store the result in 8-bits register A

void CPU::Disasm::Dis0xEE(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->af >> 8) ^ Engine::RAM::GetByte(cpu->pc + 1));
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  flags &= ~(1 << 4);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (tmp << 8) + flags;
}

// RST Instruction
// Push next instruction address onto stack and jump to given address

void CPU::Disasm::Dis0xEF(CPU::Z80 *cpu) {
  cpu->sp -= 2;
  cpu->pc += 3;
  Engine::RAM::SetByte(cpu->sp, (cpu->pc & 0xFF));
  Engine::RAM::SetByte(cpu->sp + 1, (cpu->pc >> 8));
  cpu->pc = 0x0028;
  cpu->pc--;
}

// LDH Instruction
// Save the 8-bits register A at the address 0xFF00 + 8-bits direct

void CPU::Disasm::Dis0xF0(CPU::Z80 *cpu) {
  cpu->af = (Engine::RAM::GetByte(0xFF00 + Engine::RAM::GetByte(cpu->pc + 1)) << 8) + (cpu->af & 0xFF);
}

// POP AF
// Pop 16-bits from stack and put it in 16-bits register AF

void CPU::Disasm::Dis0xF1(CPU::Z80 *cpu) {
  cpu->af = (Engine::RAM::GetByte(cpu->sp + 1) << 8) + Engine::RAM::GetByte(cpu->sp);
  cpu->sp += 2;
}

// LD Instruction
// Load the value of 8-bits direct located at the address pointed by 0xFF00 + 8-bits register C in 8-bits register A

void CPU::Disasm::Dis0xF2(CPU::Z80 *cpu) {
  cpu->af = (Engine::RAM::GetByte(0xFF00 + (cpu->bc & 0xFF)) << 8) + (cpu->af & 0xFF);
}

// DI Instruction
// Disable all interrupts

void CPU::Disasm::Dis0xF3(CPU::Z80 *cpu) {
  cpu->ime = 0;
}

/*

// Unimplemented Instruction

void CPU::Disasm::Dis0xF4(CPU::Z80 *cpu) {
}

*/

// PUSH Instruction
// Push 16-bits register AF onto stack

void CPU::Disasm::Dis0xF5(CPU::Z80 *cpu) {
  cpu->sp -= 2;
  Engine::RAM::SetByte(cpu->sp + 1, (cpu->af >> 8));
  Engine::RAM::SetByte(cpu->sp, (cpu->af & 0xFF));
}

// OR Instruction
// Logically OR 8-bits direct and 8-bits register A
// Store the result in A

void CPU::Disasm::Dis0xF6(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->af >> 8) | Engine::RAM::GetByte(cpu->pc + 1));
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  flags &= ~(1 << 4);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (tmp << 8) + flags;
}

// RST Instruction
// Push next instruction address onto stack and jump to given address

void CPU::Disasm::Dis0xF7(CPU::Z80 *cpu) {
  cpu->sp -= 2;
  cpu->pc += 3;
  Engine::RAM::SetByte(cpu->sp, (cpu->pc & 0xFF));
  Engine::RAM::SetByte(cpu->sp + 1, (cpu->pc >> 8));
  cpu->pc = 0x0030;
  cpu->pc--;
}

// LDHL Instruction
// Add 8-bits direct to 16-bits register SP
// Store the result in 16-bits register HL

void CPU::Disasm::Dis0xF8(CPU::Z80 *cpu) {
  uint8_t flags;
  char i;

  i = Engine::RAM::GetByte(cpu->pc + 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 7);
  flags &= ~(1 << 6);
  if (i > 0) {
    if (((((cpu->sp >> 8) & 0xF) + (i & 0xF)) & 0x10) == 0x10) {
      flags |= (1 << 5);
    } else {
      flags &= ~(1 << 5);
    }
    if (((((cpu->sp >> 8) & 0xFF) + (i & 0xFF)) & 0x100) == 0x100) {
      flags |= (1 << 4);
    } else {
      flags &= ~(1 << 4);
    }
  } else if (i < 0) {
    if ((((cpu->sp >> 8) & 0xF) - (i & 0xF)) < 0) {
      flags |= 1 << 5;
    } else {
      flags &= ~(1 << 5);
    }
    if ((((cpu->sp >> 8) & 0xFF) - (i & 0xFF)) < 0) {
      flags |= 1 << 4;
    } else {
      flags &= ~(1 << 4);
    }
  }
  cpu->hl = cpu->sp + i;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// LD Instruction
// Load the value of 16-bits register HL to 16-bits register SP

void CPU::Disasm::Dis0xF9(CPU::Z80 *cpu) {
  cpu->sp = cpu->hl;
}

// LD Instruction
// Load the value of 8-bits direct located at the address pointed by 16-bits direct in 8-bits register A

void CPU::Disasm::Dis0xFA(CPU::Z80 *cpu) {
  cpu->af = (Engine::RAM::GetByte((Engine::RAM::GetByte(cpu->pc + 2) << 8) + Engine::RAM::GetByte(cpu->pc + 1)) << 8) + (cpu->af & 0xFF);
}

// EI Instruction
// Enable all interrupts

void CPU::Disasm::Dis0xFB(CPU::Z80 *cpu) {
  cpu->ime = 1;
}

/*

// Unimplemented Instruction

void CPU::Disasm::Dis0xFC(CPU::Z80 *cpu) {
}

// Unimplemented Instruction

void CPU::Disasm::Dis0xFD(CPU::Z80 *cpu) {
}

*/

// CP Instruction
// Compare 8-bits direct with 8-bits register A

void CPU::Disasm::Dis0xFE(CPU::Z80 *cpu) {
  uint8_t flags;
  uint8_t tmp;

  tmp = ((cpu->af >> 8) - Engine::RAM::GetByte(cpu->pc + 1));
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) & 0xF) - (Engine::RAM::GetByte(cpu->pc + 1) & 0xF)) < 0) {
    flags |= 1 << 5;
  } else {
    flags &= ~(1 << 5);
  }
  if ((((cpu->af >> 8) & 0xFF) - (Engine::RAM::GetByte(cpu->pc + 1) & 0xFF)) < 0) {
    flags |= 1 << 4;
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RST Instruction
// Push next instruction address onto stack and jump to given address

void CPU::Disasm::Dis0xFF(CPU::Z80 *cpu) {
  cpu->sp -= 2;
  cpu->pc += 3;
  Engine::RAM::SetByte(cpu->sp, (cpu->pc & 0xFF));
  Engine::RAM::SetByte(cpu->sp + 1, (cpu->pc >> 8));
  cpu->pc = 0x0038;
  cpu->pc--;
}


/* CB Extension Instructions */

// RLC Instruction
// Rotate 8-bits register B left with carry

void CPU::Disasm::DisCB0x00(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->bc >> 8;
  tmp = (tmp << 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(0 << 6);
  flags &= ~(0 << 5);
  if ((((cpu->bc >> 8) >> 0) & 1) == 0) {
    flags &= ~(1 << 4);
  } else {
    flags |= (1 << 4);
  }
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RLC Instruction
// Rotate 8-bits register C left with carry

void CPU::Disasm::DisCB0x01(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->bc & 0xFF;
  tmp = (tmp << 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(0 << 6);
  flags &= ~(0 << 5);
  if ((((cpu->bc & 0xFF) >> 0) & 1) == 0) {
    flags &= ~(1 << 4);
  } else {
    flags |= (1 << 4);
  }
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RLC Instruction
// Rotate 8-bits register D left with carry

void CPU::Disasm::DisCB0x02(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->de >> 8;
  tmp = (tmp << 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(0 << 6);
  flags &= ~(0 << 5);
  if ((((cpu->de >> 8) >> 0) & 1) == 0) {
    flags &= ~(1 << 4);
  } else {
    flags |= (1 << 4);
  }
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RLC Instruction
// Rotate 8-bits register E left with carry

void CPU::Disasm::DisCB0x03(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->de & 0xFF;
  tmp = (tmp << 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(0 << 6);
  flags &= ~(0 << 5);
  if ((((cpu->de & 0xFF) >> 0) & 1) == 0) {
    flags &= ~(1 << 4);
  } else {
    flags |= (1 << 4);
  }
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RLC Instruction
// Rotate 8-bits register H left with carry

void CPU::Disasm::DisCB0x04(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->hl >> 8;
  tmp = (tmp << 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(0 << 6);
  flags &= ~(0 << 5);
  if ((((cpu->hl >> 8) >> 0) & 1) == 0) {
    flags &= ~(1 << 4);
  } else {
    flags |= (1 << 4);
  }
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RLC Instruction
// Rotate 8-bits register L left with carry

void CPU::Disasm::DisCB0x05(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->hl & 0xFF;
  tmp = (tmp << 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(0 << 6);
  flags &= ~(0 << 5);
  if ((((cpu->hl & 0xFF) >> 0) & 1) == 0) {
    flags &= ~(1 << 4);
  } else {
    flags |= (1 << 4);
  }
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RLC Instruction
// Rotate 8-bits direct located at the address pointed by 16-bits register HL with carry
// Place it back at the address located by 16-bits register HL

void CPU::Disasm::DisCB0x06(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = Engine::RAM::GetByte(cpu->hl);
  tmp = (tmp << 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(0 << 6);
  flags &= ~(0 << 5);
  if (((Engine::RAM::GetByte(cpu->hl) >> 0) & 1) == 0) {
    flags &= ~(1 << 4);
  } else {
    flags |= (1 << 4);
  }
  Engine::RAM::SetByte(cpu->hl, tmp);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RLC Instruction
// Rotate 8-bits register A left with carry

void CPU::Disasm::DisCB0x07(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->af >> 8;
  tmp = (tmp << 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(0 << 6);
  flags &= ~(0 << 5);
  if ((((cpu->af >> 8) >> 0) & 1) == 0) {
    flags &= ~(1 << 4);
  } else {
    flags |= (1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// RRC Instruction
// Rotate 8-bits register B right with carry

void CPU::Disasm::DisCB0x08(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->bc >> 8;
  tmp = (tmp >> 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(0 << 6);
  flags &= ~(0 << 5);
  if ((((cpu->bc >> 8) >> 7) & 1) == 0) {
    flags &= ~(1 << 4);
  } else {
    flags |= (1 << 4);
  }
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RRC Instruction
// Rotate 8-bits register C right with carry

void CPU::Disasm::DisCB0x09(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->bc & 0xFF;
  tmp = (tmp >> 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(0 << 6);
  flags &= ~(0 << 5);
  if ((((cpu->bc & 0xFF) >> 7) & 1) == 0) {
    flags &= ~(1 << 4);
  } else {
    flags |= (1 << 4);
  }
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RRC Instruction
// Rotate 8-bits register D right with carry

void CPU::Disasm::DisCB0x0A(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->de >> 8;
  tmp = (tmp >> 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(0 << 6);
  flags &= ~(0 << 5);
  if ((((cpu->de >> 8) >> 7) & 1) == 0) {
    flags &= ~(1 << 4);
  } else {
    flags |= (1 << 4);
  }
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RRC Instruction
// Rotate 8-bits register E right with carry

void CPU::Disasm::DisCB0x0B(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->de & 0xFF;
  tmp = (tmp >> 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(0 << 6);
  flags &= ~(0 << 5);
  if ((((cpu->de & 0xFF) >> 7) & 1) == 0) {
    flags &= ~(1 << 4);
  } else {
    flags |= (1 << 4);
  }
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RRC Instruction
// Rotate 8-bits register H right with carry

void CPU::Disasm::DisCB0x0C(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->hl >> 8;
  tmp = (tmp >> 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(0 << 6);
  flags &= ~(0 << 5);
  if ((((cpu->hl >> 8) >> 7) & 1) == 0) {
    flags &= ~(1 << 4);
  } else {
    flags |= (1 << 4);
  }
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RRC Instruction
// Rotate 8-bits register L right with carry

void CPU::Disasm::DisCB0x0D(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->hl & 0xFF;
  tmp = (tmp >> 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(0 << 6);
  flags &= ~(0 << 5);
  if ((((cpu->hl & 0xFF) >> 7) & 1) == 0) {
    flags &= ~(1 << 4);
  } else {
    flags |= (1 << 4);
  }
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RRC Instruction
// Rotate 8-bits direct located at the address pointed by 16-bits register HL right with carry
// Save the result at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0x0E(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = Engine::RAM::GetByte(cpu->hl);
  tmp = (tmp >> 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(0 << 6);
  flags &= ~(0 << 5);
  if (((Engine::RAM::GetByte(cpu->hl) >> 7) & 1) == 0) {
    flags &= ~(1 << 4);
  } else {
    flags |= (1 << 4);
  }
  Engine::RAM::SetByte(cpu->hl, tmp);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RRC Instruction
// Rotate 8-bits register A right with carry

void CPU::Disasm::DisCB0x0F(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->af >> 8;
  tmp = (tmp >> 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(0 << 6);
  flags &= ~(0 << 5);
  if ((((cpu->af >> 8) >> 7) & 1) == 0) {
    flags &= ~(1 << 4);
  } else {
    flags |= (1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// RL Instruction
// Rotate 8-bits register B left

void CPU::Disasm::DisCB0x10(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->bc >> 8;
  tmp = (tmp << 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (((flags >> 4) & 1) == 1) {
    tmp |= (1 << 0);
  } else {
    tmp &= ~(1 << 0);
  }
  if ((((cpu->bc >> 8) >> 7) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RL Instruction
// Rotate 8-bits register C left

void CPU::Disasm::DisCB0x11(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->bc & 0xFF;
  tmp = (tmp << 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (((flags >> 4) & 1) == 1) {
    tmp |= (1 << 0);
  } else {
    tmp &= ~(1 << 0);
  }
  if ((((cpu->bc & 0xFF) >> 7) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RL Instruction
// Rotate 8-bits register D left

void CPU::Disasm::DisCB0x12(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->de >> 8;
  tmp = (tmp << 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (((flags >> 4) & 1) == 1) {
    tmp |= (1 << 0);
  } else {
    tmp &= ~(1 << 0);
  }
  if ((((cpu->de >> 8) >> 7) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RL Instruction
// Rotate 8-bits register E left

void CPU::Disasm::DisCB0x13(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->de & 0xFF;
  tmp = (tmp << 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (((flags >> 4) & 1) == 1) {
    tmp |= (1 << 0);
  } else {
    tmp &= ~(1 << 0);
  }
  if ((((cpu->de & 0xFF) >> 7) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RL Instruction
// Rotate 8-bits register H left

void CPU::Disasm::DisCB0x14(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->hl >> 8;
  tmp = (tmp << 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (((flags >> 4) & 1) == 1) {
    tmp |= (1 << 0);
  } else {
    tmp &= ~(1 << 0);
  }
  if ((((cpu->hl >> 8) >> 7) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RL Instruction
// Rotate 8-bits register L left

void CPU::Disasm::DisCB0x15(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->hl & 0xFF;
  tmp = (tmp << 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (((flags >> 4) & 1) == 1) {
    tmp |= (1 << 0);
  } else {
    tmp &= ~(1 << 0);
  }
  if ((((cpu->hl & 0xFF) >> 7) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RL Instruction
// Rotate 8-bits direct located at the address pointed by 16-bits register HL left
// Save the result at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0x16(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = Engine::RAM::GetByte(cpu->hl);
  tmp = (tmp << 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (((flags >> 4) & 1) == 1) {
    tmp |= (1 << 0);
  } else {
    tmp &= ~(1 << 0);
  }
  if (((Engine::RAM::GetByte(cpu->hl) >> 7) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  Engine::RAM::SetByte(cpu->hl, tmp);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RL Instruction
// Rotate 8-bits register A left

void CPU::Disasm::DisCB0x17(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->af >> 8;
  tmp = (tmp << 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (((flags >> 4) & 1) == 1) {
    tmp |= (1 << 0);
  } else {
    tmp &= ~(1 << 0);
  }
  if ((((cpu->af >> 8) >> 7) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// RR Instruction
// Rotate 8-bits register B right

void CPU::Disasm::DisCB0x18(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->bc >> 8;
  tmp = (tmp >> 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (((flags >> 4) & 1) == 1) {
    tmp |= (1 << 7);
  } else {
    tmp &= ~(1 << 7);
  }
  if ((((cpu->bc >> 8) >> 0) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RR Instruction
// Rotate 8-bits register C right

void CPU::Disasm::DisCB0x19(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->bc & 0xFF;
  tmp = (tmp >> 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (((flags >> 4) & 1) == 1) {
    tmp |= (1 << 7);
  } else {
    tmp &= ~(1 << 7);
  }
  if ((((cpu->bc & 0xFF) >> 0) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RR Instruction
// Rotate 8-bits register D right

void CPU::Disasm::DisCB0x1A(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->de >> 8;
  tmp = (tmp >> 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (((flags >> 4) & 1) == 1) {
    tmp |= (1 << 7);
  } else {
    tmp &= ~(1 << 7);
  }
  if ((((cpu->de >> 8) >> 0) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RR Instruction
// Rotate 8-bits register E right

void CPU::Disasm::DisCB0x1B(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->de & 0xFF;
  tmp = (tmp >> 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (((flags >> 4) & 1) == 1) {
    tmp |= (1 << 7);
  } else {
    tmp &= ~(1 << 7);
  }
  if ((((cpu->de & 0xFF) >> 0) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RR Instruction
// Rotate 8-bits register H right

void CPU::Disasm::DisCB0x1C(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->hl >> 8;
  tmp = (tmp >> 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (((flags >> 4) & 1) == 1) {
    tmp |= (1 << 7);
  } else {
    tmp &= ~(1 << 7);
  }
  if ((((cpu->hl >> 8) >> 0) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RR Instruction
// Rotate 8-bits register L right

void CPU::Disasm::DisCB0x1D(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->hl & 0xFF;
  tmp = (tmp >> 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (((flags >> 4) & 1) == 1) {
    tmp |= (1 << 7);
  } else {
    tmp &= ~(1 << 7);
  }
  if ((((cpu->hl & 0xFF) >> 0) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RR Instruction
// Rotate 8-bits direct located at the address pointed by 16-bits register HL right
// Save the result at the address located by 16-bits register HL

void CPU::Disasm::DisCB0x1E(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = Engine::RAM::GetByte(cpu->hl);
  tmp = (tmp >> 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (((flags >> 4) & 1) == 1) {
    tmp |= (1 << 7);
  } else {
    tmp &= ~(1 << 7);
  }
  if (((Engine::RAM::GetByte(cpu->hl) >> 0) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  Engine::RAM::SetByte(cpu->hl, tmp);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// RR Instruction
// Rotate the 8-bits register A right

void CPU::Disasm::DisCB0x1F(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = cpu->af >> 8;
  tmp = (tmp >> 1);
  flags = (cpu->af & 0xFF);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (((flags >> 4) & 1) == 1) {
    tmp |= (1 << 7);
  } else {
    tmp &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) >> 0) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// SLA Instruction
// Non circular shift on 8-bits register B to the left 

void CPU::Disasm::DisCB0x20(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->bc >> 8) << 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->bc >> 8) >> 7) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SLA Instruction
// Non circular shift on 8-bits register C to the left

void CPU::Disasm::DisCB0x21(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->bc & 0xFF) << 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->bc & 0xFF) >> 7) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// SLA Instruction
// Non circular shift on 8-bits register D to the left

void CPU::Disasm::DisCB0x22(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->de >> 8) << 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->de >> 8) >> 7) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SLA Instruction
// Non circular shift on 8-bits register E to the left

void CPU::Disasm::DisCB0x23(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->de & 0xFF) << 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->de & 0xFF) >> 7) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SLA Instruction
// Non circular shift on 8-bits register H to the left

void CPU::Disasm::DisCB0x24(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->hl >> 8) << 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->hl >> 8) >> 7) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SLA Instruction
// Non circular shift on 8-bits register L to the left

void CPU::Disasm::DisCB0x25(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->hl & 0xFF) << 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->hl & 0xFF) >> 7) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SLA Instruction
// Non circular shift on 8-bits direct located at the address pointed by 16-bits register HL to the left
// Store the result at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0x26(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = Engine::RAM::GetByte(cpu->hl) << 1;
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if (((Engine::RAM::GetByte(cpu->hl) >> 7) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  Engine::RAM::SetByte(cpu->hl, tmp);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SLA Instruction
// Non circular shift on 8-bits register A to the left

void CPU::Disasm::DisCB0x27(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->af >> 8) << 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if ((((cpu->af >> 8) >> 7) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags &= ~(1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// SRA Instruction
// Non circular shift on 8-bits register B to the right

void CPU::Disasm::DisCB0x28(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->bc >> 8) >> 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  flags &= ~(1 << 4);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SRA Instruction
// Non circular shift on 8-bits register C to the right

void CPU::Disasm::DisCB0x29(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->bc & 0xFF) >> 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  flags &= ~(1 << 4);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SRA Instruction
// Non circular shift on 8-bits register D to the right

void CPU::Disasm::DisCB0x2A(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->de >> 8) >> 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  flags &= ~(1 << 4);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SRA Instruction
// Non circular shift on 8-bits register E to the right

void CPU::Disasm::DisCB0x2B(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->de & 0xFF) >> 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  flags &= ~(1 << 4);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SRA Instruction
// Non circular shift on 8-bits register H to the right

void CPU::Disasm::DisCB0x2C(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->hl >> 8) >> 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  flags &= ~(1 << 4);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SRA Instruction
// Non circular shift on 8-bits register L to the right

void CPU::Disasm::DisCB0x2D(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->hl & 0xFF) >> 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  flags &= ~(1 << 4);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SRA Instruction
// Non circular shift on 8-bits direct located at the address pointed by 16-bits register HL to the right

void CPU::Disasm::DisCB0x2E(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = Engine::RAM::GetByte(cpu->hl) >> 1;
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  flags &= ~(1 << 4);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  Engine::RAM::SetByte(cpu->hl, tmp);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SRA Instruction
// Non circular shift on 8-bits register A to the right

void CPU::Disasm::DisCB0x2F(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->af >> 8) >> 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  flags &= ~(1 << 4);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (tmp << 8) + flags;
}

// SWAP Instruction
// Swap higher (7-4) & lower (3-0) bits of 8-bits register B

void CPU::Disasm::DisCB0x30(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->bc >> 8);
  tmp = (tmp >> 4) | (tmp << 4);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  flags &= ~(1 << 4);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SWAP Instruction
// Swap higher (7-4) & lower (3-0) bits of 8-bits register C

void CPU::Disasm::DisCB0x31(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->bc & 0xFF);
  tmp = (tmp >> 4) | (tmp << 4);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  flags &= ~(1 << 4);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SWAP Instruction
// Swap higher (7-4) & lower (3-0) bits of 8-bits register D

void CPU::Disasm::DisCB0x32(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->de >> 8);
  tmp = (tmp >> 4) | (tmp << 4);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  flags &= ~(1 << 4);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SWAP Instruction
// Swap higher (7-4) & lower (3-0) bits of 8-bits register E

void CPU::Disasm::DisCB0x33(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->de & 0xFF);
  tmp = (tmp >> 4) | (tmp << 4);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  flags &= ~(1 << 4);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SWAP Instruction
// Swap higher (7-4) & lower (3-0) bits of 8-bits register H

void CPU::Disasm::DisCB0x34(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->hl >> 8);
  tmp = (tmp >> 4) | (tmp << 4);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  flags &= ~(1 << 4);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SWAP Instruction
// Swap higher (7-4) & lower (3-0) bits of 8-bits register L

void CPU::Disasm::DisCB0x35(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->hl & 0xFF);
  tmp = (tmp >> 4) | (tmp << 4);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  flags &= ~(1 << 4);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SWAP Instruction
// Swap higher (7-4) & lower (3-0) bits of 8-bits direct located at the address pointed by 16-bits HL

void CPU::Disasm::DisCB0x36(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = Engine::RAM::GetByte(cpu->hl);
  tmp = (tmp >> 4) | (tmp << 4);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  flags &= ~(1 << 4);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  Engine::RAM::SetByte(cpu->hl, tmp);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SWAP Instruction
// Swap higher (7-4) & lower (3-0) bits of 8-bits register A

void CPU::Disasm::DisCB0x37(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;
  
  tmp = (cpu->af >> 8);
  tmp = (tmp >> 4) | (tmp << 4);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  flags &= ~(1 << 4);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  cpu->af = (tmp << 8) + flags;
}

// SRL Instruction
// Shift 8-bits register B right

void CPU::Disasm::DisCB0x38(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->bc >> 8) >> 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if (((tmp >> 0) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags |= (1 << 4);
  }
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SRL Instruction
// Shift 8-bits register C right

void CPU::Disasm::DisCB0x39(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->bc & 0xFF) >> 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if (((tmp >> 0) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags |= (1 << 4);
  }
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SRL Instruction
// Shift 8-bits register D right

void CPU::Disasm::DisCB0x3A(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->de >> 8) >> 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if (((tmp >> 0) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags |= (1 << 4);
  }
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SRL Instruction
// Shift 8-bits register E right

void CPU::Disasm::DisCB0x3B(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->de & 0xFF) >> 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if (((tmp >> 0) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags |= (1 << 4);
  }
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SRL Instruction
// Shift 8-bits register H right

void CPU::Disasm::DisCB0x3C(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->hl >> 8) >> 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if (((tmp >> 0) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags |= (1 << 4);
  }
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SRL Instruction
// Shit 8-bits register L right

void CPU::Disasm::DisCB0x3D(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->hl & 0xFF) >> 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if (((tmp >> 0) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags |= (1 << 4);
  }
  cpu->hl = ((cpu->bc >> 8) << 8) + tmp;
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SRL Instruction
// Shift 8-bits direct located at the address pointed by 16-bits register HL right

void CPU::Disasm::DisCB0x3E(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = (Engine::RAM::GetByte(cpu->hl) >> 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if (((tmp >> 0) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags |= (1 << 4);
  }
  Engine::RAM::SetByte(cpu->hl, tmp);
  cpu->af = ((cpu->af >> 8) << 8) + flags;
}

// SRL Instruction
// Shift 8-bits register right

void CPU::Disasm::DisCB0x3F(CPU::Z80 *cpu) {
  uint8_t tmp;
  uint8_t flags;

  tmp = ((cpu->af >> 8) >> 1);
  flags = (cpu->af & 0xFF);
  flags &= ~(1 << 6);
  flags &= ~(1 << 5);
  if (!tmp) {
    flags |= (1 << 7);
  } else {
    flags &= ~(1 << 7);
  }
  if (((tmp >> 0) & 1) == 1) {
    flags |= (1 << 4);
  } else {
    flags |= (1 << 4);
  }
  cpu->af = (tmp << 8) + flags;
}

// BIT Instruction
// Test if bit 0 is set in 8-bits register B

void CPU::Disasm::DisCB0x40(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->bc >> 8) >> 0) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 0 is set in 8-bits register C

void CPU::Disasm::DisCB0x41(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->bc & 0xFF) >> 0) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 0 is set in 8-bits register D

void CPU::Disasm::DisCB0x42(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->de >> 8) >> 0) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 0 is set in 8-bits register E

void CPU::Disasm::DisCB0x43(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->de & 0xFF) >> 0) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 0 is set in 8-bits register H

void CPU::Disasm::DisCB0x44(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->hl >> 8) >> 0) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 0 is set in 8-bits register L

void CPU::Disasm::DisCB0x45(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->hl & 0xFF) >> 0) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 0 is set in 8-bits direct located at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0x46(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if (((Engine::RAM::GetByte(cpu->hl) >> 0) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 0 is set in 8-bits register A

void CPU::Disasm::DisCB0x47(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->af >> 8) >> 0) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 1 is set in 8-bits register B

void CPU::Disasm::DisCB0x48(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->bc >> 8) >> 1) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 1 is set in 8-bits register C

void CPU::Disasm::DisCB0x49(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->bc & 0xFF) >> 1) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 1 is set in 8-bits register D

void CPU::Disasm::DisCB0x4A(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->de >> 8) >> 1) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 1 is set in 8-bits register E

void CPU::Disasm::DisCB0x4B(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->de & 0xFF) >> 1) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 1 is set in 8-bits register H

void CPU::Disasm::DisCB0x4C(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->hl >> 8) >> 1) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 1 is set in 8-bits register L

void CPU::Disasm::DisCB0x4D(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->hl & 0xFF) >> 1) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 1 is set in 8-bits direct located at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0x4E(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if (((Engine::RAM::GetByte(cpu->hl) >> 1) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 1 is set in 8-bits register A

void CPU::Disasm::DisCB0x4F(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->af >> 8) >> 1) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 2 is set in 8-bits register B

void CPU::Disasm::DisCB0x50(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->bc >> 8) >> 2) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 2 is set in 8-bits register C

void CPU::Disasm::DisCB0x51(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->bc & 0xFF) >> 2) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 2 is set in 8-bits register D

void CPU::Disasm::DisCB0x52(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->de >> 8) >> 2) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 2 is set in 8-bits register E

void CPU::Disasm::DisCB0x53(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->de & 0xFF) >> 2) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 2 is set in 8-bits register H

void CPU::Disasm::DisCB0x54(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->hl >> 8) >> 2) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 2 is set in 8-bits register L

void CPU::Disasm::DisCB0x55(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->hl & 0xFF) >> 0) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 2 is set in 8-bits direct located at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0x56(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if (((Engine::RAM::GetByte(cpu->hl) >> 2) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 2 is set in 8-bits register A

void CPU::Disasm::DisCB0x57(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->af >> 8) >> 2) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 3 is set in 8-bits register B

void CPU::Disasm::DisCB0x58(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->bc >> 8) >> 3) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 3 is set in 8-bits register C

void CPU::Disasm::DisCB0x59(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->bc & 0xFF) >> 3) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 3 is set in 8-bits register D

void CPU::Disasm::DisCB0x5A(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->de >> 8) >> 3) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 3 is set in 8-bits register E

void CPU::Disasm::DisCB0x5B(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->de & 0xFF) >> 3) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 3 is set in 8-bits register H

void CPU::Disasm::DisCB0x5C(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->hl >> 8) >> 3) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 3 is set in 8-bits register L

void CPU::Disasm::DisCB0x5D(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->hl & 0xFF) >> 3) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 3 is set in 8-bits direct located at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0x5E(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if (((Engine::RAM::GetByte(cpu->hl) >> 3) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 3 is set in 8-bits register A

void CPU::Disasm::DisCB0x5F(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->af >> 8) >> 3) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 4 is set in 8-bits register B

void CPU::Disasm::DisCB0x60(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->bc >> 8) >> 4) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 4 is set in 8-bits register C

void CPU::Disasm::DisCB0x61(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->bc & 0xFF) >> 4) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 4 is set in 8-bits register D

void CPU::Disasm::DisCB0x62(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->de >> 8) >> 4) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 4 is set in 8-bits register E

void CPU::Disasm::DisCB0x63(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->de & 0xFF) >> 4) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 4 is set in 8-bits register H

void CPU::Disasm::DisCB0x64(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->hl >> 8) >> 4) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 4 is set in 8-bits register L

void CPU::Disasm::DisCB0x65(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->hl & 0xFF) >> 4) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 4 is set in 8-bits direct located at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0x66(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if (((Engine::RAM::GetByte(cpu->hl) >> 4) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 4 is set in 8-bits register A

void CPU::Disasm::DisCB0x67(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->af >> 8) >> 4) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 5 is set in 8-bits register B

void CPU::Disasm::DisCB0x68(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->bc >> 8) >> 5) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 5 is set in 8-bits register C

void CPU::Disasm::DisCB0x69(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->bc & 0xFF) >> 5) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 5 is set in 8-bits register D

void CPU::Disasm::DisCB0x6A(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->de >> 8) >> 5) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 5 is set in 8-bits register E

void CPU::Disasm::DisCB0x6B(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->de & 0xFF) >> 5) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 5 is set in 8-bits register H

void CPU::Disasm::DisCB0x6C(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->hl >> 8) >> 5) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 5 is set in 8-bits register L

void CPU::Disasm::DisCB0x6D(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->hl & 0xFF) >> 5) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 5 is set in 8-bits direct located at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0x6E(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if (((Engine::RAM::GetByte(cpu->hl) >> 5) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 5 is set in 8-bits register A

void CPU::Disasm::DisCB0x6F(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->af >> 8) >> 5) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 6 is set in 8-bits register B

void CPU::Disasm::DisCB0x70(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->bc >> 8) >> 6) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 6 is set in 8-bits register C

void CPU::Disasm::DisCB0x71(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->bc & 0xFF) >> 6) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 6 is set in 8-bits register D

void CPU::Disasm::DisCB0x72(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->de >> 8) >> 6) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 6 is set in 8-bits register E

void CPU::Disasm::DisCB0x73(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->de & 0xFF) >> 6) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 6 is set in 8-bits register H

void CPU::Disasm::DisCB0x74(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->hl >> 8) >> 6) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 6 is set in 8-bits register L

void CPU::Disasm::DisCB0x75(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->hl & 0xFF) >> 6) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 6 is set in 8-bits direct located at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0x76(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if (((Engine::RAM::GetByte(cpu->hl) >> 6) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 6 is set in 8-bits register A

void CPU::Disasm::DisCB0x77(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->af >> 8) >> 6) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 7 is set in 8-bits register B

void CPU::Disasm::DisCB0x78(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->bc >> 8) >> 7) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 7 is set in 8-bits register C

void CPU::Disasm::DisCB0x79(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->bc & 0xFF) >> 7) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 7 is set in 8-bits register D

void CPU::Disasm::DisCB0x7A(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->de >> 8) >> 7) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 7 is set in 8-bits register E

void CPU::Disasm::DisCB0x7B(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->de & 0xFF) >> 7) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 7 is set in 8-bits register H

void CPU::Disasm::DisCB0x7C(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->hl >> 8) >> 7) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 7 is set in 8-bits register L

void CPU::Disasm::DisCB0x7D(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->hl & 0xFF) >> 7) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 7 is set in 8-bits direct located at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0x7E(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if (((Engine::RAM::GetByte(cpu->hl) >> 7) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// BIT Instruction
// Test if bit 7 is set in 8-bits register A

void CPU::Disasm::DisCB0x7F(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af & 0xFF);
  if ((((cpu->af >> 8) >> 7) & 1) == 1) {
    tmp |= 1 << 7;
  } else {
    tmp &= ~(1 << 7);
  }
  tmp &= ~(1 << 6);
  tmp |= 1 << 5;
  cpu->af = ((cpu->af >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 0 from 8-bits register B

void CPU::Disasm::DisCB0x80(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc >> 8);
  tmp &= ~(1 << 0);
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
}

// RES Instruction
// Clear bit 0 from 8-bits register C

void CPU::Disasm::DisCB0x81(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc & 0xFF);
  tmp &= ~(1 << 0);
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 0 from 8-bits register D

void CPU::Disasm::DisCB0x82(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de >> 8);
  tmp &= ~(1 << 0);
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
}

// RES Instruction
// Clear bit 0 from 8-bits register E

void CPU::Disasm::DisCB0x83(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de & 0xFF);
  tmp &= ~(1 << 0);
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 0 from 8-bits register H

void CPU::Disasm::DisCB0x84(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl >> 8);
  tmp &= ~(1 << 0);
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
}

// RES Instruction
// Clear bit 0 from 8-bits register L

void CPU::Disasm::DisCB0x85(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl & 0xFF);
  tmp &= ~(1 << 0);
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 0 from 8-bits direct located at the address pointed by 16-bits register HL
// Save the result at the address pointed by 16-bits register HL
void CPU::Disasm::DisCB0x86(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->hl);
  tmp &= ~(1 << 0);
  Engine::RAM::SetByte(cpu->hl, tmp);
}

// RES Instruction
// Clear bit 0 from 8-bits register A

void CPU::Disasm::DisCB0x87(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af >> 8);
  tmp &= ~(1 << 0);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
}

// RES Instruction
// Clear bit 1 from 8-bits register B

void CPU::Disasm::DisCB0x88(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc >> 8);
  tmp &= ~(1 << 1);
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
}

// RES Instruction
// Clear bit 1 from 8-bits register C

void CPU::Disasm::DisCB0x89(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc & 0xFF);
  tmp &= ~(1 << 1);
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 1 from 8-bits register D

void CPU::Disasm::DisCB0x8A(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de >> 8);
  tmp &= ~(1 << 1);
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
}

// RES Instruction
// Clear bit 1 from 8-bits register E

void CPU::Disasm::DisCB0x8B(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de & 0xFF);
  tmp &= ~(1 << 1);
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 1 from 8-bits register H

void CPU::Disasm::DisCB0x8C(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl >> 8);
  tmp &= ~(1 << 1);
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
}

// RES Instruction
// Clear bit 1 from 8-bits register L

void CPU::Disasm::DisCB0x8D(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl & 0xFF);
  tmp &= ~(1 << 1);
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 1 from 8-bits direct located at the address pointed by 16-bits register HL
// Save the result at the address located by 16-bits register HL

void CPU::Disasm::DisCB0x8E(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->hl);
  tmp &= ~(1 << 1);
  Engine::RAM::SetByte(cpu->hl, tmp);
}

// RES Instruction
// Clear bit 1 from 8-bits register A

void CPU::Disasm::DisCB0x8F(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af >> 8);
  tmp &= ~(1 << 1);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
}

// RES Instruction
// Clear bit 2 from 8-bits register B

void CPU::Disasm::DisCB0x90(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc >> 8);
  tmp &= ~(1 << 2);
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
}

// RES Instruction
// Clear bit 2 from 8-bits register C

void CPU::Disasm::DisCB0x91(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc & 0xFF);
  tmp &= ~(1 << 2);
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 2 from 8-bits register D

void CPU::Disasm::DisCB0x92(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de >> 8);
  tmp &= ~(1 << 2);
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
}

// RES Instruction
// Clear bit 2 from 8-bits register E

void CPU::Disasm::DisCB0x93(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de & 0xFF);
  tmp &= ~(1 << 2);
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 2 from 8-bits register H

void CPU::Disasm::DisCB0x94(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl >> 8);
  tmp &= ~(1 << 2);
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
}

// RES Instruction
// Clear bit 2 from 8-bits register L

void CPU::Disasm::DisCB0x95(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl & 0xFF);
  tmp &= ~(1 << 2);
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 2 from 8-bits direct located at the address pointed by 16-bits register HL
// Save the result at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0x96(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->hl);
  tmp &= ~(1 << 2);
  Engine::RAM::SetByte(cpu->hl, tmp);
}

// RES Instruction
// Clear bit 2 from 8-bits register A

void CPU::Disasm::DisCB0x97(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af >> 8);
  tmp &= ~(1 << 2);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
}

// RES Instruction
// Clear bit 3 from 8-bits register B

void CPU::Disasm::DisCB0x98(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc >> 8);
  tmp &= ~(1 << 3);
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
}

// RES Instruction
// Clear bit 3 from 8-bits register C

void CPU::Disasm::DisCB0x99(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc & 0xFF);
  tmp &= ~(1 << 3);
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 3 from 8-bits register D

void CPU::Disasm::DisCB0x9A(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de >> 8);
  tmp &= ~(1 << 3);
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
}

// RES Instruction
// Clear bit 3 from 8-bits register E

void CPU::Disasm::DisCB0x9B(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de & 0xFF);
  tmp &= ~(1 << 3);
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 3 from 8-bits register H

void CPU::Disasm::DisCB0x9C(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl >> 8);
  tmp &= ~(1 << 3);
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
}

// RES Instruction
// Clear bit 3 from 8-bits register L

void CPU::Disasm::DisCB0x9D(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl & 0xFF);
  tmp &= ~(1 << 3);
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 3 from 8-bits direct located at the address pointed by 16-bits register HL
// Save the result at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0x9E(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->hl);
  tmp &= ~(1 << 3);
  Engine::RAM::SetByte(cpu->hl, tmp);
}

// RES Instruction
// Clear bit 3 from 8-bits register A

void CPU::Disasm::DisCB0x9F(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af >> 8);
  tmp &= ~(1 << 3);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
}

// RES Instruction
// Clear bit 4 from 8-bits register B

void CPU::Disasm::DisCB0xA0(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc >> 8);
  tmp &= ~(1 << 4);
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
}

// RES Instruction
// Clear bit 4 from 8-bits register C

void CPU::Disasm::DisCB0xA1(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc & 0xFF);
  tmp &= ~(1 << 4);
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 4 from 8-bits register D

void CPU::Disasm::DisCB0xA2(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de >> 8);
  tmp &= ~(1 << 4);
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
}

// RES Instruction
// Clear bit 4 from 8-bits register E

void CPU::Disasm::DisCB0xA3(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de & 0xFF);
  tmp &= ~(1 << 4);
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 4 from 8-bits register H

void CPU::Disasm::DisCB0xA4(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl >> 8);
  tmp &= ~(1 << 4);
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
}

// RES Instruction
// Clear bit 4 from 8-bits register L

void CPU::Disasm::DisCB0xA5(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl & 0xFF);
  tmp &= ~(1 << 4);
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 4 from 8-bits direct located at the address pointed by 16-bits register HL
// Save the result at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0xA6(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->hl);
  tmp &= ~(1 << 4);
  Engine::RAM::SetByte(cpu->hl, tmp);
}

// RES Instruction
// Clear bit 4 from 8-bits register A

void CPU::Disasm::DisCB0xA7(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af >> 8);
  tmp &= ~(1 << 4);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
}

// RES Instruction
// Clear bit 5 from 8-bits register B

void CPU::Disasm::DisCB0xA8(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc >> 8);
  tmp &= ~(1 << 5);
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
}

// RES Instruction
// Clear bit 5 from 8-bits register C

void CPU::Disasm::DisCB0xA9(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc & 0xFF);
  tmp &= ~(1 << 5);
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 5 from 8-bits register D

void CPU::Disasm::DisCB0xAA(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de >> 8);
  tmp &= ~(1 << 5);
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
}

// RES Instruction
// Clear bit 5 from 8-bits register E

void CPU::Disasm::DisCB0xAB(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de & 0xFF);
  tmp &= ~(1 << 5);
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 5 from 8-bits register H

void CPU::Disasm::DisCB0xAC(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl >> 8);
  tmp &= ~(1 << 5);
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
}

// RES Instruction
// Clear bit 5 from 8-bits register L

void CPU::Disasm::DisCB0xAD(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl & 0xFF);
  tmp &= ~(1 << 5);
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 5 from 8-bits direct located at the address pointed by 16-bits register HL
// Save the result at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0xAE(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->hl);
  tmp &= ~(1 << 5);
  Engine::RAM::SetByte(cpu->hl, tmp);
}

// RES Instruction
// Clear bit 5 from 8-bits register A

void CPU::Disasm::DisCB0xAF(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af >> 8);
  tmp &= ~(1 << 5);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
}

// RES Instruction
// Clear bit 6 from 8-bits register B

void CPU::Disasm::DisCB0xB0(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc >> 8);
  tmp &= ~(1 << 6);
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
}

// RES Instruction
// Clear bit 6 from 8-bits register C

void CPU::Disasm::DisCB0xB1(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc & 0xFF);
  tmp &= ~(1 << 6);
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 6 from 8-bits register D

void CPU::Disasm::DisCB0xB2(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de >> 8);
  tmp &= ~(1 << 6);
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
}

// RES Instruction
// Clear bit 6 from 8-bits register E

void CPU::Disasm::DisCB0xB3(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de & 0xFF);
  tmp &= ~(1 << 6);
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 6 from 8-bits register H

void CPU::Disasm::DisCB0xB4(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl >> 8);
  tmp &= ~(1 << 6);
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
}

// RES Instruction
// Clear bit 6 from 8-bits register L

void CPU::Disasm::DisCB0xB5(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl & 0xFF);
  tmp &= ~(1 << 6);
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 6 from 8-bits direct located at the address pointed by 16-bits register HL
// Save the result at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0xB6(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->hl);
  tmp &= ~(1 << 6);
  Engine::RAM::SetByte(cpu->hl, tmp);
}

// RES Instruction
// Clear bit 6 from 8-bits register A

void CPU::Disasm::DisCB0xB7(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af >> 8);
  tmp &= ~(1 << 6);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
}

// RES Instruction
// Clear bit 7 from 8-bits register B

void CPU::Disasm::DisCB0xB8(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc >> 8);
  tmp &= ~(1 << 7);
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
}

// RES Instruction
// Clear bit 7 from 8-bits register C

void CPU::Disasm::DisCB0xB9(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc & 0xFF);
  tmp &= ~(1 << 7);
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 7 from 8-bits register D

void CPU::Disasm::DisCB0xBA(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de >> 8);
  tmp &= ~(1 << 7);
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
}

// RES Instruction
// Clear bit 7 from 8-bits register E

void CPU::Disasm::DisCB0xBB(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de & 0xFF);
  tmp &= ~(1 << 7);
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 7 from 8-bits register H

void CPU::Disasm::DisCB0xBC(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl >> 8);
  tmp &= ~(1 << 7);
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
}

// RES Instruction
// Clear bit 7 from 8-bits register L

void CPU::Disasm::DisCB0xBD(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl & 0xFF);
  tmp &= ~(1 << 7);
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
}

// RES Instruction
// Clear bit 7 from 8-bits direct located at the address pointed by 16-bits register HL
// Save the result at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0xBE(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->hl);
  tmp &= ~(1 << 7);
  Engine::RAM::SetByte(cpu->hl, tmp);
}

// RES Instruction
// Clear bit 7 from 8-bits register A

void CPU::Disasm::DisCB0xBF(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af >> 8);
  tmp &= ~(1 << 7);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
}

// SET Instruction
// Set bit 0 from 8-bits register B

void CPU::Disasm::DisCB0xC0(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc >> 8);
  tmp |= (1 << 0);
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
}

// SET Instruction
// Set bit 0 from 8-bits register C

void CPU::Disasm::DisCB0xC1(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc & 0xFF);
  tmp |= (1 << 0);
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 0 from 8-bits register D

void CPU::Disasm::DisCB0xC2(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de >> 8);
  tmp |= (1 << 0);
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
}

// SET Instruction
// Set bit 0 from 8-bits register E

void CPU::Disasm::DisCB0xC3(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de & 0xFF);
  tmp |= (1 << 0);
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 0 from 8-bits register H

void CPU::Disasm::DisCB0xC4(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl >> 8);
  tmp |= (1 << 0);
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
}

// SET Instruction
// Set bit 0 from 8-bits register L

void CPU::Disasm::DisCB0xC5(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl & 0xFF);
  tmp |= (1 << 0);
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 0 from 8-bits direct located at the address pointed by 16-bits register HL
// Save the result at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0xC6(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->hl);
  tmp |= (1 << 0);
  Engine::RAM::SetByte(cpu->hl, tmp);
}

// SET Instruction
// Set bit 0 from 8-bits register A

void CPU::Disasm::DisCB0xC7(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af >> 8);
  tmp |= (1 << 0);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
}

// SET Instruction
// Set bit 1 from 8-bits register B

void CPU::Disasm::DisCB0xC8(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc >> 8);
  tmp |= (1 << 1);
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
}

// SET Instruction
// Set bit 1 from 8-bits register C

void CPU::Disasm::DisCB0xC9(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc & 0xFF);
  tmp |= (1 << 1);
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 1 from 8-bits register D

void CPU::Disasm::DisCB0xCA(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de >> 8);
  tmp |= (1 << 1);
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
}

// SET Instruction
// Set bit 1 from 8-bits register E

void CPU::Disasm::DisCB0xCB(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de & 0xFF);
  tmp |= (1 << 1);
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 1 from 8-bits register H

void CPU::Disasm::DisCB0xCC(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl >> 8);
  tmp |= (1 << 1);
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
}

// SET Instruction
// Set bit 1 from 8-bits register L

void CPU::Disasm::DisCB0xCD(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl & 0xFF);
  tmp |= (1 << 1);
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 1 from 8-bits direct located at the address pointed by 16-bits register HL
// Save the result at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0xCE(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->hl);
  tmp |= (1 << 1);
  Engine::RAM::SetByte(cpu->hl, tmp);
}

// SET Instruction
// Set bit 1 from 8-bits register A

void CPU::Disasm::DisCB0xCF(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af >> 8);
  tmp |= (1 << 1);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
}

// SET Instruction
// Set bit 2 from 8-bits register B

void CPU::Disasm::DisCB0xD0(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc >> 8);
  tmp |= (1 << 2);
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
}

// SET Instruction
// Set bit 2 from 8-bits register C

void CPU::Disasm::DisCB0xD1(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc & 0xFF);
  tmp |= (1 << 2);
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 2 from 8-bits register D

void CPU::Disasm::DisCB0xD2(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de >> 8);
  tmp |= (1 << 2);
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
}

// SET Instruction
// Set bit 2 from 8-bits register E

void CPU::Disasm::DisCB0xD3(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de & 0xFF);
  tmp |= (1 << 2);
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 2 from 8-bits register H

void CPU::Disasm::DisCB0xD4(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl >> 8);
  tmp |= (1 << 2);
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
}

// SET Instruction
// Set bit 2 from 8-bits register L

void CPU::Disasm::DisCB0xD5(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl & 0xFF);
  tmp |= (1 << 2);
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 2 from 8-bits direct located at the address pointed by 16-bits register HL
// Save the result at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0xD6(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->hl);
  tmp |= (1 << 2);
  Engine::RAM::SetByte(cpu->hl, tmp);
}

// SET Instruction
// Set bit 2 from 8-bits register A

void CPU::Disasm::DisCB0xD7(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af >> 8);
  tmp |= (1 << 2);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
}

// SET Instruction
// Set bit 3 from 8-bits register B

void CPU::Disasm::DisCB0xD8(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc >> 8);
  tmp |= (1 << 3);
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
}

// SET Instruction
// Set bit 3 from 8-bits register C

void CPU::Disasm::DisCB0xD9(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc & 0xFF);
  tmp |= (1 << 3);
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 3 from 8-bits register D

void CPU::Disasm::DisCB0xDA(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de >> 8);
  tmp |= (1 << 3);
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
}

// SET Instruction
// Set bit 3 from 8-bits register E

void CPU::Disasm::DisCB0xDB(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de & 0xFF);
  tmp |= (1 << 3);
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 3 from 8-bits register H

void CPU::Disasm::DisCB0xDC(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl >> 8);
  tmp |= (1 << 3);
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
}

// SET Instruction
// Set bit 3 from 8-bits register L

void CPU::Disasm::DisCB0xDD(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl & 0xFF);
  tmp |= (1 << 3);
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 3 from 8-bits direct located at the address pointed by 16-bits register HL
// Save the result at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0xDE(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->hl);
  tmp |= (1 << 3);
  Engine::RAM::SetByte(cpu->hl, tmp);
}

// SET Instruction
// Set bit 3 from 8-bits register A

void CPU::Disasm::DisCB0xDF(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af >> 8);
  tmp |= (1 << 3);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
}

// SET Instruction
// Set bit 4 from 8-bits register B

void CPU::Disasm::DisCB0xE0(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc >> 8);
  tmp |= (1 << 4);
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
}

// SET Instruction
// Set bit 4 from 8-bits register C

void CPU::Disasm::DisCB0xE1(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc & 0xFF);
  tmp |= (1 << 4);
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 4 from 8-bits register D

void CPU::Disasm::DisCB0xE2(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de >> 8);
  tmp |= (1 << 4);
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
}

// SET Instruction
// Set bit 4 from 8-bits register E

void CPU::Disasm::DisCB0xE3(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de & 0xFF);
  tmp |= (1 << 4);
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 4 from 8-bits register H

void CPU::Disasm::DisCB0xE4(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl >> 8);
  tmp |= (1 << 4);
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
}

// SET Instruction
// Set bit 4 from 8-bits register L

void CPU::Disasm::DisCB0xE5(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl & 0xFF);
  tmp |= (1 << 4);
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 4 from 8-bits direct located at the address pointed by 16-bits register HL
// Save the result at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0xE6(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->hl);
  tmp |= (1 << 4);
  Engine::RAM::SetByte(cpu->hl, tmp);
}

// SET Instruction
// Set bit 4 from 8-bits register A

void CPU::Disasm::DisCB0xE7(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af >> 8);
  tmp |= (1 << 4);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
}

// SET Instruction
// Set bit 5 from 8-bits register B

void CPU::Disasm::DisCB0xE8(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc >> 8);
  tmp |= (1 << 5);
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
}

// SET Instruction
// Set bit 5 from 8-bits register C

void CPU::Disasm::DisCB0xE9(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc & 0xFF);
  tmp |= (1 << 5);
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 5 from 8-bits register D

void CPU::Disasm::DisCB0xEA(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de >> 8);
  tmp |= (1 << 5);
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
}

// SET Instruction
// Set bit 6 from 8-bits register E

void CPU::Disasm::DisCB0xEB(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de & 0xFF);
  tmp |= (1 << 5);
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 6 from 8-bits register H

void CPU::Disasm::DisCB0xEC(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl >> 8);
  tmp |= (1 << 5);
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
}

// SET Instruction
// Set bit 6 from 8-bits register L

void CPU::Disasm::DisCB0xED(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl & 0xFF);
  tmp |= (1 << 5);
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 5 from 8-bits direct located at the address pointed by 16-bits register HL
// Save the result at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0xEE(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->hl);
  tmp |= (1 << 5);
  Engine::RAM::SetByte(cpu->hl, tmp);
}

// SET Instruction
// Set bit 5 from 8-bits register A

void CPU::Disasm::DisCB0xEF(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af >> 8);
  tmp |= (1 << 5);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
}

// SET Instruction
// Set bit 6 from 8-bits register B

void CPU::Disasm::DisCB0xF0(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc >> 8);
  tmp |= (1 << 6);
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
}

// SET Instruction
// Set bit 6 from 8-bits register C

void CPU::Disasm::DisCB0xF1(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc & 0xFF);
  tmp |= (1 << 6);
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 6 from 8-bits register D

void CPU::Disasm::DisCB0xF2(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de >> 8);
  tmp |= (1 << 6);
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
}

// SET Instruction
// Set bit 6 from 8-bits register E

void CPU::Disasm::DisCB0xF3(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de & 0xFF);
  tmp |= (1 << 6);
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 6 from 8-bits register H

void CPU::Disasm::DisCB0xF4(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl >> 8);
  tmp |= (1 << 6);
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
}

// SET Instruction
// Set bit 6 from 8-bits register L

void CPU::Disasm::DisCB0xF5(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl & 0xFF);
  tmp |= (1 << 6);
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 6 from 8-bits direct located at the address pointed by 16-bits register HL
// Save the result at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0xF6(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->hl);
  tmp |= (1 << 6);
  Engine::RAM::SetByte(cpu->hl, tmp);
}

// SET Instruction
// Set bit 6 from 8-bits register A

void CPU::Disasm::DisCB0xF7(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af >> 8);
  tmp |= (1 << 6);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
}

// SET Instruction
// Set bit 7 from 8-bits register B

void CPU::Disasm::DisCB0xF8(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc >> 8);
  tmp |= (1 << 7);
  cpu->bc = (tmp << 8) + (cpu->bc & 0xFF);
}

// SET Instruction
// Set bit 7 from 8-bits register C

void CPU::Disasm::DisCB0xF9(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->bc & 0xFF);
  tmp |= (1 << 7);
  cpu->bc = ((cpu->bc >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 7 from 8-bits register D

void CPU::Disasm::DisCB0xFA(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de >> 8);
  tmp |= (1 << 7);
  cpu->de = (tmp << 8) + (cpu->de & 0xFF);
}

// SET Instruction
// Set bit 7 from 8-bits register E

void CPU::Disasm::DisCB0xFB(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->de & 0xFF);
  tmp |= (1 << 7);
  cpu->de = ((cpu->de >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 7 from 8-bits register H

void CPU::Disasm::DisCB0xFC(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl >> 8);
  tmp |= (1 << 7);
  cpu->hl = (tmp << 8) + (cpu->hl & 0xFF);
}

// SET Instruction
// Set bit 7 from 8-bits register L

void CPU::Disasm::DisCB0xFD(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->hl & 0xFF);
  tmp |= (1 << 7);
  cpu->hl = ((cpu->hl >> 8) << 8) + tmp;
}

// SET Instruction
// Set bit 7 from 8-bits direct located at the address pointed by 16-bits register HL
// Save the result at the address pointed by 16-bits register HL

void CPU::Disasm::DisCB0xFE(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = Engine::RAM::GetByte(cpu->hl);
  tmp |= (1 << 7);
  Engine::RAM::SetByte(cpu->hl, tmp);
}

// SET Instruction
// Set bit 7 from 8-bits register A

void CPU::Disasm::DisCB0xFF(CPU::Z80 *cpu) {
  uint8_t tmp;

  tmp = (cpu->af >> 8);
  tmp |= (1 << 7);
  cpu->af = (tmp << 8) + (cpu->af & 0xFF);
}
