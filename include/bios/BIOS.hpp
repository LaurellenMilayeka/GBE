#ifndef __BIOS_HPP__
#define __BIOS_HPP__

#include <stdint.h>
#include <iostream>

#include "ROMLoader.hpp"
#include "Define.hpp"
#include "RAM.hpp"

namespace Engine {

  class BIOS {

    static uint8_t _nintendoBIOSVerification[48];

  public:

    static void CheckBIOSIntegrity();
    
  };
  
};

#endif
