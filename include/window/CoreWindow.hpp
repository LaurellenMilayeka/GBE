#pragma once

#include <cstdint>
#include <string>

#ifndef NOGRAPHICS

#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>

#endif

namespace Core {

  class Window {

#ifndef NOGRAPHICS

    SDL_Window *_window;
    SDL_Renderer *_renderer;

#endif
    
    static Core::Window *_instance;

    Window();
    
  public:
    static Core::Window *Instance();

    ~Window();

    void Init(std::string, size_t, size_t);
    void Destroy();

#ifndef NOGRAPHICS
    
    SDL_Renderer *GetRenderer();
    SDL_Window *GetWindow();

#endif
  };

};
