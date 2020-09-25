#ifndef _SOLIDTEXT_HPP_
#define _SOLIDTEXT_HPP_

#include "VisualComponent.hpp"
#include <string>
#include <cstdint>

class SolidText : public VisualComponent
{
public:
    static SolidText * newSolidText(const std::string & text,
                                    const std::string & font_name,
                                    uint8_t font_size,
                                    SDL_Color color);

private:
    SolidText(uint16_t width = 0, uint16_t height = 0, SDL_Texture * texture = nullptr);
    virtual ~SolidText();
};

#endif