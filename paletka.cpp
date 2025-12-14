#include "paletka.h"

paletka::paletka(float x, float y)
{
    shape.setSize({100.f, 20.f});
    shape.setFillColor(sf::Color(52, 152, 219));
    shape.setPosition(sf::Vector2f(x, y));
}

void paletka::setSpeed(float newSpeed)
{
    speed = newSpeed;
}

float paletka::getSpeed() const
{
    return speed;
}

void paletka::setPosition(float x, float y)
{
    shape.setPosition(sf::Vector2f(x, y));
}

void paletka::moveLeft()
{
    shape.move(sf::Vector2f(-speed, 0.f));
}

void paletka::moveRight()
{
    shape.move(sf::Vector2f(speed, 0.f));
}

void paletka::update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        moveLeft();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        moveRight();

    auto pos = shape.getPosition();
    auto size = shape.getSize();
    if (pos.x < 0) shape.setPosition(sf::Vector2f(0.f, pos.y));
    if (pos.x + size.x > 800) shape.setPosition(sf::Vector2f(800.f - size.x, pos.y));
}

void paletka::draw(sf::RenderTarget& target)
{
    target.draw(shape);
}

sf::FloatRect paletka::getBounds() const
{
    return shape.getGlobalBounds();
}

sf::Vector2f paletka::getPosition() const
{
    return shape.getPosition();
}
