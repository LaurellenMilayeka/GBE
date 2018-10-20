#include "Input.hpp"

using namespace GBE;

Byte Input::_directionInputs = 0x00;
Byte Input::_buttonInputs = 0x00;

bool Input::Update() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return (false);
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_DOWN:
                        Input::_directionInputs |= (1 << 3);
                        break;
                    case SDLK_UP:
                        Input::_directionInputs |= (1 << 2);
                        break;
                    case SDLK_RIGHT:
                        Input::_directionInputs |= (1 << 0);
                        break;
                    case SDLK_LEFT:
                        Input::_directionInputs |= (1 << 1);
                        break;
                    case SDLK_a:
                        Input::_buttonInputs |= (1 << 0);
                        break;
                    case SDLK_s:
                        Input::_buttonInputs |= (1 << 1);
                        break;
                    case SDLK_SPACE:
                        Input::_buttonInputs |= (1 << 2);
                        break;
                    case SDLK_RETURN:
                        Input::_buttonInputs |= (1 << 3);
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_DOWN:
                        Input::_directionInputs &= ~(1 << 3);
                        break;
                    case SDLK_UP:
                        Input::_directionInputs &= ~(1 << 2);
                        break;
                    case SDLK_RIGHT:
                        Input::_directionInputs &= ~(1 << 0);
                        break;
                    case SDLK_LEFT:
                        Input::_directionInputs &= ~(1 << 1);
                        break;
                    case SDLK_a:
                        Input::_buttonInputs &= ~(1 << 0);
                        break;
                    case SDLK_s:
                        Input::_buttonInputs &= ~(1 << 1);
                        break;
                    case SDLK_SPACE:
                        Input::_buttonInputs &= ~(1 << 2);
                        break;
                    case SDLK_RETURN:
                        Input::_buttonInputs &= ~(1 << 3);
                        break;
                }
                break;
        }
    }
    return (true);
}

Byte Input::GetDirectionInputs() {
    return (~(Input::_directionInputs));
}

Byte Input::GetButtonInputs() {
    return (~(Input::_buttonInputs));
}