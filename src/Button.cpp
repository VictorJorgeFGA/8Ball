#include "Button.hpp"

Button * Button::newButton(SolidImage * background, SolidText * text)
{
    Button * button = new Button();

    button->setWidth(background->getWidth());
    button->setHeight(background->getHeight());
    button->setGlobalX(background->getGlobalX());
    button->setGlobalY(background->getGlobalY());

    background->setParent(button);
    text->setParent(button);

    text->setRelativeX((button->getWidth() / 2) - (text->getWidth() / 2));
    text->setRelativeY((button->getHeight() / 2) - (text->getHeight() / 2));
    
    button->_shade = SolidImage::newSolidImage("button_shade.png", button->getWidth(), button->getHeight());
    button->_shade->setParent(button);
    button->_shade->hide();

    button->tie();

    return button;
}

void Button::setClickReaction(std::function<void()> call_back_function)
{
    _call_back_function = call_back_function;
}

Button::Button()
{

}

Button::~Button()
{

}

void Button::reactToPressing(const SDL_Point & cursor_coordinates)
{
    _shade->show();
}

void Button::reactToReleasing(const SDL_Point & cursor_coordinates)
{
    _shade->hide();
}

void Button::reactToDragging(const SDL_Point & cursor_coordinates)
{
    _shade->setRelativeX(0);
    _shade->setRelativeY(0);
}

void Button::reactToClick(const SDL_Point & cursor_coordinates)
{
    _call_back_function();
}