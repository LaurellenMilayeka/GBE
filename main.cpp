#include <iostream>
#include <OpCodes.hpp>
#include <Loader.hpp>
#include <Debug.hpp>
#include <RAM.hpp>
#include <CPU.hpp>
#include <GPU.hpp>
#include <Display.hpp>
#include <cstring>

using namespace GBE;

void InitNintendoLogo() {
    /**
     * $CE,$ED,$66,$66,$CC,$0D,$00,$0B,$03,$73,$00,$83,$00,$0C,$00,$0D
	 * $00,$08,$11,$1F,$88,$89,$00,$0E,$DC,$CC,$6E,$E6,$DD,$DD,$D9,$99
     * $BB,$BB,$67,$63,$6E,$0E,$EC,$CC,$DD,$DC,$99,$9F,$BB,$B9,$33,$3E
     */
     RAM::Write8((Byte)0xCE, 0x0104);     RAM::Write8((Byte)0xED, 0x0105);     RAM::Write8((Byte)0x66, 0x0106);     RAM::Write8((Byte)0x66, 0x0107);
     RAM::Write8((Byte)0xCC, 0x0108);     RAM::Write8((Byte)0x0D, 0x0109);     RAM::Write8((Byte)0x00, 0x010A);     RAM::Write8((Byte)0x0B, 0x010B);
     RAM::Write8((Byte)0x03, 0x010C);     RAM::Write8((Byte)0x73, 0x010D);     RAM::Write8((Byte)0x00, 0x010E);     RAM::Write8((Byte)0x83, 0x010F);
     RAM::Write8((Byte)0x00, 0x0110);     RAM::Write8((Byte)0x0C, 0x0111);     RAM::Write8((Byte)0x00, 0x0112);     RAM::Write8((Byte)0x0D, 0x0113);
     RAM::Write8((Byte)0x00, 0x0114);     RAM::Write8((Byte)0x08, 0x0115);     RAM::Write8((Byte)0x11, 0x0116);     RAM::Write8((Byte)0x1F, 0x0117);
     RAM::Write8((Byte)0x88, 0x0118);     RAM::Write8((Byte)0x89, 0x0119);     RAM::Write8((Byte)0x00, 0x011A);     RAM::Write8((Byte)0x0E, 0x011B);
     RAM::Write8((Byte)0xDC, 0x011C);     RAM::Write8((Byte)0xCC, 0x011D);     RAM::Write8((Byte)0x6E, 0x011E);     RAM::Write8((Byte)0xE6, 0x011F);
     RAM::Write8((Byte)0xDD, 0x0120);     RAM::Write8((Byte)0xDD, 0x0121);     RAM::Write8((Byte)0xD9, 0x0122);     RAM::Write8((Byte)0x99, 0x0123);
     RAM::Write8((Byte)0xBB, 0x0124);     RAM::Write8((Byte)0xBB, 0x0125);     RAM::Write8((Byte)0x67, 0x0126);     RAM::Write8((Byte)0x63, 0x0127);
     RAM::Write8((Byte)0x6E, 0x0128);     RAM::Write8((Byte)0x0E, 0x0129);     RAM::Write8((Byte)0xEC, 0x012A);     RAM::Write8((Byte)0xCC, 0x012B);
     RAM::Write8((Byte)0xDD, 0x012C);     RAM::Write8((Byte)0xDC, 0x012D);     RAM::Write8((Byte)0x99, 0x012E);     RAM::Write8((Byte)0x9F, 0x012F);
     RAM::Write8((Byte)0xBB, 0x0130);     RAM::Write8((Byte)0xB9, 0x0131);     RAM::Write8((Byte)0x33, 0x0132);     RAM::Write8((Byte)0x3E, 0x0133);
}

void InitRegisters(CPU &cpu) {
    cpu.SetRegistry16Value(Registry16::AF, 0x1180);
    cpu.SetRegistry16Value(Registry16::BC, 0x0000);
    cpu.SetRegistry16Value(Registry16::DE, 0xFF56);
    cpu.SetRegistry16Value(Registry16::HL, 0x000D);
    cpu.SetRegistry16Value(Registry16::SP, 0xFFFE);

    RAM::Write8(0x00, 0xFF05);
    RAM::Write8(0x00, 0xFF06);
    RAM::Write8(0x00, 0xFF07);
    RAM::Write8(0x80, 0xFF10);
    RAM::Write8(0xBF, 0xFF11);
    RAM::Write8(0xF3, 0xFF12);
    RAM::Write8(0xBF, 0xFF14);
    RAM::Write8(0x3F, 0xFF16);
    RAM::Write8(0x00, 0xFF17);
    RAM::Write8(0xBF, 0xFF19);
    RAM::Write8(0x7F, 0xFF1A);
    RAM::Write8(0xFF, 0xFF1B);
    RAM::Write8(0x9F, 0xFF1C);
    RAM::Write8(0xBF, 0xFF1E);
    RAM::Write8(0xFF, 0xFF20);
    RAM::Write8(0x00, 0xFF21);
    RAM::Write8(0x00, 0xFF22);
    RAM::Write8(0xBF, 0xFF23);
    RAM::Write8(0x77, 0xFF24);
    RAM::Write8(0xF3, 0xFF25);
    RAM::Write8(0xF1, 0xFF26);
    RAM::Write8(0x91, 0xFF40);
    RAM::Write8(0x00, 0xFF42);
    RAM::Write8(0x00, 0xFF43);
    RAM::Write8(0x00, 0xFF45);
    RAM::Write8(0xFC, 0xFF47);
    RAM::Write8(0xFF, 0xFF48);
    RAM::Write8(0xFF, 0xFF49);
    RAM::Write8(0x00, 0xFF4A);
    RAM::Write8(0x00, 0xFF4B);
    RAM::GetRAM()[0xFF00] = 0xFF;
    RAM::Write8(0x00, 0xFFFF);
}

int main(int ac, char**av) {
    CPU cpu;
    GPU gpu;
    Display screen;
    Byte instr;
    SDL_Event event;
    bool isRunning = true;

    if (ac < 2) {
        std::cout << "[DEBUG] : Please enter a rom name" << std::endl;
        exit(EXIT_FAILURE);
    }

    printf("Welcome to GBE ( GameBoy Emulator )\n");
    Loader::LoadROM(av[1]);
    //Loader::LoadBootloader();
    cpu.SetRegistry16Value(Registry16::PC, 0x0100);
    InitRegisters(cpu);

    while (isRunning) {
        unsigned int cycles = 0;
        Uint64 frameStart = SDL_GetPerformanceCounter();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;
            }
        }

        while (cycles < CYCLES_PER_FRAME) {
            instr = cpu.GetNextInstruction();
            opCodes[instr].f(cpu);
            cpu.TickClock(opCodes[instr].cycles);
            cpu.SetLastInstrCycles((Byte) opCodes[instr].cycles);
            cycles += opCodes[instr].cycles;
            if (cpu.IsInterruptsEnabled()) {
                if (cpu.HasInterrupt(Interrupt::INT_VBLANK)) {
                    cpu.SetupInterrupt(Interrupt::INT_VBLANK);
                }
                if (cpu.HasInterrupt(Interrupt::INT_LCD_STAT)) {
                    cpu.SetupInterrupt(Interrupt::INT_LCD_STAT);
                }
                if (cpu.HasInterrupt(Interrupt::INT_TIMER)) {
                    cpu.SetupInterrupt(Interrupt::INT_TIMER);
                }
                if (cpu.HasInterrupt(Interrupt::INT_SERIAL)) {
                    cpu.SetupInterrupt(Interrupt::INT_SERIAL);
                }
                if (cpu.HasInterrupt(Interrupt::INT_JOYPAD)) {
                    cpu.SetupInterrupt(Interrupt::INT_JOYPAD);
                }
            }
            gpu.Step(cpu);
        }

        Uint64 frameEnd = SDL_GetPerformanceCounter();
        while (true) {
            frameEnd = SDL_GetPerformanceCounter();
            double frameElapsedInSec = (double)(frameEnd - frameStart) / SDL_GetPerformanceFrequency();
            if (frameElapsedInSec >= TIME_PER_FRAME) {
                break;
            }
        }
        frameStart = frameEnd;
    }
    return (0);
}