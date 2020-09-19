#include "ScrollBar.hpp"
#include "AssetsManager.hpp"

ScrollBar * ScrollBar::newScrollBar(ScrollDirection scroll_direction,
                                    uint16_t proportion,
                                    uint16_t length,
                                    const std::string & scrollbutton_texture_name)
{
    ScrollBar * scrollbar = new ScrollBar();
    scrollbar->_scroll_direction = scroll_direction;
    
    if (scroll_direction == HORIZONTAL) {
        scrollbar->setWidth(length);
        scrollbar->setHeight(length / proportion);
        scrollbar->setTexture(AssetsManager::getInstance()->getTexture("horizontal_default_scrollbar_background_texture.png"));
    } else {
        scrollbar->setWidth(length / proportion);
        scrollbar->setHeight(length);
        scrollbar->setTexture(AssetsManager::getInstance()->getTexture("vertical_default_scrollbar_background_texture.png"));
    }
    scrollbar->setRelativeX(0);
    scrollbar->setRelativeY(0);

    scrollbar->_proportion = proportion;
    scrollbar->_callback = ScrollBar::emptyCallback;

    ScrollButton * scrollbutton = ScrollButton::newScrollButton(scrollbar, length / proportion, length / proportion, scrollbutton_texture_name);
    scrollbar->_scrollbutton = scrollbutton;

    scrollbar->deactivate();

    return scrollbar;
}

void ScrollBar::setCallbackFunction(std::function<void(double_t)> callback)
{
    _callback = callback; 
}

double_t ScrollBar::getScrolledPercentage() const
{
    if (_scroll_direction == HORIZONTAL) {
        double_t max_size = getWidth() - _scrollbutton->getWidth();
        double_t cur_size = _scrollbutton->getGlobalX() - VisualComponent::getGlobalX();
        return 100.0 * (cur_size / max_size);
    } else {
        double_t max_size = getHeight() - _scrollbutton->getHeight();
        double_t cur_size = _scrollbutton->getGlobalY() - VisualComponent::getGlobalY();
        return 100.0 * (cur_size / max_size);
    }
}

void ScrollBar::emptyCallback(double_t x)
{

}

ScrollBar::ScrollBar()
{

}

ScrollBar::~ScrollBar()
{

}

ScrollButton * ScrollButton::newScrollButton(ScrollBar * parent_scrollbar,
                                             uint16_t width,
                                             uint16_t height,
                                             const std::string & scrollbutton_texture_name)
{
    ScrollButton * scrollbutton = new ScrollButton();
    scrollbutton->setWidth(width);
    scrollbutton->setHeight(height);
    scrollbutton->setRelativeX(0);
    scrollbutton->setRelativeY(0);
    scrollbutton->setTexture(AssetsManager::getInstance()->getTexture(scrollbutton_texture_name));
    scrollbutton->untie();

    scrollbutton->setParent(parent_scrollbar);
    scrollbutton->_parent_scrollbar = parent_scrollbar;

    return scrollbutton;
}

ScrollButton::ScrollButton()
{

}

ScrollButton::~ScrollButton()
{

}

void ScrollButton::reactToDragging(const SDL_Point & cursor_coordinates)
{
    _parent_scrollbar->_callback(_parent_scrollbar->getScrolledPercentage());
}