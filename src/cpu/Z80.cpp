#include "Z80.hpp"

CPU::Z80 *CPU::Z80::_singleton = nullptr;

CPU::Z80::Z80() {

  this->af = 0x0000;
  this->bc = 0x0000;
  this->de = 0x0000;
  this->hl = 0x0000;

  this->sp = 0x0000;
  this->pc = 0x0000;

  this->clock.t = 0;
  this->clock.m = 0;

  this->_halt = 0;
  this->_rom = false;
}

CPU::Z80::~Z80() {

}

CPU::Z80 *CPU::Z80::Instance() {
  if (_singleton == NULL) {
    _singleton = new CPU::Z80();
  }
  return (_singleton);
}

void CPU::Z80::Destroy() {
  if (_singleton != NULL) {
    delete(_singleton);
  }
}

void CPU::Z80::Tick() {
  static uint16_t clock = 0;

#ifdef DEBUG
  
  dprintf(1, "[DEBUG] : DIV Register before function : 0x%02X\n", Engine::RAM::GetByte(0xFF04));
  dprintf(1, "[DEBUG] : Clock 8 lower bits : 0x%02X\n", clock & 0xFF);
  dprintf(1, "[DEBUG] : Clock 8 lower bits after addition : 0x%02X\n", (clock & 0xFF) + this->nextInstructionDuration);

#endif
  
  if (((((clock & 0xFF) & 0xFF) + (this->nextInstructionDuration & 0xFF)) & 0x100) == 0x100) {

#ifdef DEBUG
    
    dprintf(1, "[DEBUG] : Carry flag set, incrementing DIV register\n");

#endif

    Engine::RAM::SetByte(0xFF04, Engine::RAM::GetByte(0xFF04) + 1, false);
  }
  if (((Engine::RAM::GetByte(0xFF07) >> 2) & 1) == 1) {
    uint16_t frequency = 0;

    switch ((Engine::RAM::GetByte(0xFF07) & 3)) {
    case 0:
      frequency = 0x3FF;
      break;
    case 1:
      frequency = 0x10;
      break;
    case 2:
      frequency = 0x40;
      break;
    case 3:
      frequency = 0x100;
    }

#ifdef DEBUG
    
    dprintf(1, "[DEBUG] : TIMA Frequency  : %dHz\n", frequency);

#endif

    uint16_t tmp = ((clock & frequency) + (this->nextInstructionDuration & frequency)) & frequency;
    uint8_t tmpInc = (tmp < ((clock & frequency) + (this->nextInstructionDuration & frequency)) & frequency) ? 1 : 0;

    if ((Engine::RAM::GetByte(0xFF05) + tmpInc) > 0xFF) {
      uint8_t iFlags = Engine::RAM::GetByte(0xFF0F);
      
      iFlags |= (1 << 2);
      Engine::RAM::SetByte(0xFF05, Engine::RAM::GetByte(0xFF06));
      Engine::RAM::SetByte(0xFF0F, iFlags);
    } else {
      Engine::RAM::SetByte(0xFF05, Engine::RAM::GetByte(0xFF05) + tmpInc);
    }
  }
  clock += this->nextInstructionDuration;

#ifdef DEBUG
  
  dprintf(1, "[DEBUG] : DIV Register after function : 0x%02X\n", Engine::RAM::GetByte(0xFF04));
  dprintf(1, "[DEBUG] : TIMA Register after function : 0x%02X\n", Engine::RAM::GetByte(0xFF05));

#endif

}
