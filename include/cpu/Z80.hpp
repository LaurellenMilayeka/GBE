#ifndef __Z80_HPP__
#define __z80_HPP__

#include <stdint.h>
#include <cstdlib>

namespace CPU {

  class Z80 {

    Z80();

    static Z80 *_singleton;
    
  public:

    ~Z80();
    static Z80 *Instance();
    static void Destroy();
    
    /* CPU varholders registers */

    uint16_t af;
    uint16_t bc;
    uint16_t de;
    uint16_t hl;

    /* Stack and program registers */

    uint16_t sp;
    uint16_t pc;

  };
  
};

#endif
