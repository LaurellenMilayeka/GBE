#pragma once

#ifndef NOGRAPHICS

#include <SDL2/SDL.h>

#endif

namespace Engine {

  typedef enum JoypadKeys {
    NONE = 0,
    LEFT = 1,
    RIGHT = 2,
    UP = 3,
    DOWN = 4,
    A = 5,
    B = 6,
    SELECT = 7,
    START = 8
  } JoypadKeys;
    
  class Joypad {

    static JoypadKeys _prevKey;

    Joypad();

  public:

    ~Joypad();

#ifndef NOGRAPHICS

    static void ProcessEvent(SDL_Event event);

#endif
  };
};
