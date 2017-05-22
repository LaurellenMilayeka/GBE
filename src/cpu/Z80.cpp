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
