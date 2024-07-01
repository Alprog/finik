#include "input_system.h"

#include "SDL.h"

InputSystem::InputSystem()
{
    SDL_Init(SDL_INIT_EVENTS | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER);
}