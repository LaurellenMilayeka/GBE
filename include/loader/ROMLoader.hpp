#pragma once

#include <stdint.h>
#include <cstring>
#include <iostream>
#include <fstream>

#include "Define.hpp"

enum CGB {
  COMPATIBLE,
  CGB_ONLY,
  GB_ONLY
};

enum CRT_TYPE {
  ROMONLY	= 0x00,
  MBC1		= 0x01,
  MBC1RAM	= 0x02,
  MBC1RAMBTRY	= 0x03,
  MBC2		= 0x05,
  MBC2BTRY	= 0x06,
  ROMRAM	= 0x08,
  ROMRAMBTRY	= 0x09,
  MMM01		= 0x0B,
  MMM01RAM	= 0x0C,
  MMM01RAMBTRY	= 0x0D,
  MBC3TMRBTRY	= 0x0F,
  MBC3TMRRAMBTRY= 0x10,
  MBC3		= 0X11,
  MBC3RAM	= 0x12,
  MBC3RAMBTRY	= 0x13,
  MBC4		= 0x15,
  MBC4RAM	= 0x16,
  MBC4RAMBTRY	= 0x17,
  MBC5		= 0x19,
  MBC5RAM	= 0x1A,
  MBC5RAMBTRY	= 0x1B,
  MBC5RMBL	= 0x1C,
  MBC5RMBLRAM	= 0x1D,
  MBC5RMBLRAMBTRY=0x1E,
  MBC6		= 0x20,
  MBC7SSRRMBLRAMBTRY = 0x22,
  PCKTCAM	= 0xFC,
  BANDAITAMA5	= 0xFD,
  HUC3		= 0xFE,
  HUC1RAMBTRY	= 0xFF
};

enum ROMSize {
  R32KB		= 0x00,
  R64KB		= 0x01,
  R128KB	= 0x02,
  R256KB	= 0x03,
  R512KB	= 0x04,
  R1MB		= 0x05,
  R2MB		= 0x06,
  R4MB		= 0x07,
  R8MB		= 0x08,
  R11MB		= 0x52,
  R12MB		= 0x53,
  R15MB		= 0x54
};

enum RAMSize {
  NONE		= 0x00,
  RA2KB		= 0x01,
  RA8KB		= 0x02,
  RA32KB	= 0x03,
  RA128KB	= 0x04,
  RA64KB	= 0x05
};

namespace Loader {

  class ROM {

    uint8_t	_nintendoScrollingGraphics[48];
    uint8_t	_name[16];
    uint8_t	_manufacturer[4];
    CGB		_cgbFunctions;
    uint8_t	_licenseeCode[2];
    CGB		_sgbFunctions;
    uint8_t	_memoryBank;
    size_t	_romSize;
    uint8_t	_ramSize;
    uint8_t	_destination;
    uint8_t	_maskROMVersion;
    uint8_t	_headerChecksum;
    uint16_t	_globalChecksum;
    uint8_t	*_romData;
    
    static ROM	*_singleton;
    
    ROM();
    
  public:

    ~ROM();

    static ROM *Instance();
    static void Destroy();
    
    void	Load(const char *);
    void	Unload();

    uint8_t	GetMBCType() const;
    uint8_t	*GetROMData() const;
  };
};
