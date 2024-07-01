#include "desktop_system.h"

#include <SDL.h>

DesktopSystem::DesktopSystem()
{
    SDL_Init(SDL_INIT_VIDEO);
}