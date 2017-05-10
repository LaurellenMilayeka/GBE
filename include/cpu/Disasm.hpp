#ifndef __DISASM_HPP__
#define __DISASM_HPP__

#include <stdint.h>
#include <stdio.h>
#include "RAM.hpp"
#include "Z80.hpp"

namespace CPU {

  class Disasm {

  public:

    static void Dis0x00();
    static void Dis0x01();
    static void Dis0x02();
    static void Dis0x03();
    static void Dis0x04();
    static void Dis0x05();
    static void Dis0x06();
    static void Dis0x07();
    static void Dis0x08();
    static void Dis0x09();
    static void Dis0x0A();
    static void Dis0x0B();
    static void Dis0x0C();
    static void Dis0x0D();
    static void Dis0x0E();
    static void Dis0x0F();
  };
};

#endif
