#include "Everything.hpp"
#include "test.hpp"
#include <iostream>
#include <vector>
#include <functional>
#include <string>

const std::string Test::COMPONENT_TEST_MSG = "\033[0;36mTesting component: \033[0m";
const std::string Test::FUNCTIONALITY_TEST_MSG = "\t\033[0;35mTesting functionality: \033[0m";

void Test::runTest()
{
    try {
        graphicsTest();
        timerTest();
        assetsManagerTest();
        visualComponentTest();
        interactiveComponentTest();
        soundManagerTest();
        std::cout << "\t\033[0;32mTests passed!\033[0m" << std::endl;
    }
    catch (std::runtime_error & e) {
        std::cerr << e.what() << std::endl;
        std::cout << "--------------------------------------" << std::endl;
        std::cout << "\t\033[0;31mTests failed!\033[0m" << std::endl; 
    }
}

void Test::graphicsTest()
{
    std::cout << "Graphics tests:" << std::endl;
    
    Graphics::startUp("Test", 720, 480, "assets/default_icon.png");
    Graphics * graphics = Graphics::getInstance(); 
    SDL_Rect rectangle {graphics->getWindowWidth() / 2 - 25, graphics->getWindowHeight() / 2 - 25, 50, 50};
    
    SDL_Texture * texture_example = graphics->loadTexture("assets/default_icon.png");
    TTF_Font * font = graphics->loadFont("assets/sony_sketch.ttf", 64);
    SDL_Texture * text = graphics->createTextTexture(font, "Test");

    std::vector<std::function<void()>> micro_tests {
        [&]() {
            graphics->setDrawColor(0x0, 0xFF, 0x0);
            graphics->drawRectangle(&rectangle);
        },
        [&]() {
            graphics->setDrawColor(0x0, 0x0, 0xFF);
            graphics->drawRectangle(&rectangle);
        },
        [&]() {
            graphics->setDrawColor(0xFF, 0x0, 0x0);
            graphics->drawRectangle(rectangle);
        },
        [&]() {
            graphics->setDrawColor(0xFF, 0xFF, 0x0);
            graphics->drawRectangle(rectangle);
        },
        [&]() {
            graphics->drawTexture(texture_example, &rectangle);
        },
        [&]() {
            graphics->drawTexture(text, NULL);
        },
        [&]() {
            graphics->drawTexture(text, rectangle);
        }
    };
    
    for (auto test : micro_tests) {
        int32_t initial_ticks = SDL_GetTicks();
        while (int32_t(SDL_GetTicks()) - initial_ticks <= 1000) {
            graphics->clearScreen();
            test();
            graphics->updateScreen();
            SDL_Delay(16);
        }
    }

    graphics->unloadTexture(text);
    graphics->unloadTexture(texture_example);
    graphics->unloadFont(font);
    Graphics::shutDown();
    std::cout << '\t' << "Ok" << std::endl;
}

void Test::timerTest()
{
    std::cout << "Timer tests:" << std::endl;

    Timer timer;

    std::cout << "\tTest (1.0x):" << std::endl;
    SDL_Delay(1000);
    float elapsed_time = timer.getElapsedTime();
    if (elapsed_time > 1.05f || elapsed_time < 0.95f)
        throw std::runtime_error("Timer test failed! Values expected > 0.95, < 1.05. Value received:" + std::to_string(elapsed_time));
    std::cout << "\t\t" << elapsed_time << std::endl;
    

    std::cout << "\tTest (2.0x):" << std::endl;
    timer.setTimeScale(2.0f);
    timer.reset();
    SDL_Delay(1000);
    elapsed_time = timer.getElapsedTime();
    if (elapsed_time > 2.05f || elapsed_time < 1.95f)
        throw std::runtime_error("Timer test failed! Values expected > 1.95, < 2.05. Value received:" + std::to_string(elapsed_time));
    std::cout << "\t\t" << elapsed_time << std::endl;


    std::cout << "\tTest (0.5x):" << std::endl;
    timer.setTimeScale(0.5f);
    timer.reset();
    SDL_Delay(1000);
    elapsed_time = timer.getElapsedTime();
    if (elapsed_time > 0.55f || elapsed_time < 0.45f)
        throw std::runtime_error("Timer test failed! Values expected > 0.45, < 0.55. Value received:" + std::to_string(elapsed_time));
    std::cout << "\t\t" << elapsed_time << std::endl;


    std::cout << '\t' << "Ok" << std::endl;
}

void Test::assetsManagerTest()
{
    std::cout << "Assets Manager tests:" << std::endl;

    Graphics::startUp();
    Graphics * graphics = Graphics::getInstance();

    AssetsManager * am = AssetsManager::getInstance();
    SDL_Texture * texture_example = am->getTexture("default_icon.png");
    SDL_Texture * text_example = am->getTextTexture("sony_sketch.ttf", 32, "assets_test");

    SDL_Rect draw_area {50, 50, 100, 100};

    graphics->clearScreen();
    graphics->drawTexture(texture_example, &draw_area);
    graphics->updateScreen();
    SDL_Delay(1000);

    graphics->clearScreen();
    graphics->drawTexture(text_example, &draw_area);
    graphics->updateScreen();
    SDL_Delay(1000);

    graphics->clearScreen();
    graphics->drawTexture(am->getTexture("default_icon.png"), &draw_area);
    graphics->updateScreen();
    SDL_Delay(1000);

    graphics->clearScreen();
    graphics->drawTexture(am->getTextTexture("sony_sketch.ttf", 32, "8BALL", {255, 126, 0, 255}), &draw_area);
    graphics->updateScreen();
    SDL_Delay(1000);

    /* Not necessary because of AssetsManager destructor
    
    graphics->unloadTexture(texture_example);
    graphics->unloadTexture(text_example);
    
    */

    AssetsManager::shutDown();
    Graphics::shutDown();

    std::cout << '\t' << "Ok" << std::endl;
}

void Test::visualComponentTest()
{
    std::cout << "Visual Component tests:" << std::endl;

    Graphics::startUp();
    Graphics * graphics = Graphics::getInstance();
    VisualComponent::startUp();
    VisualComponent::setVerboseMode();
    AssetsManager::setVerboseMode();

    SolidImage * background = SolidImage::newSolidImage("background_test.png", 210, 210),
                    * ball6 = SolidImage::newSolidImage("ball6_test.png", 60, 60),
                    * ball7 = SolidImage::newSolidImage("ball7_test.png", 60, 60),
                    * ball8 = SolidImage::newSolidImage("ball8_test.png", 60, 60),
                    * ball9 = SolidImage::newSolidImage("ball9_test.png", 60, 60);

    SolidText * text = SolidText::newSolidText("Solid Text testing!", "sony_sketch.ttf", 32, {0, 0, 0, 0xff});

    ball6->setParent(background);
    ball7->setParent(background);
    ball8->setParent(background);
    ball9->setParent(background);

    if (background->countChildren() != 4)
        throw std::runtime_error("Visual Component children vector size failed! Expected 4 children, got " + std::to_string(background->countChildren()));
    else if (VisualComponent::getScreenObject()->countChildren() != 2)
        throw std::runtime_error("SCREEN Visual Component children vector size failed! Expected 1, got " + std::to_string(VisualComponent::getScreenObject()->countChildren()));

    text->setRelativeX(10); text->setRelativeY(10);

    background->setGlobalX(graphics->getWindowWidth() / 2 - 105);
    background->setGlobalY(graphics->getWindowHeight() / 2 - 105);
    background->setRotationAngle(45.0f);

    ball6->setRelativeX(10); ball6->setRelativeY(10);

    ball7->setRelativeX(background->getWidth() - ball7->getWidth() - 10);
    ball7->setRelativeY(10);

    ball8->setRelativeX(10);
    ball8->setRelativeY(background->getHeight() - ball8->getHeight() - 10);

    ball9->setRelativeX(background->getWidth() - ball9->getWidth() - 10);
    ball9->setRelativeY(background->getHeight() - ball9->getHeight() - 10);

    VisualComponent::drawComponents();
    SDL_Delay(1200);

    ball8->setParent(VisualComponent::getScreenObject());
    ball7->hide();
    text->setRotationAngle(20);

    VisualComponent::drawComponents();
    SDL_Delay(1200);

    VisualComponent::shutDown();
    AssetsManager::shutDown();
    Graphics::shutDown();

    std::cout << '\t' << "Ok" << std::endl;
}

void Test::interactiveComponentTest()
{
    std::cout << "Visual Component tests:" << std::endl;

    Graphics::startUp();
    VisualComponent::startUp();
    AssetsManager::setVerboseMode();
    VisualComponent::setVerboseMode();

    Button * button = Button::newButton("Button test");
    button->untie();

    VisualComponent::drawComponents();
    SDL_Delay(1000);

    std::cout << "\tUntied dragging simulation" << std::endl;

    int32_t new_global_x = button->getGlobalX()+button->getWidth() - 1;
    int32_t new_global_y = button->getGlobalY()+button->getHeight() - 1;
    InteractiveComponent::processMouseButtonDown({button->getGlobalX()+1,button->getGlobalY()+1});
    InteractiveComponent::processMouseMotion({button->getGlobalX()+button->getWidth(), button->getGlobalY()+button->getHeight()});
    VisualComponent::drawComponents();
    SDL_Delay(500);

    InteractiveComponent::processMouseButtonUp({10,10});
    VisualComponent::drawComponents();
    SDL_Delay(1000);

    if (button->getGlobalX() != new_global_x || button->getGlobalY() != new_global_y)
        throw std::runtime_error(
            "Untied dragging test failed. Expected coordinates: " +
            std::to_string(new_global_x) + ", " +
            std::to_string(new_global_y) + ". Got:" +
            std::to_string(button->getGlobalX()) + ", " +
            std::to_string(button->getGlobalY())
        );

    button->tie();
    InteractiveComponent::processMouseButtonDown({button->getGlobalX(), button->getGlobalY()});
    InteractiveComponent::processMouseMotion({button->getGlobalX()+button->getWidth(), button->getGlobalY()+button->getHeight()});
    VisualComponent::drawComponents();
    SDL_Delay(500);

    InteractiveComponent::processMouseButtonUp({10,10});
    SDL_Delay(1000);

    if (button->getGlobalX() != new_global_x || button->getGlobalY() != new_global_y)
        throw std::runtime_error(
            "Tied dragging test failed. Expected coordinates: " +
            std::to_string(new_global_x) + ", " +
            std::to_string(new_global_y) + ". Got:" +
            std::to_string(button->getGlobalX()) + ", " +
            std::to_string(button->getGlobalY())
        );

    VisualComponent::shutDown();
    AssetsManager::shutDown();
    Graphics::shutDown();

    std::cout << '\t' << "Ok" << std::endl;
}

void Test::soundManagerTest()
{
    std::cout << COMPONENT_TEST_MSG << "SoundManager" << std::endl;

    Graphics::startUp();
    VisualComponent::startUp();
    SoundManager::startUp();

    SoundManager::setVerboseMode();
    SoundManager * sound_manager = SoundManager::getInstance();

    std::cout << FUNCTIONALITY_TEST_MSG << "playSoundEffect" << std::endl;
    sound_manager->playSoundEffect("sound_effect_test.wav");
    SDL_Delay(4000);

    std::cout << FUNCTIONALITY_TEST_MSG << "playSoundEffect (with 50% intensity)" << std::endl;
    sound_manager->playSoundEffect("sound_effect_test.wav", 50.0);
    SDL_Delay(4000);

    std::cout << FUNCTIONALITY_TEST_MSG << "playSong" << std::endl;
    sound_manager->playSong("test_song.ogg");
    SDL_Delay(10000);

    std::cout << FUNCTIONALITY_TEST_MSG << "pauseCurrentSong" << std::endl;
    sound_manager->pauseCurrentSong();
    SDL_Delay(5000);

    std::cout << FUNCTIONALITY_TEST_MSG << "resumeCurrentSong" << std::endl;
    sound_manager->resumeCurrentSong();
    SDL_Delay(5000);

    std::cout << FUNCTIONALITY_TEST_MSG << "toggleCurrentSong" << std::endl;
    sound_manager->toggleCurrentSong();
    SDL_Delay(5000);

    std::cout << FUNCTIONALITY_TEST_MSG << "toggleCurrentSong" << std::endl;
    sound_manager->toggleCurrentSong();
    SDL_Delay(5000);

    std::cout << FUNCTIONALITY_TEST_MSG << "isPlayingSong" << std::endl;
    if (!sound_manager->isPlayingSong())
        throw std::runtime_error("isPlayingSong test failed! Expected true, got false");

    std::cout << FUNCTIONALITY_TEST_MSG << "stopCurrentSong" << std::endl;
    sound_manager->stopCurrentSong();
    SDL_Delay(5000);

    std::cout << FUNCTIONALITY_TEST_MSG << "setSoundEffectsVolume (30%)" << std::endl;
    sound_manager->setSoundEffectsVolume(30.0);
    sound_manager->playSoundEffect("sound_effect_test.wav");
    SDL_Delay(5000);

    std::cout << FUNCTIONALITY_TEST_MSG << "getSoundEffectsVolume" << std::endl;
    if (abs(sound_manager->getSoundEffectsVolume() - 30.0) > DBL_EPSILON)
        throw std::runtime_error("getSoundEffectsVolume test failed! Expected 30.0 got " + std::to_string(sound_manager->getSoundEffectsVolume()));

    std::cout << FUNCTIONALITY_TEST_MSG << "setSoundEffectsVolume (100%)" << std::endl;
    sound_manager->setSoundEffectsVolume(100.0);
    sound_manager->playSoundEffect("sound_effect_test.wav");
    SDL_Delay(5000);

    std::cout << FUNCTIONALITY_TEST_MSG << "setSongsVolume (30%)" << std::endl;
    sound_manager->setSongsVolume(30.0);
    sound_manager->playSong("test_song.ogg");

    std::cout << FUNCTIONALITY_TEST_MSG << "getSongsVolume" << std::endl;
    if (abs(sound_manager->getSongsVolume() - 30.0) > DBL_EPSILON)
        throw std::runtime_error("getSongsVolume test failed! Expected 30.0 got " + std::to_string(sound_manager->getSongsVolume()));

    SDL_Delay(10000);

    std::cout << FUNCTIONALITY_TEST_MSG << "setMasterVolume (100%)" << std::endl;
    sound_manager->setMasterVolume(100.0);
    sound_manager->playSoundEffect("sound_effect_test.wav");
    SDL_Delay(5000);

    std::cout << FUNCTIONALITY_TEST_MSG << "setMasterVolume (40%)" << std::endl;
    sound_manager->setMasterVolume(40.0);
    sound_manager->playSoundEffect("sound_effect_test.wav");
    SDL_Delay(10000);

    SoundManager::shutDown();
    VisualComponent::shutDown();
    AssetsManager::shutDown();
    Graphics::shutDown();

    std::cout << '\t' << "Ok" << std::endl;
}

void Test::physicsTest()
{
    
}
