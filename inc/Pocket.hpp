#ifndef _POCKET_HPP_
#define _POCKET_HPP_

#include "PhysicComponent.hpp"
#include "Vector2D.hpp"
#include "SolidImage.hpp"
#include <string>


class Pocket : public PhysicComponent
{
public:
    static const std::string POCKET_TEXTURE;
    static const std::string POCKET_SPOTLIGHT_TEXTURE;
    
    static Pocket * newPocket(const Vector2D center, double_t radius);
    
    static void enablePocketChoice() noexcept;
    static void disablePocketChoice() noexcept;

    void setCenter(const Vector2D & center) noexcept;
    Vector2D getCenter() const noexcept;

    void setRadius(double_t radius) noexcept;
    double_t getRadius() const noexcept;


private:
    static Pocket * chosen_pocket;
    static bool can_choose_pocket;
    
    void updateTextureCoordinates() noexcept;
    void updateTextureSize() noexcept;

    Pocket();
    Pocket(const Vector2D center, double_t radius);
    virtual ~Pocket();

    Vector2D _center;
    double_t _radius;
    SolidImage * _spotlight;

protected:

    virtual void reactToClick(const SDL_Point & cursor_coordinates) override;
};

#endif