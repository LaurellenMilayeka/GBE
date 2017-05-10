#include "RAM.hpp"

unsigned int Engine::RAM::_ramSize = 0;
uint8_t *Engine::RAM::_ram = nullptr;

void Engine::RAM::Initialize() {
  Loader::ROM *rom = Loader::ROM::Instance();
  
  DEBUG_PRINT("Initializing RAM");
  switch (rom->GetMBCType()) {
  case ROMONLY:
    _ramSize = 0;
    break;
  case 0x01 ... 0x03:
    _ramSize = 32768;
    break;
  case 0x05 ... 0x06:
    _ramSize = 512*4;
    break;
  case 0x0F ... 0x13:
    _ramSize = 32768;
    break;
  case 0x15 ... 0x17:
    _ramSize = 32768;
    break;
  case 0x19 ... 0x1E:
    _ramSize = 131072;
    break;
  case 0x20:
    _ramSize = 131072;
    break;
  case 0x22:
    _ramSize = 131072;
    break;
  }
  if ((Engine::RAM::_ram = (uint8_t*)malloc(sizeof(uint8_t) * Engine::RAM::_ramSize)) == nullptr) {
    std::cerr << "Error allocation RAM" << std::endl;
    exit(EXIT_FAILURE);
  }
  DEBUG_PRINT("Setting all bytes to 0");
  memset(Engine::RAM::_ram, 0, Engine::RAM::_ramSize);
  DEBUG_PRINT("Done");
  DEBUG_PRINT("Loading first 16kb of ROM data in the first memory bank");
  Engine::RAM::GetROMChunk(0x0000, 0x3FFF);
  DEBUG_PRINT("Done");
}

uint8_t Engine::RAM::GetByte(uint16_t pos) {
  return (_ram[pos]);
}

void Engine::RAM::SetByte(uint16_t pos, uint8_t value) {
  _ram[pos] = value;
}

void Engine::RAM::GetROMChunk(uint16_t start, uint16_t end) {
  Loader::ROM *rom = Loader::ROM::Instance();

  memcpy(Engine::RAM::_ram, &(rom->GetROMData())[start], (end - start));
}

uint8_t *Engine::RAM::GetRAM() {
  return (Engine::RAM::_ram);
}
