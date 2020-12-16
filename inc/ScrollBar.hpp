#ifndef _SCROLLBAR_HPP_
#define _SCROLLBAR_HPP_

#include "InteractiveComponent.hpp"
#include "SolidImage.hpp"

#include <string>
#include <functional>

class ScrollBar;
class ScrollButton;

class ScrollBar : public InteractiveComponent
{
friend ScrollButton;
public:
    enum ScrollDirection {
        HORIZONTAL,
        VERTICAL
    };

    static ScrollBar * newScrollBar(ScrollDirection scroll_direction,
                                    uint16_t proportion = 8,
                                    uint16_t length = 160,
                                    const std::string & scrollbutton_texture_name = "default_scrollbutton_texture.png");

    // Callback function will be called every time scrollbar changes its "filled" value
    void setCallbackFunction(std::function<void(double_t)> callback);

    double_t getScrolledPercentage() const;

private:
    static void emptyCallback(double_t);

    ScrollBar(const ScrollBar & cpy);
    ScrollBar();
    virtual ~ScrollBar();

    uint16_t _proportion;
    ScrollButton * _scrollbutton;
    ScrollDirection _scroll_direction;
    std::function<void(double_t)> _callback;

};



class ScrollButton : public InteractiveComponent
{
public:
    static ScrollButton * newScrollButton(ScrollBar * parent_scroolbar,
                                          uint16_t width,
                                          uint16_t height,
                                          const std::string & scrollbutton_texture_name);

private:
    ScrollButton();
    virtual ~ScrollButton();

    ScrollBar * _parent_scrollbar;

protected:
    virtual void reactToDragging(const SDL_Point & cursor_coordinates);
};

#endif