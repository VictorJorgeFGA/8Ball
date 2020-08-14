#include "IncludeSettings.hpp"

#if WINDOWS_MODE
    #include <SDL_image.h>
#elif UNIX_MODE
    #include <SDL2/SDL_image.h>
#endif