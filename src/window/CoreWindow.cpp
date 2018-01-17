#include "CoreWindow.hpp"
#include "Define.hpp"

Core::Window *Core::Window::_instance = nullptr;

#ifndef NOGRAPHICS

Core::Window::Window()
{
  DEBUG_PRINT("Initializing graphic library...");
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
  {
    DEBUG_PRINT("Error during initialization : " << SDL_GetError());
    std::cerr << "Error during initialization. Quitting..." << std::endl;
    exit(EXIT_FAILURE);
  }
  DEBUG_PRINT("Initialization OK.");
}

Core::Window::~Window()
{
}

Core::Window *Core::Window::Instance()
{
  if (Core::Window::_instance == nullptr)
  {
    Core::Window::_instance = new Core::Window();
  }
  return (Core::Window::_instance);
}

void Core::Window::Init(std::string title, size_t width, size_t height)
{

#ifndef NOGRAPHICS

  DEBUG_PRINT("Creating window and renderer with following parameters :");
  DEBUG_PRINT("Title : " << title << "\nWidth : " << width << "\nHeight : " << height);
  if (SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL, &(this->_window), &(this->_renderer)))
  {
    DEBUG_PRINT("Error initializing window and renderer : " << SDL_GetError());
    std::cerr << "Error initializing window and renderer. Quitting..." << std::endl;
    exit(EXIT_FAILURE);
  }
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_CreateContext(this->_window);
  glewExperimental = GL_TRUE;
  glewInit();
  SDL_SetWindowTitle(this->_window, title.c_str());
  DEBUG_PRINT("Window and renderer created");

#endif
}

void Core::Window::Destroy()
{

#ifndef NOGRAPHICS

  SDL_DestroyRenderer(this->_renderer);
  SDL_DestroyWindow(this->_window);

#endif

  this->_renderer = nullptr;
  this->_window = nullptr;
}

#endif

#ifndef NOGRAPHICS

SDL_Renderer *Core::Window::GetRenderer()
{
  return (this->_renderer);
}

SDL_Window *Core::Window::GetWindow()
{
  return (this->_window);
}

#endif
