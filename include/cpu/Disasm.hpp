#ifndef __DISASM_HPP__
#define __DISASM_HPP__

#include <stdint.h>
#include <stdio.h>
#include "RAM.hpp"
#include "Z80.hpp"

namespace CPU {

  class Disasm {

  public:

    static void Dis0x00(CPU::Z80*);
    static void Dis0x01(CPU::Z80*);
    static void Dis0x02(CPU::Z80*);
    static void Dis0x03(CPU::Z80*);
    static void Dis0x04(CPU::Z80*);
    static void Dis0x05(CPU::Z80*);
    static void Dis0x06(CPU::Z80*);
    static void Dis0x07(CPU::Z80*);
    static void Dis0x08(CPU::Z80*);
    static void Dis0x09(CPU::Z80*);
    static void Dis0x0A(CPU::Z80*);
    static void Dis0x0B(CPU::Z80*);
    static void Dis0x0C(CPU::Z80*);
    static void Dis0x0D(CPU::Z80*);
    static void Dis0x0E(CPU::Z80*);
    static void Dis0x0F(CPU::Z80*);
  };
};

#endif
