#include "IncludeSettings.hpp"

#if WINDOWS_MODE
    #include <SDL.h>
#elif UNIX_MODE
    #include <SDL2/SDL.h>
#endif