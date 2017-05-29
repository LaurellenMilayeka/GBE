#include <stdio.h>
#include <bitset>

#ifndef NOGRAPHICS

#include <SDL2/SDL.h>
#include "CoreWindow.hpp"

#endif

#include <thread>
#include "Opcodes.hpp"
#include "ROMLoader.hpp"
#include "Boot.hpp"
#include "RAM.hpp"
#include "DebugShell.hpp"
#include "GPU.hpp"
#include "Joypad.hpp"

void RegDump(CPU::Z80 *cpu) {
  dprintf(1, "[DEBUG] : AF Register : 0x%04X\n", cpu->af);
  dprintf(1, "[DEBUG] : \tFlags set :\n");
  dprintf(1, "[DEBUG] : \t\tZero flag : %s\n", ((((cpu->af & 0xFF) >> 7) & 1) == 1) ? "SET" : "NOT SET");
  dprintf(1, "[DEBUG] : \t\tOperation flag : %s\n", ((((cpu->af & 0xFF) >> 6) & 1) == 1) ? "SET" : "NOT SET");
  dprintf(1, "[DEBUG] : \t\tHalf Carry flag : %s\n", ((((cpu->af & 0xFF) >> 5) & 1) == 1) ? "SET" : "NOT SET");
  dprintf(1, "[DEBUG] : \t\tCarry flag : %s\n", ((((cpu->af & 0xFF) >> 4) & 1) == 1) ? "SET" : "NOT SET");
  dprintf(1, "[DEBUG] : BC Register : 0x%04X\n", cpu->bc);
  dprintf(1, "[DEBUG] : DE Register : 0x%04X\n", cpu->de);
  dprintf(1, "[DEBUG] : HL Register : 0x%04X\n", cpu->hl);
  dprintf(1, "[DEBUG] : SP Register : 0x%04X\n", cpu->sp);
  dprintf(1, "[DEBUG] : PC Register : 0x%04X\n", cpu->pc);  
  dprintf(1, "[DEBUG] : Clock _t Register : %d\n", cpu->clock.t);  
  dprintf(1, "[DEBUG] : Clock _m Register : %d\n", cpu->clock.m);
}

/*void GPURegDump(Graphics::GPU *gpu) {
  dprintf(1, "[DEBUG] : LCD Control Status :\n");
  dprintf(1, "[DEBUG] : \t0xFF40 Value : 0x%02X\n", Engine::RAM::GetByte(0xFF40));
  dprintf(1, "[DEBUG] : \tLCD Enabled : %s\n", (gpu->IsLCDEnabled()) ? "TRUE" : "FALSE");
  dprintf(1, "[DEBUG] : \tWindow Enabled : %s\n", (gpu->IsWindowDisplayEnabled()) ? "TRUE" : "FALSE");
  dprintf(1, "[DEBUG] : \tSprite Display Enabled : %s\n", (gpu->IsSpriteDisplayEnabled()) ? "TRUE" : "FALSE");
  dprintf(1, "[DEBUG] : \tBackground Enabled : %s\n", (gpu->IsBackgroundEnabled()) ? "TRUE" : "FALSE");
  dprintf(1, "[DEBUG] : \tAddress plage for Window tile map : %s\n", (gpu->GetWindowTileMapDisplaySelect()) ? "0x9C00-0x9FFF" : "0x9800-0x9BFF");
  dprintf(1, "[DEBUG] : \tAddress plage for Background and Window tile data : %s\n", (gpu->GetBGWindowTileDataSelect()) ? "0x8000-0x8FFF" : "0x8800-0x97FF");
  dprintf(1, "[DEBUG] : \tAddress plage for Background display : %s\n", (gpu->GetBGTileMapDisplaySelect()) ? "0x9C00-0x9FFF" : "0x9800-0x9BFF");
  dprintf(1, "[DEBUG] : \tSprite size in pixels : %s\n", (gpu->GetSpriteSize()) ? "8x16" : "8x8");
  dprintf(1, "[DEBUG] : \tLine being treated : %d\n", Engine::RAM::GetByte(0xFF44));
  }*/

void Addr0xFFXDump() {
  dprintf(1, "[DEBUG] : [0xFF05] = 0x%02X\n", Engine::RAM::GetByte(0xFF05));
  dprintf(1, "[DEBUG] : [0xFF06] = 0x%02X\n", Engine::RAM::GetByte(0xFF06));
  dprintf(1, "[DEBUG] : [0xFF07] = 0x%02X\n", Engine::RAM::GetByte(0xFF07));
  dprintf(1, "[DEBUG] : [0xFF10] = 0x%02X\n", Engine::RAM::GetByte(0xFF10));
  dprintf(1, "[DEBUG] : [0xFF11] = 0x%02X\n", Engine::RAM::GetByte(0xFF11));
  dprintf(1, "[DEBUG] : [0xFF12] = 0x%02X\n", Engine::RAM::GetByte(0xFF12));
  dprintf(1, "[DEBUG] : [0xFF14] = 0x%02X\n", Engine::RAM::GetByte(0xFF14));
  dprintf(1, "[DEBUG] : [0xFF16] = 0x%02X\n", Engine::RAM::GetByte(0xFF16));
  dprintf(1, "[DEBUG] : [0xFF17] = 0x%02X\n", Engine::RAM::GetByte(0xFF17));
  dprintf(1, "[DEBUG] : [0xFF19] = 0x%02X\n", Engine::RAM::GetByte(0xFF19));
  dprintf(1, "[DEBUG] : [0xFF1A] = 0x%02X\n", Engine::RAM::GetByte(0xFF1A));
  dprintf(1, "[DEBUG] : [0xFF1B] = 0x%02X\n", Engine::RAM::GetByte(0xFF1B));
  dprintf(1, "[DEBUG] : [0xFF1C] = 0x%02X\n", Engine::RAM::GetByte(0xFF1C));
  dprintf(1, "[DEBUG] : [0xFF1E] = 0x%02X\n", Engine::RAM::GetByte(0xFF1E));
  dprintf(1, "[DEBUG] : [0xFF20] = 0x%02X\n", Engine::RAM::GetByte(0xFF20));
  dprintf(1, "[DEBUG] : [0xFF21] = 0x%02X\n", Engine::RAM::GetByte(0xFF21));
  dprintf(1, "[DEBUG] : [0xFF22] = 0x%02X\n", Engine::RAM::GetByte(0xFF22));
  dprintf(1, "[DEBUG] : [0xFF23] = 0x%02X\n", Engine::RAM::GetByte(0xFF23));
  dprintf(1, "[DEBUG] : [0xFF24] = 0x%02X\n", Engine::RAM::GetByte(0xFF24));
  dprintf(1, "[DEBUG] : [0xFF25] = 0x%02X\n", Engine::RAM::GetByte(0xFF25));
  dprintf(1, "[DEBUG] : [0xFF26] = 0x%02X\n", Engine::RAM::GetByte(0xFF26));
  dprintf(1, "[DEBUG] : [0xFF40] = 0x%02X\n", Engine::RAM::GetByte(0xFF40));
  dprintf(1, "[DEBUG] : [0xFF42] = 0x%02X\n", Engine::RAM::GetByte(0xFF42));
  dprintf(1, "[DEBUG] : [0xFF43] = 0x%02X\n", Engine::RAM::GetByte(0xFF43));
  dprintf(1, "[DEBUG] : [0xFF45] = 0x%02X\n", Engine::RAM::GetByte(0xFF45));
  dprintf(1, "[DEBUG] : [0xFF47] = 0x%02X\n", Engine::RAM::GetByte(0xFF47));
  dprintf(1, "[DEBUG] : [0xFF48] = 0x%02X\n", Engine::RAM::GetByte(0xFF48));
  dprintf(1, "[DEBUG] : [0xFF49] = 0x%02X\n", Engine::RAM::GetByte(0xFF49));
  dprintf(1, "[DEBUG] : [0xFF4A] = 0x%02X\n", Engine::RAM::GetByte(0xFF4A));
  dprintf(1, "[DEBUG] : [0xFF4B] = 0x%02X\n", Engine::RAM::GetByte(0xFF4B));
  dprintf(1, "[DEBUG] : [0xFFFF] = 0x%02X\n", Engine::RAM::GetByte(0xFFFF));
}

void InitRegistersAndControls(CPU::Z80 *cpu) {
  cpu->af = 0x01B0;
  cpu->bc = 0x0013;
  cpu->de = 0x00D8;
  cpu->hl = 0x014D;
  cpu->sp = 0xFFFE;
  cpu->pc = 0x0100;
  Engine::RAM::SetByte(0xFF05, 0x00);
  Engine::RAM::SetByte(0xFF06, 0x00);
  Engine::RAM::SetByte(0xFF07, 0x00);
  Engine::RAM::SetByte(0xFF10, 0x80);
  Engine::RAM::SetByte(0xFF11, 0xBF);
  Engine::RAM::SetByte(0xFF12, 0xF3);
  Engine::RAM::SetByte(0xFF14, 0xBF);
  Engine::RAM::SetByte(0xFF16, 0x3F);
  Engine::RAM::SetByte(0xFF17, 0x00);
  Engine::RAM::SetByte(0xFF19, 0xBF);
  Engine::RAM::SetByte(0xFF1A, 0x7F);
  Engine::RAM::SetByte(0xFF1B, 0xFF);
  Engine::RAM::SetByte(0xFF1C, 0x9F);
  Engine::RAM::SetByte(0xFF1E, 0xBF);
  Engine::RAM::SetByte(0xFF20, 0xFF);
  Engine::RAM::SetByte(0xFF21, 0x00);
  Engine::RAM::SetByte(0xFF22, 0x00);
  Engine::RAM::SetByte(0xFF23, 0xBF);
  Engine::RAM::SetByte(0xFF24, 0x77);
  Engine::RAM::SetByte(0xFF25, 0xF3);
  Engine::RAM::SetByte(0xFF26, 0xF1);
  Engine::RAM::SetByte(0xFF40, 0x91);
  Engine::RAM::SetByte(0xFF42, 0x00);
  Engine::RAM::SetByte(0xFF43, 0x00);
  Engine::RAM::SetByte(0xFF45, 0x00);
  Engine::RAM::SetByte(0xFF47, 0xFC);
  Engine::RAM::SetByte(0xFF48, 0xFF);
  Engine::RAM::SetByte(0xFF49, 0xFF);
  Engine::RAM::SetByte(0xFF4A, 0x00);
  Engine::RAM::SetByte(0xFF4B, 0x00);
  Engine::RAM::SetByte(0xFFFF, 0x00);
  Engine::RAM::GetROMChunk(0x0000, 0x0000, 0x0100);
}

int main(int ac, char **av) {

  Loader::ROM *rom;
  CPU::Z80 *cpu;
  Graphics::GPU *gpu;
  int i;
  bool found;
  bool useDMG = true, running = true;
  uint8_t iFlags;
  
#ifndef NOGRAPHICS
  
  uint8_t inputCheck;
  Core::Window *window;
  SDL_Event event;

#endif
  
  if (ac == 2) {

#ifndef NOGRAPHICS
    
    window = Core::Window::Instance();
    window->Init("GBEmulator", 160, 144);

#endif
    
    cpu = CPU::Z80::Instance();
    Engine::Boot::BootInit();
    rom = Loader::ROM::Instance();
    rom->Load(av[1]);
    Engine::RAM::Initialize();
    gpu = Graphics::GPU::Instance();

    //InitRegistersAndControls(cpu);
    //useDMG = false;
    while (running) {
      i = 0;
      found = false;
      iFlags = Engine::RAM::GetByte(0xFF0F);
      
#ifndef NOGRAPHICS

      inputCheck = Engine::RAM::GetByte(0xFF00);
      while (SDL_PollEvent(&event)) {
	if (event.type == SDL_QUIT) {
	  running = false;
	} else if (event.type = SDL_KEYDOWN) {
	  Engine::Joypad::ProcessEvent(event);
	}
      }

      if (inputCheck != Engine::RAM::GetByte(0xFF00)) {
	inputCheck = Engine::RAM::GetByte(0xFF00);
	if (((inputCheck >> 5) & 1) == 0) {
	  if (((inputCheck >> 0) & 1) == 0) {
	    dprintf(1, "[DEBUG] : A Button pressed\n");
	  } else if (((inputCheck >> 1) & 1) == 0) {
	    dprintf(1, "[DEBUG] : B Button pressed\n");
	  } else if (((inputCheck >> 2) & 1) == 0) {
	    dprintf(1, "[DEBUG] : SELECT Button pressed\n");
	  } else if (((inputCheck >> 3) & 1) == 0) {
	    dprintf(1, "[DEBUG] : START Button pressed\n");
	  }
	} else if (((inputCheck >> 4) & 1) == 0) {
	  if (((inputCheck >> 0) & 1) == 0) {
	    dprintf(1, "[DEBUG] : RIGHT Button pressed\n");
	  } else if (((inputCheck >> 1) & 1) == 0) {
	    dprintf(1, "[DEBUG] : LEFT Button pressed\n");
	  } else if (((inputCheck >> 2) & 1) == 0) {
	    dprintf(1, "[DEBUG] : UP Button pressed\n");
	  } else if (((inputCheck >> 3) & 1) == 0) {
	    dprintf(1, "[DEBUG] : DOWN Button pressed\n");
	  }
	}
      }

#endif
      
      while (opcodes[i].byteLength != 0 && !found) {
	if (Engine::RAM::GetByte(cpu->pc) == opcodes[i].code) {

#ifdef DEBUG

	  dprintf(1, "+-------------------------------START--------------------------------+\n");
	  dprintf(1, "[DEBUG] : Actual PC : 0x%04X\n", cpu->pc);
	  dprintf(1, "[DEBUG] : Instruction 0x%02X found\n", opcodes[i].code);
	  dprintf(1, "[DEBUG] : Instruction label : %s\n", opcodes[i].label);

#endif

	  if (cpu->pc == 0x00FE && useDMG) {
	    Engine::RAM::TurnOffDMGRom();
	    useDMG = false;
	  }
	  
	  opcodes[i].fptr(cpu);
	  cpu->nextInstructionDuration = opcodes[i].nbrClockCycles;
	  cpu->clock.t += opcodes[i].nbrClockCycles;
	  cpu->clock.m += opcodes[i].nbrClockCycles / 4;
	  cpu->Tick();
	  cpu->pc += opcodes[i].byteLength;

	  if (cpu->ime == 1) {
	    uint8_t interruptRegister = Engine::RAM::GetByte(0xFFFF);

	    if (((iFlags >> 0) & 1) == 1 && ((interruptRegister >> 0) & 1) == 1) {
	      iFlags &= ~(1 << 0);
	      cpu->ime = 0;
	      cpu->sp -= 2;
	      Engine::RAM::SetByte(0xFF0F, iFlags);
	      Engine::RAM::SetByte(cpu->sp + 1, (cpu->pc >> 8));
	      Engine::RAM::SetByte(cpu->sp, (cpu->pc & 0xFF));
	      cpu->pc = 0x0040;
	    } else if (((iFlags >> 1) & 1) == 1 && ((interruptRegister >> 1) & 1) == 1) {
	      iFlags &= ~(1 << 1);
	      cpu->ime = 0;
	      cpu->sp -= 2;
	      Engine::RAM::SetByte(0xFF0F, iFlags);
	      Engine::RAM::SetByte(cpu->sp + 1, (cpu->pc >> 8));
	      Engine::RAM::SetByte(cpu->sp, (cpu->pc & 0xFF));
	      cpu->pc = 0x0048;
	    } else if (((iFlags >> 2) & 1) == 1 && ((interruptRegister >> 2) & 1) == 1) {
	      iFlags &= ~(1 << 2);
	      cpu->ime = 0;
	      cpu->sp -= 2;
	      Engine::RAM::SetByte(0xFF0F, iFlags);
	      Engine::RAM::SetByte(cpu->sp + 1, (cpu->pc >> 8));
	      Engine::RAM::SetByte(cpu->sp, (cpu->pc & 0xFF));
	      cpu->pc = 0x0050;
	    } else if (((iFlags >> 3) & 1) == 1 && ((interruptRegister >> 3) & 1) == 1) {
	      iFlags &= ~(1 << 3);
	      cpu->ime = 0;
	      cpu->sp -= 2;
	      Engine::RAM::SetByte(0xFF0F, iFlags);
	      Engine::RAM::SetByte(cpu->sp + 1, (cpu->pc >> 8));
	      Engine::RAM::SetByte(cpu->sp, (cpu->pc & 0xFF));
	      cpu->pc = 0x0058;
	    } else if (((iFlags >> 4) & 1) == 1 && ((interruptRegister >> 4) & 1) == 1) {
	      iFlags &= ~(1 << 4);
	      cpu->ime = 0;
	      cpu->sp -= 2;
	      Engine::RAM::SetByte(0xFF0F, iFlags);
	      Engine::RAM::SetByte(cpu->sp + 1, (cpu->pc >> 8));
	      Engine::RAM::SetByte(cpu->sp, (cpu->pc & 0xFF));
	      cpu->pc = 0x0060;
	    }
	  }

#ifdef DEBUG
	  
	  RegDump(cpu);	  
	  dprintf(1, "+--------------------------------END---------------------------------+\n");

#ifdef STS_DBG
	  
	  getchar();

#endif
	  
#endif
	  found = true;
	}
	i++;
      }
      
#ifndef NOGRPAHICS

      gpu->DrawScanLine(cpu);

#endif

      if (cpu->clock.t > 70224) {
	cpu->clock.t = 0;
	cpu->clock.m = 0;
      }
    }
#ifdef DEBUG
    
    dprintf(1, "[DEBUG] : Nbr Refresh %d\n", gpu->_nbrRefresh);

#endif
    
  }
  return (0);
}
