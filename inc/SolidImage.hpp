#ifndef _SOLIDIMAGE_HPP_
#define _SOLIDIMAGE_HPP_

#include "VisualComponent.hpp"
#include <string>

class SolidImage : public VisualComponent
{
public:
    static SolidImage * newSolidImage(const std::string & image_name, int32_t width, int32_t height);

private:
    SolidImage();
    ~SolidImage();
};

#endif