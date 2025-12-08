#pragma once
#include <SFML/Graphics.hpp>

class paletka {
private:
    sf::RectangleShape shape;
    float speed = 8.f;

public:
    paletka(float x, float y) {
        shape.setSize({100.f, 20.f});
        shape.setFillColor(sf::Color(52, 152, 219));
        shape.setPosition(sf::Vector2f(x, y));
    }

    void setSpeed(float newSpeed) {
        speed = newSpeed;
    }

    float getSpeed() const {
        return speed;
    }

    void setPosition(float x, float y) {
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

    void draw(sf::RenderTarget& target) {
        target.draw(shape);
    }
    

    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }

    sf::Vector2f getPosition() const {
        return shape.getPosition();
    }

    
};
