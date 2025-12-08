#pragma once
#include <SFML/Graphics.hpp>

class pilka {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity = {6.f, -6.f};

public:
    pilka(float x, float y) {
        shape.setRadius(10.f);
        shape.setFillColor(sf::Color(241, 196, 15));
        shape.setPosition(sf::Vector2f(x, y));
    }

    void update() {
        shape.move(velocity);
    }

    void draw(sf::RenderTarget& target) {
        target.draw(shape);
    }
        

    void bounceHorizontally() {
         velocity.x = -velocity.x;
     
         }

    void bounceVertically() {
         velocity.y = -velocity.y;
      
         }

    

    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }
    sf::Vector2f getPosition() const {
        return shape.getPosition();
    }
    sf::Vector2f getVelocity() const {
        return velocity;
    }
    void setVelocity(const sf::Vector2f& newVelocity) {
        velocity = newVelocity;
    }
    void scaleVelocity(float factor) {
        velocity.x *= factor;
        velocity.y *= factor;
    }
    

    void setPosition(float x, float y) { shape.setPosition(sf::Vector2f(x, y)); }
};
