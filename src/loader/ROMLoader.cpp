#include <unistd.h>
#include "ROMLoader.hpp"

Loader::ROM *Loader::ROM::_singleton = nullptr;

Loader::ROM::ROM() {

}

Loader::ROM::~ROM() {

}

Loader::ROM *Loader::ROM::Instance() {
  if (_singleton == nullptr) {
    _singleton = new Loader::ROM();
  }
  return (_singleton);
}

void Loader::ROM::Destroy() {
  delete(_singleton);
}

size_t GetROMSize(const char *romPath) {
  std::ifstream mySource;

  mySource.open(romPath, std::ios_base::binary);
  mySource.seekg(0, std::ios_base::end);
  size_t size = mySource.tellg();
  mySource.close();
  return (size);
}

void Loader::ROM::Load(const char *romPath) {
  std::ifstream file(romPath);

  DEBUG_PRINT("Opening rom " << romPath);
  if (!file) {
    std::cerr << "[ERROR] : Could not open rom " << romPath << std::endl;
    DEBUG_PRINT("An error occured : " << std::strerror(errno));
  }
  this->_romSize = GetROMSize(romPath);
  if ((this->_romData = (uint8_t*)malloc(sizeof(uint8_t) * this->_romSize)) == NULL) {
    std::cerr << "[ERROR] : Error allocation ROM memory" << std::endl;
  }
  file.read((char*)this->_romData, this->_romSize);
  if (file) {
    std::cout << "[INFO] : ROM Loading complete" << std::endl;
    DEBUG_PRINT("Read " << this->_romSize << " bytes.");
  } else {
    std::cerr << "[ERROR] : A problem occured" << std::endl;
    DEBUG_PRINT("Could only read " << file.gcount() << " bytes out of " << this->_romSize);
    exit(EXIT_FAILURE);
  }
  DEBUG_PRINT("Temporary program counter initialized at 0x104");
  DEBUG_PRINT("Fetching nintendo scrolling graphics bytecode...");
  memcpy(this->_nintendoScrollingGraphics, &(this->_romData)[0x104], 48);
  DEBUG_PRINT("Fetched nintendo scrolling graphics bytecode");

#ifdef DEBUG
  int i;

  i = 0;
  while (i < 48) {
    if ((i % 16) == 0 && i != 0) {
      write(1, "\n", 1);
      dprintf(1, "[DEBUG] : ");
      dprintf(1, "0x%02X ", this->_nintendoScrollingGraphics[i]);
    } else if (i == 0) {
      dprintf(1, "[DEBUG] : ");
      dprintf(1, "0x%02X ", this->_nintendoScrollingGraphics[i]);
    } else {
      dprintf(1, "0x%02X ", this->_nintendoScrollingGraphics[i]);
    }
    i++;
  }
  dprintf(1, "\n");
#endif

    DEBUG_PRINT("Temporary program counter initialized at 0x134");
  DEBUG_PRINT("Fetching ROM title...");
  memcpy(this->_name, &(this->_romData)[0x134], 16);
  DEBUG_PRINT("Retrieved 16 bytes");
  DEBUG_PRINT("Fetched title : " << this->_name);
  std::cout << "[INFO] : ROM Title : " << this->_name << std::endl;
  DEBUG_PRINT("Temporary program counter initialized at 0x13F");
  DEBUG_PRINT("Fetching manufacturer code...");
  memcpy(this->_manufacturer, &(this->_romData)[0x13F], 4);
  DEBUG_PRINT("Retrieved 4 bytes");
  DEBUG_PRINT("Fetched manufacturer code : 0x" << std::hex << this->_manufacturer);
  DEBUG_PRINT("Temporary program counter initialized at 0x143");
  DEBUG_PRINT("Fetching CGB support...");
  if (this->_romData[0x143] == 0x80) {
    this->_cgbFunctions = COMPATIBLE;
    DEBUG_PRINT("CGB cartridge, C/GB compatible");
  } else if (this->_romData[0x143] == 0xC0) {
    this->_cgbFunctions = CGB_ONLY;
    DEBUG_PRINT("CGB cartridge, CGB only");
  } else {
    this->_cgbFunctions = GB_ONLY;
    DEBUG_PRINT("GB cartridge, GB only");
  }
  DEBUG_PRINT("Temporary program counter intialized at 0x144");
  DEBUG_PRINT("Fetching licensee code...");
  memcpy(this->_licenseeCode, &(this->_romData)[0x144], 2);
  DEBUG_PRINT("Fetched licensee code : " << this->_licenseeCode);
  DEBUG_PRINT("Temporary program counter initialized at 0x146");
  DEBUG_PRINT("Fetching SGB support...");
  if (this->_romData[0x146] == 0x03) {
    DEBUG_PRINT("Supports SGB functions");
    this->_sgbFunctions = COMPATIBLE;
  } else {
    DEBUG_PRINT("C/GB ROM only. SGB support skipped");
    this->_sgbFunctions = GB_ONLY;
  }
  DEBUG_PRINT("Temporary program counter initialized at 0x147");
  DEBUG_PRINT("Fetching cartridge type...");
  this->_memoryBank = this->_romData[0x147];
  switch (this->_memoryBank) {
  case ROMONLY:
    DEBUG_PRINT("Memory bank set to ROM ONLY");
    break;
  case MBC1:
    DEBUG_PRINT("Memory bank set to MBC1");
    break;
  case MBC1RAM:
    DEBUG_PRINT("Memory bank set to MBC1+RAM");
    break;
  case MBC1RAMBTRY:
    DEBUG_PRINT("Memory bank set to MBC1+RAM+BATTERY");
    break;
  case MBC2:
    DEBUG_PRINT("Memory bank set to MBC2");
    break;
  case MBC2BTRY:
    DEBUG_PRINT("Memory bank set to MBC2+BATTERY");
    break;
  case ROMRAM:
    DEBUG_PRINT("Memory bank set to ROM+RAM");
    break;
  case ROMRAMBTRY:
    DEBUG_PRINT("Memory bank set to ROM+RAM+BATTERY");
    break;
  case MMM01:
    DEBUG_PRINT("Memory bank set to MMM01");
    break;
  case MMM01RAM:
    DEBUG_PRINT("Memory bank set to MMM01+RAM");
    break;
  case MMM01RAMBTRY:
    DEBUG_PRINT("Memory bank set to MMM01+RAM+BATTERY");
    break;
  case MBC3TMRBTRY:
    DEBUG_PRINT("Memory bank set to MBC3+TIMER+BATTERY");
    break;
  case MBC3TMRRAMBTRY:
    DEBUG_PRINT("Memory bank set to MBC3+TIMER+RAM+BATTERY");
    break;
  case MBC3:
    DEBUG_PRINT("Memory bank set to MBC3");
    break;
  case MBC3RAM:
    DEBUG_PRINT("Memory bank set to MBC3+RAM");
    break;
  case MBC3RAMBTRY:
    DEBUG_PRINT("Memory bank set to MBC3+RAM+BATTERY");
    break;
  case MBC4:
    DEBUG_PRINT("Memory bank set to MBC4");
    break;
  case MBC4RAM:
    DEBUG_PRINT("Memory bank set to MBC4+RAM");
    break;
  case MBC4RAMBTRY:
    DEBUG_PRINT("Memory bank set to MBC4+RAM+BATTERY");
    break;
  case MBC5:
    DEBUG_PRINT("Memory bank set to MBC5");
    break;
  case MBC5RAM:
    DEBUG_PRINT("Memory bank set to MBC5+RAM");
    break;
  case MBC5RAMBTRY:
    DEBUG_PRINT("Memory bank set to MBC5+RAM+BATTERY");
    break;
  case MBC5RMBL:
    DEBUG_PRINT("Memory bank set to MBC5+RUMBLE");
    break;
  case MBC5RMBLRAM:
    DEBUG_PRINT("Memory bank set to MBC5+RUMBLE+RAM");
    break;
  case MBC5RMBLRAMBTRY:
    DEBUG_PRINT("Memory bank set to MBC5+RUMBLE+RAM+BATTERY");
    break;
  case MBC6:
    DEBUG_PRINT("Memory bank set to MBC6");
    break;
  case MBC7SSRRMBLRAMBTRY:
    DEBUG_PRINT("Memory bank set to MBC7+SENSOR+RUMBLE+RAM+BATTERY");
    break;
  case PCKTCAM:
    DEBUG_PRINT("Memory bank set to POCKET CAMERA");
    break;
  case BANDAITAMA5:
    DEBUG_PRINT("Memory bank set to BANDAI TAMA 5");
    break;
  case HUC3:
    DEBUG_PRINT("Memory bank set to HUC3");
    break;
  case HUC1RAMBTRY:
    DEBUG_PRINT("Memory bank set to HUC1+RAM+BATTERY");
    break;
  }
  DEBUG_PRINT("Fetched Memory bank");
  DEBUG_PRINT("Temporary program counter initialized at 0x148");
  DEBUG_PRINT("Fetching ROM size...");
  this->_romSize = this->_romData[0x148];
  switch (this->_romSize) {
  case R32KB:
    DEBUG_PRINT("ROM size set to 32kb");
    std::cout << "[INFO] : ROM size set to 32kb" << std::endl;
    break;
  case R64KB:
    DEBUG_PRINT("ROM size set to 64kb");
    std::cout << "[INFO] : ROM size set to 64kb" << std::endl;
    break;
  case R128KB:
    DEBUG_PRINT("ROM size set to 128kb");
    std::cout << "[INFO] : ROM size set to 128kb" << std::endl;
    break;
  case R256KB:
    DEBUG_PRINT("ROM size set to 256kb");
    std::cout << "[INFO] : ROM size set to 256kb" << std::endl;
    break;
  case R512KB:
    DEBUG_PRINT("ROM size set to 512kb");
    std::cout << "[INFO] : ROM size set to 512kb" << std::endl;
    break;
  case R1MB:
    DEBUG_PRINT("ROM size set to 1MB");
    std::cout << "[INFO] : ROM size set to 1MB" << std::endl;
    break;
  case R2MB:
    DEBUG_PRINT("ROM size set to 2MB");
    std::cout << "[INFO] : ROM size set to 2MB" << std::endl;
    break;
  case R4MB:
    DEBUG_PRINT("ROM size set to 4MB");
    std::cout << "[INFO] : ROM size set to 4MB" << std::endl;
    break;
  case R8MB:
    DEBUG_PRINT("ROM size set to 8MB");
    std::cout << "[INFO] : ROM size set to 8MB" << std::endl;
    break;
  case R11MB:
    DEBUG_PRINT("ROM size set to 1.1MB");
    std::cout << "[INFO] : ROM size set to 1.1MB" << std::endl;
    break;
  case R12MB:
    DEBUG_PRINT("ROM size set to 1.2MB");
    std::cout << "[INFO] : ROM size set to 1.2MB" << std::endl;
    break;
  case R15MB:
    DEBUG_PRINT("ROM size set to 1.5MB");
    std::cout << "[INFO] : ROM size set to 1.5MB" << std::endl;
    break;
  }
  DEBUG_PRINT("Fetched ROM size");
  DEBUG_PRINT("Temporary program counter initialized at 0x149");
  DEBUG_PRINT("Fetching RAM size...");
  this->_ramSize = this->_romData[0x149];
  switch (this->_ramSize) {
  case NONE:
    DEBUG_PRINT("RAM size set to NONE");
    std::cout << "[INFO] : RAM size set to NONE" << std::endl;
    break;
  case RA2KB:
    DEBUG_PRINT("RAM size set to 2kb");
    std::cout << "[INFO] : RAM size set to 2kb" << std::endl;
    break;
  case RA8KB:
    DEBUG_PRINT("RAM size set to 8kb");
    std::cout << "[INFO] : RAM size set to 8kb" << std::endl;
    break;
  case RA32KB:
    DEBUG_PRINT("RAM size set to 32kb");
    std::cout << "[INFO] : RAM size set to 32kb" << std::endl;
    break;
  case RA128KB:
    DEBUG_PRINT("RAM size set to 128kb");
    std::cout << "[INFO] : RAM size set to 128kb" << std::endl;
    break;
  case RA64KB:
    DEBUG_PRINT("RAM size set to 64kb");
    std::cout << "[INFO] : RAM size set to 64kb" << std::endl;
    break;
  }
  DEBUG_PRINT("Fetched RAM size");
  DEBUG_PRINT("Temporary program counter initialized at 0x14A");
  this->_destination = this->_romData[0x14A];
  DEBUG_PRINT("Fetched destination");
  DEBUG_PRINT("Found : " << std::hex << this->_destination);
  if (this->_destination == 0x00) {
    std::cout << "[INFO] : Japanese cartridge" << std::endl;
  } else {
    std::cout << "[INFO] : Non-japanese cartridge" << std::endl;
  }
  DEBUG_PRINT("Temporary program counter initialized at 0x14C");
  DEBUG_PRINT("Fetching mask ROM version...");
  this->_maskROMVersion = this->_romData[0x14C];
  DEBUG_PRINT("Fetched mask ROM version");
  DEBUG_PRINT("Mask ROM version is : " << std::hex << this->_maskROMVersion);
  DEBUG_PRINT("Temporary program counter initialized at 0x14D");
  DEBUG_PRINT("Fetching header checksum...");
  this->_headerChecksum = this->_romData[0x14D];
  DEBUG_PRINT("Fetched header checksum");
  DEBUG_PRINT("Header checksum value : " << std::hex << this->_headerChecksum);
  DEBUG_PRINT("Temporary program counter initialized at 0x14E");
  DEBUG_PRINT("Fetching global checksum...");
  this->_globalChecksum = this->_romData[0x14E];
  this->_globalChecksum <<= 8;
  this->_globalChecksum += this->_romData[0x14F];
  DEBUG_PRINT("Fetched global checksum");
  DEBUG_PRINT("Global checksum value : " << std::hex << this->_globalChecksum);
  file.close();
}

void Loader::ROM::Unload() {

}

uint8_t Loader::ROM::GetMBCType() const {
  return (this->_memoryBank);
}

uint8_t *Loader::ROM::GetROMData() const {
  return (this->_romData);
}
