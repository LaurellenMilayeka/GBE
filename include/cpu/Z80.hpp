#pragma once

#include <stdint.h>
#include <cstdlib>
#include "RAM.hpp"

#define FREQUENCY 4194304

namespace CPU {

  typedef enum IState {
    VBLANK =	0x01,
    LCD	=	0x02,
    TIMER =	0x04,
    SERIAL =	0x08,
    JOYPAD =	0x10
  } InterruptState;
  
  typedef struct s_timer_clock {
    int t;
    int m;
  } CLOCK;
  
  class Z80 {

    Z80();

    static Z80 *_singleton;
    
  public:

    ~Z80();
    static Z80 *Instance();
    static void Destroy();

    void Tick();
    
    /* CPU varholders registers */

    uint16_t af;
    uint16_t bc;
    uint16_t de;
    uint16_t hl;

    /* Stack and program registers */

    uint16_t sp;
    uint16_t pc;

    /* Interrupt registers */
    uint8_t ime;
    InterruptState iState;

    /* Clock */
    
    CLOCK    clock;

    uint8_t	nextInstructionDuration;
  };
  
};
