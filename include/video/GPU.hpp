#ifndef __GPU_HPP__
#define __GPU_HPP__

#include <cstdint>

typedef enum GPU_REGISTER {

  SCROLLX = 0xFF43,
  SCROLLY = 0xFF42,
  CURRSLI = 0xFF44,
  BGPALET = 0xFF47
  
} GPU_REGISTER;

namespace Graphics {

  class GPU {

    static GPU *_singleton;

    uint8_t	_lcdc;
    uint8_t	_lcdStatus;
    
    GPU();
  public:

    static GPU *Instance();

    ~GPU();
    
    void EnableLCD();
    void EnableWindow();
    void EnableSpriteDisplay();

    void DisableLCD();
    void DisableWindow();
    void DisableSpriteDisplay();
    
    bool isLCDEnabled();
    bool isWindowDisplayEnabled();
    bool isSpriteDisplayEnabled();

    void SetLCDStatus(uint8_t status);

    
  };
};

#endif
