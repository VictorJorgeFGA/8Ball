#include "SolidImage.hpp"
#include "AssetsManager.hpp"

SolidImage * SolidImage::newSolidImage(const std::string & image_name, int32_t width, int32_t height)
{
    AssetsManager * am = AssetsManager::getInstance();

    SolidImage * new_image = new SolidImage();
    new_image->setTexture(am->getTexture(image_name));
    new_image->setWidth(width);
    new_image->setHeight(height);
    new_image->setParent(getScreenObject());

    return new_image;
}

SolidImage::SolidImage():VisualComponent()
{

}

SolidImage::~SolidImage()
{

}
