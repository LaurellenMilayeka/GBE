#ifndef __BOOT_HPP__
#define __BOOT_HPP__

#include <stdint.h>
#include <cstring>
#include <fstream>

#include "Define.hpp"

namespace Engine {

  class Boot {

    static uint8_t _biosData[256];
    
  public:
    static void BootInit();
    static void UnloadBoot();
  };

};

#endif
