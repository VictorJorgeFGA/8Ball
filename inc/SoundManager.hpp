#ifndef _SOUNDMANAGER_HPP_
#define _SOUNDMANAGER_HPP_

#include "SDL.hpp"
#include "SDL_mixer.hpp"

#include <map>
#include <string>

class SoundManager
{
public:
    static void startUp(bool verbose = false);
    static void shutDown();
    static SoundManager * getInstance();

    void playSoundEffect(const std::string & sound_effect_name);
    void playSong(const std::string & song_name);

    void pauseCurrentSong();
    void resumeCurrentSong();

private:
    static bool VERBOSE;
    static const std::string ERROR_MSG;
    static const std::string VERBOSE_MSG;

    static SoundManager * _instance;

    Mix_Chunk * getChunk(const std::string & sound_effect_name);
    Mix_Music * getMusic(const std::string & song_name);

    SoundManager();
    ~SoundManager();

    std::map<std::string, Mix_Chunk *> _sound_effects;
    std::map<std::string, Mix_Music *> _songs;
};

#endif