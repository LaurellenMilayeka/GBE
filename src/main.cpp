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
#include "IRAM.hpp"
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
  dprintf(1, "[DEBUG] : LCDC Value : 0x%02X\n", Engine::RAM::GetByte(0xFF40));
  dprintf(1, "[DEBUG] : STAT Value : 0x%02X\n", Engine::RAM::GetByte(0xFF41));
  dprintf(1, "[DEBUG] : LY Value : 0x%02X\n", Engine::RAM::GetByte(0xFF44));
  dprintf(1, "[DEBUG] : CNT Value : 0x%02X\n", Engine::RAM::GetByte(0xFF40));
  dprintf(1, "[DEBUG] : IE Value : 0x%02X\n", Engine::RAM::GetByte(0xFFFF));
  dprintf(1, "[DEBUG] : IF Value : 0x%02X\n", Engine::RAM::GetByte(0xFF0F));
  dprintf(1, "[DEBUG] : IME Value : 0x%02X\n", cpu->ime);
}

void GPURegDump(Graphics::GPU *gpu) {
  dprintf(1, "[DEBUG] : LCD Control Status :\n");
  dprintf(1, "[DEBUG] : \t0xFF40 Value : 0x%02X\n", Engine::RAM::GetByte(0xFF40));
  dprintf(1, "[DEBUG] : \tLine being treated : %d\n", Engine::RAM::GetByte(0xFF44));
  dprintf(1, "[DEBUG] : \tScrollY Register : %d\n", Engine::RAM::GetByte(0xFF42));
  dprintf(1, "[DEBUG] : \tScrollX Register : %d\n", Engine::RAM::GetByte(0xFF43));
}

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
  Engine::RAM::SetByte(0xFF00, 0xCF, false);
  Engine::RAM::SetByte(0xFF05, 0x00, false);
  Engine::RAM::SetByte(0xFF06, 0x00, false);
  Engine::RAM::SetByte(0xFF07, 0x00, false);
  Engine::RAM::SetByte(0xFF10, 0x80, false);
  Engine::RAM::SetByte(0xFF11, 0xBF, false);
  Engine::RAM::SetByte(0xFF12, 0xF3, false);
  Engine::RAM::SetByte(0xFF14, 0xBF, false);
  Engine::RAM::SetByte(0xFF16, 0x3F, false);
  Engine::RAM::SetByte(0xFF17, 0x00, false);
  Engine::RAM::SetByte(0xFF19, 0xBF, false);
  Engine::RAM::SetByte(0xFF1A, 0x7F, false);
  Engine::RAM::SetByte(0xFF1B, 0xFF, false);
  Engine::RAM::SetByte(0xFF1C, 0x9F, false);
  Engine::RAM::SetByte(0xFF1E, 0xBF, false);
  Engine::RAM::SetByte(0xFF20, 0xFF, false);
  Engine::RAM::SetByte(0xFF21, 0x00, false);
  Engine::RAM::SetByte(0xFF22, 0x00, false);
  Engine::RAM::SetByte(0xFF23, 0xBF, false);
  Engine::RAM::SetByte(0xFF24, 0x77, false);
  Engine::RAM::SetByte(0xFF25, 0xF3, false);
  Engine::RAM::SetByte(0xFF26, 0xF1, false);
  Engine::RAM::SetByte(0xFF40, 0x91, false);
  Engine::RAM::SetByte(0xFF41, 0x85, false);
  Engine::RAM::SetByte(0xFF42, 0x00, false);
  Engine::RAM::SetByte(0xFF43, 0x00, false);
  Engine::RAM::SetByte(0xFF45, 0x00, false);
  Engine::RAM::SetByte(0xFF47, 0xFC, false);
  Engine::RAM::SetByte(0xFF48, 0xFF, false);
  Engine::RAM::SetByte(0xFF49, 0xFF, false);
  Engine::RAM::SetByte(0xFF4A, 0x00, false);
  Engine::RAM::SetByte(0xFF4B, 0x00, false);
  Engine::RAM::SetByte(0xFF0F, 0xE1, false);
  Engine::RAM::SetByte(0xFFFF, 0x00, false);
  Engine::RAM::GetROMChunk(0x0000, 0x0000, 0x0100);
  cpu->_rom = true;
}

int main(int ac, char **av) {

  Loader::ROM *rom;
  CPU::Z80 *cpu;
  Graphics::GPU *gpu;
  int i;
  bool found;
  bool useDMG = true, running = true;
  uint8_t iFlags;

#ifdef STS_DBG

  bool sts = false;
  
#endif

  uint16_t prev_pc = 0;
  int count = 0;
  
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

    InitRegistersAndControls(cpu);
    useDMG = false;
    while (running) {
      i = 0;
      found = false;
      iFlags = Engine::RAM::GetByte(0xFF0F);
      
#ifndef NOGRAPHICS

      inputCheck = Engine::RAM::GetByte(0xFF00);
      while (SDL_PollEvent(&event)) {
	if (event.type == SDL_QUIT) {
	  running = false;
	} else if (event.type == SDL_KEYDOWN) {
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

      if (cpu->_halt != 1) {
	while (opcodes[i].byteLength != 0 && !found) {
	  if (Engine::RAM::GetByte(cpu->pc) == opcodes[i].code) {
	    
#ifdef DEBUG
	    
	    dprintf(1, "+-------------------------------START--------------------------------+\n");
	    dprintf(1, "[DEBUG] : Actual PC : 0x%04X\n", cpu->pc);
	    dprintf(1, "[DEBUG] : Instruction 0x%02X found\n", opcodes[i].code);
	    dprintf(1, "[DEBUG] : Instruction label : %s\n", opcodes[i].label);
	    
#endif
	    
	    /*if (cpu->pc == 0x288C) {
	      dprintf(1, "Instruction 0x288C reached\n");
	      GPURegDump(gpu);	    
	      RegDump(cpu);	  
	      exit(EXIT_SUCCESS);
	      }*/
	    if (cpu->pc == 0x00FE && useDMG) {
	      Engine::RAM::TurnOffDMGRom();
	      useDMG = false;
	      cpu->_rom = true;
	    }

	    opcodes[i].fptr(cpu);
	    cpu->nextInstructionDuration = opcodes[i].nbrClockCycles;
	    cpu->clock.t += opcodes[i].nbrClockCycles;
	    cpu->clock.m += opcodes[i].nbrClockCycles / 4;
	    cpu->Tick();
	    cpu->pc += opcodes[i].byteLength;

#ifdef DEBUG
	    GPURegDump(gpu);	    
	    RegDump(cpu);	  
	    dprintf(1, "+--------------------------------END---------------------------------+\n");
	      
	    if (prev_pc != cpu->pc) {
	      prev_pc = cpu->pc;
	      count = 0;
	    } else {
	      count++;
	    }
	    
	    if (count == 3) {
	      dprintf(1, "[DEBUG] : Infinite loop, quitting\n");
	      exit(EXIT_FAILURE);
	    }

#ifdef STS_DBG
		
		
	    if (cpu->pc == 0x2882) {
	      sts = true;
	    }
		
	    if (sts) {
	      dprintf(1, "Joypad : 0x%02X\n", Engine::RAM::GetByte(0xFF00));
	      getchar();
	    }
		
#endif
		
#endif
	    found = true;
	  }
	  i++;
	}
      } else {
	cpu->nextInstructionDuration = opcodes[i].nbrClockCycles;
	cpu->clock.t += opcodes[i].nbrClockCycles;
	cpu->clock.m += opcodes[i].nbrClockCycles / 4;
	cpu->Tick();
	cpu->pc += opcodes[i].byteLength;
      }
      
      uint8_t interruptRegister = Engine::RAM::GetByte(0xFFFF);

      if (((iFlags >> 0) & 1) == 1 && ((interruptRegister >> 0) & 1) == 1 && gpu->IsLCDEnabled()) {
	if (cpu->ime == 1) {
		
	  iFlags &= ~(1 << 0);
	  cpu->ime = 0;
	  cpu->sp -= 2;
	  Engine::RAM::SetByte(0xFF0F, iFlags);
	  Engine::RAM::SetByte(cpu->sp + 1, (cpu->pc >> 8));
	  Engine::RAM::SetByte(cpu->sp, (cpu->pc & 0xFF));
	  cpu->pc = 0x0040;

#ifdef DEBUG

	  dprintf(1, "VBLANK Interrupt\n");
		
#endif

	}
      } else if (((iFlags >> 1) & 1) == 1 && ((interruptRegister >> 1) & 1) == 1) {
	if (cpu->ime == 1) {

	  iFlags &= ~(1 << 1);
	  cpu->ime = 0;
	  cpu->sp -= 2;
	  Engine::RAM::SetByte(0xFF0F, iFlags);
	  Engine::RAM::SetByte(cpu->sp + 1, (cpu->pc >> 8));
	  Engine::RAM::SetByte(cpu->sp, (cpu->pc & 0xFF));
	  cpu->pc = 0x0048;

#ifdef DEBUG
		
	  dprintf(1, "STAT Interrupt\n");
		
#endif

	}
      } else if (((iFlags >> 2) & 1) == 1 && ((interruptRegister >> 2) & 1) == 1) {
	if (cpu->ime == 1) {

	  iFlags &= ~(1 << 2);
	  cpu->ime = 0;
	  cpu->sp -= 2;
	  Engine::RAM::SetByte(0xFF0F, iFlags);
	  Engine::RAM::SetByte(cpu->sp + 1, (cpu->pc >> 8));
	  Engine::RAM::SetByte(cpu->sp, (cpu->pc & 0xFF));
	  cpu->pc = 0x0050;
		
#ifdef DEBUG
		
	  dprintf(1, "Timer Interrupt\n");
		
#endif
	}
      } else if (((iFlags >> 3) & 1) == 1 && ((interruptRegister >> 3) & 1) == 1) {
	if (cpu->ime == 1) {

	  iFlags &= ~(1 << 3);
	  cpu->ime = 0;
	  cpu->sp -= 2;
	  Engine::RAM::SetByte(0xFF0F, iFlags);
	  Engine::RAM::SetByte(cpu->sp + 1, (cpu->pc >> 8));
	  Engine::RAM::SetByte(cpu->sp, (cpu->pc & 0xFF));
	  cpu->pc = 0x0058;
		  
#ifdef DEBUG
		  
	  dprintf(1, "Serial Interrupt\n");
		  
#endif
	}
      } else if (((iFlags >> 4) & 1) == 1 && ((interruptRegister >> 4) & 1) == 1) {
	if (cpu->ime == 1) {

	  iFlags &= ~(1 << 4);
	  cpu->ime = 0;
	  cpu->sp -= 2;
	  Engine::RAM::SetByte(0xFF0F, iFlags);
	  Engine::RAM::SetByte(cpu->sp + 1, (cpu->pc >> 8));
	  Engine::RAM::SetByte(cpu->sp, (cpu->pc & 0xFF));
	  cpu->pc = 0x0060;
		  
#ifdef DEBUG
		  
	  dprintf(1, "Joypad Interrupt\n");
		  
#endif
	}
      }

#ifndef NOGRPAHICS

      gpu->DrawScanLine(cpu);

#endif

      if (cpu->clock.t > 70224) {
	cpu->clock.t = 0;
	cpu->clock.m = 0;
	gpu->SetFrameStatus(false);
      }
    }
#ifdef DEBUG
    
    dprintf(1, "[DEBUG] : Nbr Refresh %d\n", gpu->_nbrRefresh);

#endif

    GPURegDump(gpu);	    
    RegDump(cpu);	  

  }
  return (0);
}
