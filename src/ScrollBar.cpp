#include "ScrollBar.hpp"
#include "AssetsManager.hpp"
#include "SolidImage.hpp"

ScrollBar * ScrollBar::newScrollBar(ScrollDirection scroll_directon,
                                    uint16_t scrollbar_length,
                                    uint16_t scrollbar_margin,
                                    uint16_t scrollbar_porportion,
                                    const std::string & fillbar_texture_name,
                                    const std::string & scrollbar_body_texture_name,
                                    const std::string & scroll_button_texture_name)
{
    ScrollBar * scrollbar = new ScrollBar();
    
    scrollbar->_proportion = scrollbar_porportion;
    scrollbar->_scroll_direction = scroll_directon;
    scrollbar->_scrollbar_margin = scrollbar_margin;

    scrollbar->setParent(VisualComponent::getScreenObject());
    scrollbar->setTexture(AssetsManager::getInstance()->getTexture(scrollbar_body_texture_name));
    scrollbar->setRelativeX(0);
    scrollbar->setRelativeY(0);

    scrollbar->tie();

    SolidImage * solid_image = nullptr;

    solid_image = SolidImage::newSolidImage(fillbar_texture_name, 1, 1);
    scrollbar->_fillbar_texture = solid_image;
    scrollbar->_fillbar_texture->setParent(scrollbar);
    scrollbar->_fillbar_texture->setRelativeX(scrollbar_margin);
    scrollbar->_fillbar_texture->setRelativeY(scrollbar_margin);

    solid_image = SolidImage::newSolidImage(scroll_button_texture_name, 1, 1);
    scrollbar->_scroll_button = solid_image;
    scrollbar->_scroll_button->setParent(scrollbar);
    scrollbar->_scroll_button->setRelativeX(0);
    scrollbar->_scroll_button->setRelativeY(0);
    
    scrollbar->updateScrollBarSize(scrollbar_length);

    scrollbar->setScrollX(0);
    scrollbar->setScrollY(0);

    scrollbar->_call_back = ScrollBar::emptyCallback;

    return scrollbar;
}

void ScrollBar::setScrollingEventCallback(std::function<void(double_t)> scrolling_event_callback)
{
    _call_back = scrolling_event_callback;
}

double_t ScrollBar::getFilledPercentage() const
{
    return double_t(getFilledSize()) / double_t(getMaxFillSize());
}

void ScrollBar::updateScrollBarSize(int32_t length)
{
    if (_scroll_direction == HORIZONTAL) {
        VisualComponent::setWidth(length);
        VisualComponent::setHeight(length / _proportion);
        
        _fillbar_texture->setHeight(length / _proportion - 2 * _scrollbar_margin);
        
    } else {
        VisualComponent::setHeight(length);
        VisualComponent::setWidth(length / _proportion);

        _fillbar_texture->setWidth(length / _proportion - 2 * _scrollbar_margin);
    }
    _scroll_button->setWidth(length / _proportion);
    _scroll_button->setHeight(length / _proportion);
}

void ScrollBar::emptyCallback(double_t x)
{

}

int32_t ScrollBar::getMaxFillSize() const
{
    if (_scroll_direction == HORIZONTAL)
        return VisualComponent::getWidth() - 2 * _scrollbar_margin;
    else
        return VisualComponent::getHeight() - 2 * _scrollbar_margin;
}

int32_t ScrollBar::getFilledSize() const
{
    if (_scroll_direction == HORIZONTAL)
        return _fillbar_texture->getWidth();
    else
        return _fillbar_texture->getHeight();
}

int32_t ScrollBar::getMinScrollX() const
{
    return VisualComponent::getGlobalX() + _scrollbar_margin;
}

int32_t ScrollBar::getMaxScrollX() const
{
    return VisualComponent::getGlobalX() + VisualComponent::getWidth() - _scrollbar_margin;
}

int32_t ScrollBar::getMinScrollY() const
{
    return VisualComponent::getGlobalY() + _scrollbar_margin;
}

int32_t ScrollBar::getMaxScrollY() const
{
    return VisualComponent::getGlobalY() + VisualComponent::getHeight() - _scrollbar_margin;
}

void ScrollBar::setScrollX(int32_t x)
{
    if (_scroll_direction == VERTICAL)
        return;

    x = x < getMinScrollX() ? getMinScrollX() : x;
    x = x > getMaxScrollX() ? getMaxScrollX() : x;
    _fillbar_texture->setWidth(x - getMinScrollX());

    x = x < getMinScrollX() + _scroll_button->getWidth() / 2 ? getMinScrollX() + _scroll_button->getWidth() / 2 : x;
    x = x > getMaxScrollY() - _scroll_button->getWidth() / 2 ? getMaxScrollY() - _scroll_button->getWidth() / 2 : x;
    _scroll_button->setGlobalX(x);
}

void ScrollBar::setScrollY(int32_t y)
{
    if (_scroll_direction == HORIZONTAL)
        return;

    y = y < getMinScrollY() ? getMinScrollY() : y;
    y = y > getMaxScrollY() ? getMaxScrollY() : y;
    _fillbar_texture->setHeight(y - getMinScrollY());

    y = y < getMinScrollY() + _scroll_button->getHeight() / 2 ? getMinScrollY() + _scroll_button->getHeight() / 2 : y;
    y = y > getMaxScrollY() - _scroll_button->getHeight() / 2 ? getMaxScrollY() - _scroll_button->getHeight() / 2 : y;
    _scroll_button->setGlobalY(y);
}

ScrollBar::ScrollBar()
{

}

ScrollBar::~ScrollBar()
{

}

void ScrollBar::reactToClick(const SDL_Point & cursor_coordinates)
{
    setScrollX(cursor_coordinates.x);
    setScrollY(cursor_coordinates.y);
    _call_back(getFilledSize());
}

void ScrollBar::reactToDragging(const SDL_Point & cursor_coordinates)
{
    setScrollX(cursor_coordinates.x);
    setScrollY(cursor_coordinates.y);
    _call_back(getFilledSize());
}
