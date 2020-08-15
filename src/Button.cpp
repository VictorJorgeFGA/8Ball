#include "Button.hpp"
#include "AssetsManager.hpp"
#include "SolidImage.hpp"
#include "SolidText.hpp"

Button * Button::newButton( const std::string & button_text,
                            const std::string & background_image_name,
                            const std::string & font_name,
                            const SDL_Color & font_color,
                            uint8_t font_size,
                            int32_t width,
                            int32_t height )
{
    Button * button = new Button();

    AssetsManager * am = AssetsManager::getInstance();
    button->setTexture(am->getTexture(background_image_name));

    SolidText * text = SolidText::newSolidText(button_text, font_name, font_size, font_color);
    text->setParent(button);
    text->setRelativeX((button->getWidth() / 2) - (text->getWidth() / 2));
    text->setRelativeY((button->getHeight() / 2) - (text->getHeight() / 2));
    button->_text = text;

    SolidImage * shade = SolidImage::newSolidImage("button_shade.png", width, height);
    shade->setParent(button);
    shade->setRelativeX(0);
    shade->setRelativeY(0);
    shade->hide();
    button->_shade = shade;

    button->setWidth(width);
    button->setHeight(height);
    button->tie();

    return button;
}

void Button::setClickReaction(std::function<void()> call_back_function)
{
    _call_back_function = call_back_function;
}

void Button::setWidth(int32_t width)
{
    VisualComponent::setWidth(width);
    _shade->setWidth(width);
    _text->setRelativeX((width / 2) - (_text->getWidth() / 2));
}

void Button::setHeight(int32_t height)
{
    VisualComponent::setHeight(height);
    _shade->setHeight(height);
    _text->setRelativeY((height / 2) - (_text->getHeight() / 2));
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

}

void Button::reactToClick(const SDL_Point & cursor_coordinates)
{
    _call_back_function();
}