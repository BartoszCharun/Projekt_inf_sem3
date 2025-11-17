#pragma once
#include <SFML/Graphics.hpp>

class Pilka {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity = {6.f, -6.f};

public:
    Pilka(float x, float y) {
        shape.setRadius(10.f);
        shape.setFillColor(sf::Color(46, 139, 87));
        shape.setPosition(sf::Vector2f(x, y));
    }

    void update() {
        shape.move(velocity);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    void bounceHorizontally() {
         velocity.x = -velocity.x;
     
         }

    void bounceVertically() {
         velocity.y = -velocity.y;
      
         }

    

    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }

    void setPosition(float x, float y) { shape.setPosition(sf::Vector2f(x, y)); }
};
