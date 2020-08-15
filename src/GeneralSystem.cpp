#include "GeneralSystem.hpp"
#include "Everything.hpp"

#include <iostream>

void GeneralSystem::INIT_SUBSYSTEMS(bool VERBOSE_MODE)
{
    Graphics::startUp();
    VisualComponent::startUp();
    RunningManager::startUp();
    
    if (VERBOSE_MODE) {
        AssetsManager::setVerboseMode();
        VisualComponent::setVerboseMode();
    }
}

void GeneralSystem::QUIT_SUBSYSTEMS()
{
    RunningManager::shutDown();
    VisualComponent::shutDown();
    AssetsManager::shutDown();
    Graphics::shutDown();
}