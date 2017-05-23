#pragma once

#include <cstdint>
#include "Z80.hpp"

#define GB_SCR_HEIGHT	144
#define GB_SCR_WIDTH	160

typedef enum GPU_REGISTER {

  SCROLLX = 0xFF43,
  SCROLLY = 0xFF42,
  CURRSLI = 0xFF44,
  BGPALET = 0xFF47
  
} GPU_REGISTER;

typedef struct GPU_TILE_PLAGE {

  uint16_t start;
  uint16_t end;
  
} TileOffset;

namespace Graphics {

  typedef struct s_pixel_value {
    uint8_t		r;
    uint8_t		g;
    uint8_t		b;
    uint8_t		a;
  } RGBAPixValue;
  
  class GPU {

    static GPU *	_singleton;

    uint8_t		_lcdc;
    uint8_t		_lcdStatus;
    RGBAPixValue	_data[144][160];
    uint16_t		_clock;
    uint8_t		_actualLine;
    unsigned int	_nbrRefresh;

    TileOffset		_windowTile;
    TileOffset		_bgWindowTile;
    TileOffset		_bgTile;
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
    
    bool IsLCDEnabled();
    bool IsWindowDisplayEnabled();
    bool IsSpriteDisplayEnabled();
    bool IsBackgroundEnabled();
    
    bool GetWindowTileMapDisplaySelect();
    bool GetBGWindowTileDataSelect();
    bool GetBGTileMapDisplaySelect();
    bool GetSpriteSize();

    unsigned int GetTotalRefreshes();
    
    void SetLCDStatus(uint8_t status);

    void Tick(CPU::Z80 *);
    void Process();
  };
};
