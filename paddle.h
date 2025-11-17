#pragma once
#include <SFML/Graphics.hpp>

class Paletka {
private:
    sf::RectangleShape shape;
    float speed = 6.f;

public:
    Paletka(float x, float y) {
        shape.setSize({100.f, 20.f});
        shape.setFillColor(sf::Color(229, 127, 61));
        shape.setPosition(sf::Vector2f(x, y));
    }

    void moveLeft() {
        shape.move(sf::Vector2f(-speed, 0.f));
    }

    void moveRight() {
        shape.move(sf::Vector2f(speed, 0.f));
    }

    void update() {
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) moveLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) moveRight();

        auto pos = shape.getPosition();
        auto size = shape.getSize();
        if (pos.x < 0) shape.setPosition(sf::Vector2f(0.f, pos.y));
        if (pos.x + size.x > 800) shape.setPosition(sf::Vector2f(800.f - size.x, pos.y));
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }
};
