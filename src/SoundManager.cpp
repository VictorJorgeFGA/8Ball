#include "SoundManager.hpp"

#include <iostream>
#include <stdexcept>
#include <cstdint>

bool SoundManager::VERBOSE = false;
const std::string SoundManager::ERROR_MSG = "\033[0;31m(ERROR) SoundManager:\033[0m\t";
const std::string SoundManager::VERBOSE_MSG = "\033[0;33m(VERBOSE) SoundManager:\033[0m\t";

SoundManager * SoundManager::_instance = nullptr;

void SoundManager::startUp()
{
    if (_instance != nullptr) {
        std::cerr << ERROR_MSG << "Attempt to initialize SoundManager more than once." << std::endl;
        throw std::runtime_error("SoundManager startUp bad call.");
    }

    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
        std::cerr << ERROR_MSG << "Unable to initialize SDL_AUDIO system." << std::endl;
        throw std::runtime_error(SDL_GetError());
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        std::cerr << ERROR_MSG << "Unable to initialize SDL_Mixer." << std::endl;
        throw std::runtime_error(Mix_GetError());
    }

    _instance = new SoundManager();

    if (VERBOSE) std::cout << VERBOSE_MSG << "Starting up!" << std::endl;
}

void SoundManager::shutDown()
{
    if (_instance == nullptr) {
        std::cerr << ERROR_MSG << "Attempt to shut down SoundManager before initialization." << std::endl;
        throw std::runtime_error("SoundManager shutDown bad call.");
    }

    Mix_HaltMusic();
    int32_t ALL_CHANNELS = -1;
    Mix_HaltChannel(ALL_CHANNELS);

    delete _instance;
    _instance = nullptr;

    Mix_CloseAudio();

    if (VERBOSE) std::cout << VERBOSE_MSG << "Shutting down!" << std::endl;
}

SoundManager * SoundManager::getInstance()
{
    if (_instance == nullptr) {
        std::cerr << ERROR_MSG << "Attempt to get SoundManager instance before initialization." << std::endl;
        throw std::runtime_error("SoundManager initializing forgotten.");
    }
    return _instance;
}

void SoundManager::setVerboseMode()
{
    VERBOSE = true;
}

void SoundManager::playSoundEffect(const std::string & sound_effect_name, double_t sound_intensity_percentage)
{
    if (sound_intensity_percentage < 0.0) sound_intensity_percentage = 0.0;
    else if (sound_intensity_percentage > 100.0) sound_intensity_percentage = 100.0;

    sound_intensity_percentage /= 100.0;

    Mix_Chunk * sound_effect = getChunk(sound_effect_name);
    int32_t previous_volume = Mix_VolumeChunk(sound_effect, -1);
    Mix_VolumeChunk(sound_effect, int32_t(previous_volume * sound_intensity_percentage));
    playSoundEffect(sound_effect_name);
}

void SoundManager::playSoundEffect(const std::string & sound_effect_name)
{
    if (Mix_PlayChannel(-1, getChunk(sound_effect_name), 0) == -1) {
        std::cerr << ERROR_MSG << "Unable to play sound effect: " << sound_effect_name << std::endl;
        throw std::runtime_error(Mix_GetError());
    }

    if (VERBOSE) std::cout << VERBOSE_MSG << "Playing sound effect: " << sound_effect_name << std::endl;
}

void SoundManager::playSong(const std::string & song_name)
{
    int32_t MIX_PLAY_FOREVER = -1;
    if (Mix_FadeInMusic(getMusic(song_name), MIX_PLAY_FOREVER, 2000) == -1) {
        std::cerr << ERROR_MSG << "Unable to play song: " << song_name << std::endl;
        throw std::runtime_error(Mix_GetError());
    }

    if (VERBOSE) std::cout << VERBOSE_MSG << "Playing song: " << song_name << std::endl;
}

void SoundManager::pauseCurrentSong()
{
    if (Mix_PlayingMusic() && !Mix_PausedMusic()) {
        Mix_PauseMusic();
        if (VERBOSE) std::cout << VERBOSE_MSG << "Pause song." << std::endl;
    }
    else if (VERBOSE && !Mix_PlayingMusic())
        std::cout << VERBOSE_MSG << "Warning (pauseCurrentSong): there is no active song to pause." << std::endl;
    else if (VERBOSE && Mix_PausedMusic())
        std::cout << VERBOSE_MSG << "Warning (pauseCurrentSong): current song is already paused." << std::endl;
}

void SoundManager::resumeCurrentSong()
{
    if (Mix_PlayingMusic() && Mix_PausedMusic()) {
        Mix_ResumeMusic();
        if (VERBOSE) std::cout << VERBOSE_MSG << "Resume song." << std::endl;
    }
    else if (VERBOSE && !Mix_PlayingMusic())
        std::cout << VERBOSE_MSG << "Warning (pauseCurrentSong): there is no active song to resume." << std::endl;
    else if (VERBOSE && !Mix_PausedMusic())
        std::cout << VERBOSE_MSG << "Warning (pauseCurrentSong): current song is already resumed." << std::endl;
}

void SoundManager::toggleCurrentSong()
{
    if (isPlayingSong())
        pauseCurrentSong();
    else
        resumeCurrentSong();
}

bool SoundManager::isPlayingSong() const
{
    return Mix_PlayingMusic() && !Mix_PausedMusic();
}

void SoundManager::stopCurrentSong()
{
    if (Mix_PlayingMusic())
        Mix_HaltMusic();
    else if (VERBOSE) std::cout << VERBOSE_MSG << "Warning (stopCurrentSong): there is no active song to stop." << std::endl;
}

void SoundManager::setSoundEffectsVolume(double_t percent)
{
    if (percent < 0.0) percent = 0.0;
    else if (percent > 100.0) percent = 100.0;

    _sound_effects_volume = percent / 100.0;
    for (auto sound_effect : _sound_effects)
        Mix_VolumeChunk(sound_effect.second, int32_t(_master_volume * _sound_effects_volume * 128));

    if (VERBOSE) std::cout << VERBOSE_MSG << "Setting sound effects volume to " << percent << '%' << std::endl;
}

double_t SoundManager::getSoundEffectsVolume() const
{
    return _sound_effects_volume * 100;
}

void SoundManager::setSongsVolume(double_t percent)
{
    if (percent < 0.0) percent = 0.0;
    else if (percent > 100.0) percent = 100.0;

    _songs_volume = percent / 100.0;
    Mix_VolumeMusic(int32_t(_master_volume * _songs_volume * 128));

    if (VERBOSE) std::cout << VERBOSE_MSG << "Setting songs volume to " << percent << '%' << std::endl;
}

double_t SoundManager::getSongsVolume() const
{
    return _songs_volume * 100.0;
}

void SoundManager::setMasterVolume(double_t percent)
{
    if (percent < 0.0) percent = 0.0;
    else if (percent > 100.0) percent = 100.0;
    
    _master_volume = percent / 100.0;
    setSoundEffectsVolume(getSoundEffectsVolume());
    setSongsVolume(getSongsVolume());

    if (VERBOSE) std::cout << VERBOSE_MSG << "Setting master volume to " << percent << '%' << std::endl;
}

double_t SoundManager::getMasterVolume() const
{
    return _master_volume * 100.0;
}

Mix_Chunk * SoundManager::getChunk(const std::string & sound_effect_name)
{
    if (_sound_effects.count(sound_effect_name) < 1) {
        _sound_effects[sound_effect_name] = Mix_LoadWAV(std::string("assets/" + sound_effect_name).c_str());
        if (_sound_effects[sound_effect_name] == NULL) {
            std::cerr << ERROR_MSG << "Unable to load sound effect: " << sound_effect_name << std::endl;;
            throw std::runtime_error(Mix_GetError());
        }

        if (VERBOSE) std::cout << VERBOSE_MSG << "Loading sound effect \"" << sound_effect_name << '\"' << std::endl;
    }
    return _sound_effects[sound_effect_name];
}

Mix_Music * SoundManager::getMusic(const std::string & song_name)
{
    if (_songs.count(song_name) < 1) {
        _songs[song_name] = Mix_LoadMUS(std::string("assets/" + song_name).c_str());
        if (_songs[song_name] == NULL) {
            std::cerr << ERROR_MSG << "Unable to load song: " << song_name << std::endl;
            throw std::runtime_error(Mix_GetError());
        }

        if (VERBOSE) std::cout << VERBOSE_MSG << "Loading song \"" << song_name << '\"' << std::endl;
    }
    return _songs[song_name];
}

SoundManager::SoundManager():
_master_volume(1.0),
_sound_effects_volume(1.0),
_songs_volume(1.0)
{

}

SoundManager::~SoundManager()
{
    for (auto music : _songs)
        Mix_FreeMusic(music.second);
    for (auto chunk : _sound_effects)
        Mix_FreeChunk(chunk.second);
}