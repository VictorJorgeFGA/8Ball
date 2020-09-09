#include "Table.hpp"
#include "PhysicComponent.hpp"
#include "AssetsManager.hpp"
#include "Cushion.hpp"

Table * Table::newTable()
{
    return new Table();
}

void Table::setPosition(const Vector2D & top_left)
{
    _top_left = top_left;
    VisualComponent::setRelativeX(_top_left.x() / PhysicComponent::getScale());
    VisualComponent::setRelativeY(_top_left.y() / PhysicComponent::getScale());
    updateCushionsPosition();
}

Vector2D Table::getPosition() const
{
    return _top_left;
}

Vector2D Table::getTableCenter() const
{
    return Vector2D(_width / 2.0, _height / 2.0);
}

void Table::updateCushionsPosition()
{
    _top_cushion->setPostion(_top_left + Vector2D(19.0, 0.0));
    _right_cushion->setPostion(_top_left + Vector2D(217.0, 19.0));
    _bot_cushion->setPostion(_top_left + Vector2D(19.0, 118.0));
    _left_cushion->setPostion(_top_left + Vector2D(0.0, 19.0));
}

Table::Table():
_width(236.0),
_height(137.0),
_top_left(Vector2D(0.0, 0.0))
{
    PhysicComponent::setScale(236.0 / double_t(Graphics::getInstance()->getWindowWidth()));

    InteractiveComponent::tie();
    VisualComponent::setTexture(AssetsManager::getInstance()->getTexture("table_texture.png"));
    VisualComponent::setWidth(_width / PhysicComponent::getScale());
    VisualComponent::setHeight(_height / PhysicComponent::getScale());

    _top_cushion = Cushion::newCushion(198.0, 19.0);
    _right_cushion = Cushion::newCushion(19.0, 99.0);
    _bot_cushion = Cushion::newCushion(198.0, 19.0);
    _left_cushion = Cushion::newCushion(19.0, 99.0);

    _top_cushion->setParent(this);
    _right_cushion->setParent(this);
    _bot_cushion->setParent(this);
    _left_cushion->setParent(this);

    _top_cushion->deactivate();
    _right_cushion->deactivate();
    _bot_cushion->deactivate();
    _left_cushion->deactivate();

    setPosition(_top_left);
}

Table::~Table()
{

}
