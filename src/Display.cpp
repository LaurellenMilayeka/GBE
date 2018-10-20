//
// Created by Flox Ajuro on 13/09/2018.
//

#include <iostream>
#include <Display.hpp>
#include <RAM.hpp>
#include <cstring>

using namespace GBE;

SDL_Renderer* Display::_renderer = nullptr;
SDL_Surface* Display::_tmpScreenData = nullptr;
SDL_Texture* Display::_screenData = nullptr;
Uint32 *Display::pixels = nullptr;

Display::Display() {
    Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "[DEBUG] : Could not initialize SDL" << std::endl;
    }
    if (SDL_CreateWindowAndRenderer(480, 432, 0, &(this->_window), &(Display::_renderer)) != 0) {
        std::cerr << "[DEBUG] : Cannot initialize window and renderer" << std::endl;
    }
    if ((Display::_tmpScreenData = SDL_CreateRGBSurface(0, 160, 144, 32, rmask, gmask, bmask, amask)) == nullptr) {
        std::cerr << "[DEBUG] : Coud not ccreate surface" << std::endl;
    }
    if ((Display::_screenData = SDL_CreateTexture(Display::_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, 160, 144)) == nullptr) {
        std::cerr << "[DEBUG] : Could not create texture" << std::endl;
    }
    Display::pixels = new Uint32[160*144];
    std::memset(Display::pixels, 0x00, 160*144);
}

Display::~Display() {

}

void Display::UpdateDataScreen(GBE::PixelData *_data) {
    for (unsigned int i = 0; i < 160; i++) {
        Display::pixels[(RAM::Read8(LY) * 160) + i] = SDL_MapRGB(Display::_tmpScreenData->format, _data[i].r, _data[i].g, _data[i].b);
    }
}

void Display::RefreshData() {
    SDL_RenderClear(Display::_renderer);
    SDL_UpdateTexture(Display::_screenData, nullptr, Display::pixels, Display::_tmpScreenData->pitch);
    SDL_RenderCopy(Display::_renderer, Display::_screenData, nullptr, nullptr);
    SDL_RenderPresent(Display::_renderer);
}