#ifndef _BUTTON_HPP_
#define _BUTTON_HPP_

#include "InteractiveComponent.hpp"
#include "SolidImage.hpp"
#include "SolidText.hpp"
#include <functional>

class Button : public InteractiveComponent
{
public:
    static Button * newButton(SolidImage * background, SolidText * text);

    void setClickReaction(std::function<void()> call_back_function);

private:
    std::function<void()> _call_back_function;
    SolidImage * _shade;

protected:
    Button();
    ~Button();

    virtual void reactToPressing(const SDL_Point & cursor_coordinates);
    virtual void reactToReleasing(const SDL_Point & cursor_coordinates);
    virtual void reactToDragging(const SDL_Point & cursor_coordinates);
    virtual void reactToClick(const SDL_Point & cursor_coordinates);
};

#endif