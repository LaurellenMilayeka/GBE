//
// Created by Flox Ajuro on 13/09/2018.
//

#ifndef GAMEBOY_EMULATOR_DISPLAY_HPP
#define GAMEBOY_EMULATOR_DISPLAY_HPP

#include "GBE.hpp"
#include "GPU.hpp"

namespace GBE {

    class Display {

        private:

            SDL_Window *_window;
            static SDL_Renderer *_renderer;

            static SDL_Surface *_tmpScreenData;
            static SDL_Texture *_screenData;

            static Uint32 *pixels;
        public:

            Display();
            ~Display();

            static void UpdateDataScreen(PixelData _data[160]);
            static void RefreshData();

    };

};

#endif //GAMEBOY_EMULATOR_DISPLAY_HPP
