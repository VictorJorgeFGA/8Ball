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
                                const std::string & background_image_name = "background_test.png",
                                const std::string & font_name = "arial.ttf",
                                const SDL_Color & font_color = {0xFF,0xFF,0,0xFF},
                                uint8_t font_size = 16,
                                int32_t width = 80,
                                int32_t height = 65 );

    void setClickReaction(std::function<void()> call_back_function);

    void setWidth(int32_t width);
    void setHeight(int32_t height);

private:
    std::function<void()> _call_back_function;
    SolidImage * _shade;
    SolidText * _text;

protected:
    Button();
    ~Button();

    virtual void reactToPressing(const SDL_Point & cursor_coordinates);
    virtual void reactToReleasing(const SDL_Point & cursor_coordinates);
    virtual void reactToDragging(const SDL_Point & cursor_coordinates);
    virtual void reactToClick(const SDL_Point & cursor_coordinates);
}; 

#endif