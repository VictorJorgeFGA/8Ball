#include "IncludeSettings.hpp"

#if WINDOWS_MODE
    #include <SDL_mixer.h>
#elif UNIX_MODE
    #include <SDL2/SDL_mixer.h>
#endif
