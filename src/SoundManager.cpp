#include "SoundManager.hpp"

#include <iostream>
#include <stdexcept>

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
    VERBOSE = false;
    _instance = new SoundManager();

    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
        std::cerr << ERROR_MSG << "Unable to initialize SDL_AUDIO system." << std::endl;
        throw std::runtime_error(SDL_GetError());
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        std::cerr << ERROR_MSG << "Unable to initialize SDL_Mixer." << std::endl;
        throw std::runtime_error(Mix_GetError());
    }
}

void SoundManager::shutDown()
{
    if (_instance == nullptr) {
        std::cerr << ERROR_MSG << "Attempt to shut down SoundManager before initialization." << std::endl;
        throw std::runtime_error("SoundManager shutDown bad call.");
    }
    delete _instance;
    _instance = nullptr;
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
    if (isPlayingSong()) {
        Mix_PausedMusic();
        _is_playing_music = false;
    }
}

void SoundManager::resumeCurrentSong()
{
    if (!isPlayingSong()) {
        Mix_ResumeMusic();
        _is_playing_music = true;
    }
}

bool SoundManager::isPlayingSong() const
{
    return _is_playing_music;
}

Mix_Chunk * SoundManager::getChunk(const std::string & sound_effect_name)
{
    if (_sound_effects.count(sound_effect_name) < 1) {
        _sound_effects[sound_effect_name] = Mix_LoadWAV(std::string("assets/" + sound_effect_name).c_str());
        if (_sound_effects[sound_effect_name] == NULL) {
            std::cerr << ERROR_MSG << "Unable to load sound effect: " << sound_effect_name << std::endl;;
            throw std::runtime_error(Mix_GetError());
        }
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
    }
    return _songs[song_name];
}

SoundManager::SoundManager():
_is_playing_music(false)
{

}

SoundManager::~SoundManager()
{
    for (auto music : _songs)
        Mix_FreeMusic(music.second);
    for (auto chunk : _sound_effects)
        Mix_FreeChunk(chunk.second);
}