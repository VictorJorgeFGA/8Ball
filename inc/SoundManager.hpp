#ifndef _SOUNDMANAGER_HPP_
#define _SOUNDMANAGER_HPP_

#include "SDL.hpp"
#include "SDL_mixer.hpp"

#include <map>
#include <string>

class SoundManager
{
public:
    static void startUp();
    static void shutDown();
    static SoundManager * getInstance();

    static void setVerboseMode();

    void playSoundEffect(const std::string & sound_effect_name);
    void playSong(const std::string & song_name);

    void pauseCurrentSong();
    void resumeCurrentSong();
    void toggleCurrentSong();
    bool isPlayingSong() const;

    void setSoundEffectsVolume(double_t percent);
    double_t getSoundEffectsVolume() const;

    void setSongsVolume(double_t percent);
    double_t getSongsVolume() const;

    void setMasterVolume(double_t percent);
    double_t getMasterVolume() const;

private:
    static bool VERBOSE;
    static const std::string ERROR_MSG;
    static const std::string VERBOSE_MSG;

    static SoundManager * _instance;

    Mix_Chunk * getChunk(const std::string & sound_effect_name);
    Mix_Music * getMusic(const std::string & song_name);

    SoundManager();
    ~SoundManager();

    bool _is_playing_music;
    double_t _master_volume;
    double_t _sound_effects_volume;
    double_t _songs_volume;

    std::map<std::string, Mix_Chunk *> _sound_effects;
    std::map<std::string, Mix_Music *> _songs;
};

#endif