#include "IncludeSettings.hpp"

#if WINDOWS_MODE
    #include <SDL_ttf.h>
#elif UNIX_MODE
    #include <SDL2/SDL_ttf.h>
#endif