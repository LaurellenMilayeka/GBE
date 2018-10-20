//
// Created by Flox Ajuro on 09/09/2018.
//

#ifndef GAMEBOY_EMULATOR_GPU_HPP
#define GAMEBOY_EMULATOR_GPU_HPP

#include <bitset>
#include "CPU.hpp"

namespace GBE {

    typedef enum {
        LCD_ENABLE = 1 << 7,
        WINDOW_TILE_MAP = 1 << 6,
        WINDOW_ENABLE = 1 << 5,
        BG_WINDOW_TILE_DATA_ADDRESS = 1 << 4,
        BG_TILE_DATA_ADDRESS = 1 << 3,
        SPRITE_SIZE = 1 << 2,
        SPRITE_ENABLE = 1 << 1,
        PRIORITY_ENABLE = 1 << 0
    } LCDControl;

    typedef enum {
        LYC_INTERRUPT = 1 << 6,
        OAM_INTERRUPT = 1 << 5,
        VBLANK_INTERRUPT = 1 << 4,
        HBLANK_INTERRUPT = 1 << 3,
        COINCIDENCE = 1 << 2,
    } LCDStatus;

    typedef enum {
        WHITE,
        WHITE_GRAY,
        DARK_GRAY,
        DARK
    } Colour;

#define SCY 0xFF42
#define SCX 0xFF43
#define LY 0xFF44
#define LYC 0xFF45
#define PALETTE 0xFF47
#define WY 0xFF4A
#define WX 0xFF4B

    typedef enum {
        OAM = 2,
        PIXEL_TRANSFER = 3,
        HBLANK = 0,
        VBLANK = 1
    } VideoMode;

    typedef struct {
        Byte r;
        Byte g;
        Byte b;
        Byte a;
    } PixelData;

    class GPU {

        private:

            unsigned char _lcdControl;
            unsigned char _lcdStatus;

            unsigned short _gpuClock;

            PixelData _data[160];
            Byte _color[160];

            void SetVideoMode(VideoMode videoMode);

            Word GetBGTileMapAddress();
            Word GetTileDataAddress();
            Word GetWindowTileAddress();
            int GetColour(Byte data, Word address);
            void ProcessLineData();

            void ProcessSprites();

            bool IsLCDEnabled() const;

            std::string VideoModeToString() {
                return ("Hello");
            }

        public:

            GPU();
            ~GPU();

            bool IsStatusInterruptEnabled(LCDStatus toCheck);

            void Step(CPU& cpu);
            VideoMode GetVideoMode();

    };

};

#endif //GAMEBOY_EMULATOR_DISPLAY_HPP
