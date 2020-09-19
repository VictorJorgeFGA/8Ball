#include "GeneralSystem.hpp"
#include "Everything.hpp"

#include <iostream>

void GeneralSystem::INIT_SUBSYSTEMS(bool VERBOSE_MODE)
{
    Graphics::startUp("Billiards", 960, 544, "assets/default_icon.png");
    VisualComponent::startUp();
    InteractiveComponent::startUp();
    SoundManager::startUp();
    RunningManager::startUp();
    
    if (VERBOSE_MODE) {
        AssetsManager::setVerboseMode();
        VisualComponent::setVerboseMode();
        SoundManager::setVerboseMode();
    }
}

void GeneralSystem::QUIT_SUBSYSTEMS()
{
    SoundManager::shutDown();
    RunningManager::shutDown();
    VisualComponent::shutDown();
    AssetsManager::shutDown();
    Graphics::shutDown();
}