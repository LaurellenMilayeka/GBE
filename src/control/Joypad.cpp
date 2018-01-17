#include "Joypad.hpp"
#include "IRAM.hpp"

Engine::JoypadKeys Engine::Joypad::_prevKey = NONE;

Engine::Joypad::Joypad()
{
}

Engine::Joypad::~Joypad()
{
}

#ifndef NOGRAPHICS

void Engine::Joypad::ProcessEvent(SDL_Event event)
{
  uint8_t key_reg = Engine::RAM::GetByte(0xFF00);
  uint8_t iFlags = Engine::RAM::GetByte(0xFF0F);

  switch (event.key.keysym.sym)
  {
  case SDLK_a:
    if (Engine::Joypad::_prevKey != A)
    {
      iFlags |= (1 << 2);
      key_reg = 0xFF;
      key_reg |= (1 << 5);
      key_reg |= (1 << 0);
      Engine::Joypad::_prevKey = Engine::A;
    }
    break;
  case SDLK_b:
    if (Engine::Joypad::_prevKey != B)
    {
      iFlags |= (1 << 2);
      key_reg = 0xFF;
      key_reg &= ~(1 << 5);
      key_reg &= ~(1 << 1);
      Engine::Joypad::_prevKey = Engine::B;
    }
    break;
  case SDLK_SPACE:
    if (Engine::Joypad::_prevKey != START)
    {
      iFlags |= (1 << 2);
      key_reg = 0xFF;
      key_reg &= ~(1 << 5);
      key_reg &= ~(1 << 3);
      Engine::Joypad::_prevKey = Engine::START;
    }
    break;
  case SDLK_RETURN:
    if (Engine::Joypad::_prevKey != SELECT)
    {
      iFlags |= (1 << 2);
      key_reg = 0xFF;
      key_reg &= ~(1 << 5);
      key_reg &= ~(1 << 2);
      Engine::Joypad::_prevKey = Engine::SELECT;
    }
    break;
  case SDLK_UP:
    if (Engine::Joypad::_prevKey != Engine::UP)
    {
      iFlags |= (1 << 2);
      key_reg = 0xFF;
      key_reg &= ~(1 << 4);
      key_reg &= ~(1 << 2);
      Engine::Joypad::_prevKey = Engine::UP;
    }
    break;
  case SDLK_DOWN:
    if (Engine::Joypad::_prevKey != Engine::DOWN)
    {
      iFlags |= (1 << 2);
      key_reg = 0xFF;
      key_reg &= ~(1 << 4);
      key_reg &= ~(1 << 3);
      Engine::Joypad::_prevKey = Engine::DOWN;
    }
    break;
  case SDLK_RIGHT:
    if (Engine::Joypad::_prevKey != Engine::RIGHT)
    {
      iFlags |= (1 << 2);
      key_reg = 0xFF;
      key_reg &= ~(1 << 4);
      key_reg &= ~(1 << 0);
      Engine::Joypad::_prevKey = Engine::RIGHT;
    }
    break;
  case SDLK_LEFT:
    if (Engine::Joypad::_prevKey != Engine::LEFT)
    {
      iFlags |= (1 << 2);
      key_reg = 0xFF;
      key_reg &= ~(1 << 4);
      key_reg &= ~(1 << 1);
      Engine::Joypad::_prevKey = Engine::LEFT;
    }
    break;
  default:
    iFlags |= (1 << 2);
    key_reg = 0xFF;
    Engine::Joypad::_prevKey = Engine::NONE;
    break;
  }
  Engine::RAM::SetByte(0xFF0F, iFlags, false);
  Engine::RAM::SetByte(0xFF00, key_reg, false);
}

#endif
