#ifndef _SCROLLBAR_HPP_
#define _SCROLLBAR_HPP_

#include "InteractiveComponent.hpp"
#include "SolidImage.hpp"

#include <string>
#include <functional>

class ScrollBar : public InteractiveComponent
{
public:
    enum ScrollDirection {
        HORIZONTAL,
        VERTICAL
    };

    static ScrollBar * newScrollBar(ScrollDirection scroll_direction,
                                    uint16_t scrollbar_length = 80, // in pixels
                                    uint16_t scrollbar_margin = 5, // in pixels
                                    uint16_t scrollbar_porportion = 6, // x:1 - for example: 8:1
                                    const std::string & fillbar_texture_name = "scroll_fillbar_texture.png",
                                    const std::string & scrollbar_body_texture_name = "scrollbar_body_texture.png",
                                    const std::string & scroll_button_texture_name = "scroll_button_texture.png");

    // scrolling_event_callback will be called whenever scrollbar changes its state
    // getFilledPercentage will be assigned to callback function argument
    void setScrollingEventCallback(std::function<void(double_t)> scrolling_event_callback);

    double_t getFilledPercentage() const;

    void updateScrollBarSize(int32_t length);

private:
    static void emptyCallback(double_t x);

    int32_t getMaxFillSize() const;
    int32_t getFilledSize() const;

    int32_t getMinScrollX() const;
    int32_t getMaxScrollX() const;

    int32_t getMinScrollY() const;
    int32_t getMaxScrollY() const;

    void setScrollX(int32_t x);
    void setScrollY(int32_t y);

    ScrollBar();
    virtual ~ScrollBar();

    uint16_t _proportion;
    uint16_t _scrollbar_margin;
    SolidImage * _fillbar_texture;
    SolidImage * _scroll_button;
    ScrollDirection _scroll_direction;
    std::function<void(double_t)> _call_back;

protected:

    virtual void reactToClick(const SDL_Point & cursor_coordinates);
    virtual void reactToDragging(const SDL_Point & cursor_coordinates);

};

#endif