#ifndef _BUTTON_HPP_
#define _BUTTON_HPP_

#include "InteractiveComponent.hpp"
#include "SolidImage.hpp"
#include "SolidText.hpp"
#include "SDL.hpp"

#include <functional>
#include <string>

class Button : public InteractiveComponent
{
public:
    static Button * newButton(  const std::string & button_text,
                                const std::string & background_image_name = "button_background.png",
                                const std::string & font_name = "arial.ttf",
                                const SDL_Color & font_color = {0xFF,0xFF,0,0xFF},
                                uint8_t font_size = 16,
                                uint16_t width = 120,
                                uint16_t height = 50 );

    void setClickReaction(std::function<void()> call_back_function);

    void setWidth(uint16_t width);
    void setHeight(uint16_t height);

private:
    Button();
    Button(const Button & cpy);

    std::function<void()> _call_back_function;
    SolidImage * _shade;
    SolidText * _text;

protected:
    Button(uint16_t width, uint16_t height, SDL_Texture * texture = nullptr);
    virtual ~Button();

    virtual void reactToPressing(const SDL_Point & cursor_coordinates) override;
    virtual void reactToReleasing(const SDL_Point & cursor_coordinates) override;
    virtual void reactToClick(const SDL_Point & cursor_coordinates) override;
}; 

#endif