#pragma once

#include <cstdint>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>

namespace Core {

  class Window {

    SDL_Window *_window;
    SDL_Renderer *_renderer;

    static Core::Window *_instance;

    Window();
    
  public:
    static Core::Window *Instance();

    ~Window();

    void Init(std::string, size_t, size_t);
    void Destroy();

    SDL_Renderer *GetRenderer();
    SDL_Window *GetWindow();

  };

};
