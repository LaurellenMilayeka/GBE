#include "Boot.hpp"

uint8_t Engine::Boot::_biosData[256] = {0};

void Engine::Boot::BootInit() {
  std::ifstream bios("BIOS/DMG_ROM.bin", std::ios::binary);

  memset(Engine::Boot::_biosData, 0, 256);
  bios.read((char*)Engine::Boot::_biosData, 256);
  DEBUG_PRINT("BIOS Loaded");

#ifdef DEBUG

  HexDump(Engine::Boot::_biosData, 0x0000, 0x00FF);

#endif
  
}

uint8_t *Engine::Boot::GetBiosData() {
  return (Engine::Boot::_biosData);
}

void Engine::Boot::UnloadBoot() {
  memset(Engine::Boot::_biosData, 0, 256);
}
