#pragma once
#include <SFML/Graphics.hpp>

class paletka {
private:
    sf::RectangleShape shape;
    float speed = 8.f;

public:
    paletka(float x, float y);

    void setSpeed(float newSpeed);
    float getSpeed() const;
    void setPosition(float x, float y);

    void moveLeft();
    void moveRight();
    void update();
    void draw(sf::RenderTarget& target);

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
};
