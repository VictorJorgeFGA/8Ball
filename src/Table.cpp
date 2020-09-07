#include "Table.hpp"
#include "PhysicComponent.hpp"
#include "AssetsManager.hpp"
#include "Cushion.hpp"

Table * Table::newTable(double_t width, double_t height, const Vector2D & top_left)
{
    return new Table(width, height, top_left);
}

void Table::setPosition(const Vector2D & top_left)
{
    _top_left = top_left;
    setRelativeX(_top_left.x() / PhysicComponent::getScale());
    setRelativeY(_top_left.y() / PhysicComponent::getScale());
}

Vector2D Table::getPosition() const
{
    return _top_left;
}

Table::Table(double_t width, double_t height, const Vector2D & top_left):
_width(width),
_height(height),
_top_left(top_left)
{
    InteractiveComponent::tie();
    VisualComponent::setTexture(AssetsManager::getInstance()->getTexture("table_texture.png"));
    VisualComponent::setWidth(_width / PhysicComponent::getScale());
    VisualComponent::setHeight(_height / PhysicComponent::getScale());

    Cushion * temp = Cushion::newCushion(_width, _height * 0.1, Vector2D(0.0, 0.0));
    temp->setParent(this);
    _cushions.push_back(temp);

    temp = Cushion::newCushion(_height * 0.1, _height, Vector2D(width - _height * 0.1, 0.0));
    temp->setParent(this);
    _cushions.push_back(temp);

    temp = Cushion::newCushion(_width, _height * 0.1, Vector2D(0.0, _height - _height * 0.1));
    temp->setParent(this);
    _cushions.push_back(temp);

    temp = Cushion::newCushion(_height * 0.1, _height, Vector2D(0.0, 0.0));
    temp->setParent(this);
    _cushions.push_back(temp);

    setPosition(top_left);
}

Table::~Table()
{

}
