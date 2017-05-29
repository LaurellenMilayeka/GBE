#include "RAM.hpp"

unsigned int Engine::RAM::_ramSize = 0;
uint8_t *Engine::RAM::_ram = nullptr;

void Engine::RAM::Initialize() {
  Loader::ROM *rom = Loader::ROM::Instance();
  uint8_t timer;
  
  DEBUG_PRINT("Initializing RAM");
  switch (rom->GetMBCType()) {
  case ROMONLY:
    _ramSize = 131072;
    break;
  case 0x01 ... 0x03:
    _ramSize = 131072;
    break;
  case 0x05 ... 0x06:
    _ramSize = 131072;
    break;
  case 0x0F ... 0x13:
    _ramSize = 131072;
    break;
  case 0x15 ... 0x17:
    _ramSize = 131072;
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
  if ((Engine::RAM::_ram = (uint8_t*)malloc(sizeof(uint8_t) * _ramSize)) == nullptr) {
    std::cerr << "Error allocation RAM" << std::endl;
    exit(EXIT_FAILURE);
  }
  DEBUG_PRINT("Setting all bytes to 0");
  memset(Engine::RAM::_ram, 0, _ramSize);
  DEBUG_PRINT("Done");
  DEBUG_PRINT("Loading first 16kb of ROM data in the first memory bank");
  memset(Engine::RAM::_ram, 0, 0x9FFF - 0x8000);
  Engine::RAM::LoadBIOS();
  Engine::RAM::GetROMChunk(0x0100, 0x0100, 0x3FFF);
  timer = Engine::RAM::GetByte(0xFF07);
  timer |= (1 << 2);
  Engine::RAM::SetByte(0xFF07, timer);
  DEBUG_PRINT("Done");
}

uint8_t Engine::RAM::GetByte(uint16_t pos) {
  return (_ram[pos]);
}

uint8_t Engine::RAM::GetROMByte(uint16_t addr) {
  Loader::ROM *rom = Loader::ROM::Instance();

  return (rom->GetROMData()[addr]);
}

void Engine::RAM::SetByte(uint16_t pos, uint8_t value, bool user) {
  if (pos == 0xFF04 && user) {
    _ram[pos] = 0;
  } else {
    _ram[pos] = value;
  }
}

void Engine::RAM::LoadBIOS() {
  memcpy(Engine::RAM::_ram, Engine::Boot::GetBiosData(), 0x100);
}

void Engine::RAM::GetROMChunk(uint16_t startRAM, uint16_t start, uint16_t end) {
  Loader::ROM *rom = Loader::ROM::Instance();
  
  memcpy(&(Engine::RAM::_ram)[startRAM], &(rom->GetROMData())[start], (end - start));
}

uint8_t *Engine::RAM::GetRAM() {
  return (Engine::RAM::_ram);
}

void Engine::RAM::TurnOffDMGRom() {
  Engine::RAM::GetROMChunk(0x0000, 0x0000, 0x0100);
  HexDump(Engine::RAM::_ram, 0x0000, 0x0100);
}
