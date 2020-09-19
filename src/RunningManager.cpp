#include "RunningManager.hpp"
#include "VisualComponent.hpp"
#include "InteractiveComponent.hpp"
#include "Button.hpp"
#include "SolidImage.hpp"
#include "Table.hpp"
#include "SoundManager.hpp"
#include "ScrollBar.hpp"

#include <stdexcept>
#include <iostream>

RunningManager * RunningManager::_instance = nullptr;

void RunningManager::startUp()
{
    if (_instance != nullptr)
        throw std::runtime_error("Attempt to initialize RunningManager twice.");

    _instance = new RunningManager();
}

RunningManager * RunningManager::getInstance()
{
    return _instance;
}

void RunningManager::shutDown()
{
    if (_instance == nullptr)
        throw std::runtime_error("Attempt to shutdown RunningManager before initialization");

    delete _instance;
    _instance = nullptr;
}

void RunningManager::runProgram()
{
    while (! _quit) {
        while (SDL_PollEvent(&_event) != 0)
            processEvent();

        if (_physics_timer.getElapsedTime() >= _120FPS_TIME) {
            _physic_world->updateWorldObjects(_physics_timer.getElapsedTime());
            _physics_timer.reset();
        }
        
        if (_rendering_timer.getElapsedTime() >= _60FPS_TIME) {
            VisualComponent::drawComponents();
            _rendering_timer.reset();
        }
        SDL_Delay(5);
    }
}


void RunningManager::processEvent()
{
    switch (_event.type) {
    case SDL_QUIT:
        _quit = true;
        break;

    case SDL_MOUSEBUTTONDOWN:
        if (_event.button.button == SDL_BUTTON_LEFT)
            InteractiveComponent::processMouseButtonDown({_event.button.x, _event.button.y});
        break;
    
    case SDL_MOUSEBUTTONUP:
        if (_event.button.button == SDL_BUTTON_LEFT)
            InteractiveComponent::processMouseButtonUp({_event.button.x, _event.button.y});
        break;

    case SDL_MOUSEMOTION:
        InteractiveComponent::processMouseMotion({_event.motion.x, _event.motion.y});
        break;

    default:
        break;
    }
}

RunningManager::RunningManager():
_event(),
_quit(false),
_rendering_timer(),
_LOOP_TIME(0.0035),
_120FPS_TIME(1.0/120.0),
_60FPS_TIME(1.0/60.0),
_30FPS_TIME(1.0/30.0),
_quit_button(nullptr)
{
    _quit_button = Button::newButton("Sair");
    _quit_button->setClickReaction([](){
        SDL_Event e;
        e.type = SDL_QUIT;
        SDL_PushEvent(&e);
    });

    Button * music_button = Button::newButton("Music");
    music_button->setClickReaction([](){
        SoundManager::getInstance()->toggleCurrentSong();
    });

    Button * down_volume = Button::newButton("Down volume");
    down_volume->setClickReaction([](){
        SoundManager * sm = SoundManager::getInstance();
        sm->setMasterVolume(sm->getMasterVolume() - 10.0);
    });

    Button * up_volume = Button::newButton("Up volume");
    up_volume->setClickReaction([](){
        SoundManager * sm = SoundManager::getInstance();
        sm->setMasterVolume(sm->getMasterVolume() + 10.0);
    });

    ScrollBar * volume_scrollbar = ScrollBar::newScrollBar(ScrollBar::HORIZONTAL);
    volume_scrollbar->setCallbackFunction([](double_t volume){
        SoundManager::getInstance()->setMasterVolume(volume);
    });
    volume_scrollbar->setGlobalX(50);
    volume_scrollbar->setGlobalY(20);

    ScrollBar * timer_scrollbar = ScrollBar::newScrollBar(ScrollBar::VERTICAL);
    timer_scrollbar->setRelativeX(10);
    timer_scrollbar->setRelativeY(70);
    timer_scrollbar->setCallbackFunction([&](double_t speed){
        _physics_timer.setTimeScale(speed / 100.0);
    });

    _table = Table::newTable();
    volume_scrollbar->setParent(_table);
    timer_scrollbar->setParent(_table);

    _quit_button->setParent(_table);
    _quit_button->untie();

    music_button->setRelativeX(_table->getWidth() - music_button->getWidth());
    music_button->setRelativeY(0);
    music_button->setParent(_table);

    down_volume->setParent(_table);
    down_volume->setRelativeX(_table->getWidth() / 2 - down_volume->getWidth());
    down_volume->setRelativeY(0);

    up_volume->setParent(_table);
    up_volume->setRelativeX(_table->getWidth() / 2);
    up_volume->setRelativeY(0);

    _physic_world = PhysicWorld::getInstance();

    _120FPS_TIME -= _LOOP_TIME;
    _60FPS_TIME -= _LOOP_TIME;
    _30FPS_TIME -= _LOOP_TIME;

    Ball::newBall(2.85, _table->getTableCenter() + Vector2D(10.0, 0.0), 1)->setVelocity({0.0, 55.0});
    Ball::newBall(2.85, _table->getTableCenter() + Vector2D(20.0, 0.0), 1)->setVelocity({0.0, -55.0});
    Ball::newBall(2.85, _table->getTableCenter() + Vector2D(30.0, 0.0), 1)->setVelocity({55.0, 0.0});
    Ball::newBall(2.85, _table->getTableCenter() + Vector2D(40.0, 0.0), 1)->setVelocity({-50.0, 0.0});

    SoundManager::getInstance()->playSong("test_song.ogg");

}

RunningManager::~RunningManager()
{

}