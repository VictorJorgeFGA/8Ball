#include "SolidText.hpp"
#include "AssetsManager.hpp"
#include "SDL.hpp"
#include "SDL_ttf.hpp"

SolidText * SolidText::newSolidText(const std::string & text, const std::string & font_name, uint8_t font_size, SDL_Color color)
{
    SolidText * new_text = new SolidText();

    AssetsManager * am = AssetsManager::getInstance();
    new_text->setTexture(am->getTextTexture(font_name, font_size, text, color));
    
    int32_t w, h;
    TTF_SizeText(am->getFont(font_name, font_size), text.c_str(), &w, &h);
    
    new_text->setWidth(w);
    new_text->setHeight(h);
    new_text->setParent(getScreenObject());

    return new_text;
}

SolidText::SolidText():VisualComponent()
{

}

SolidText::~SolidText()
{

}