#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "blok.h"

class paletka;

class pilka {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity = {6.f, -6.f};

public:
    pilka(float x, float y);

    void update();
    void draw(sf::RenderTarget& target);

    void bounceHorizontally();
    void bounceVertically();

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    void setVelocity(const sf::Vector2f& newVelocity);
    void scaleVelocity(float factor);
    void setPosition(float x, float y);

    // Zwraca true jeśli piłka spadła poniżej obszaru gry.
    bool handleWallCollision(float areaWidth, float areaHeight);
    // Zwraca true przy trafieniu w paletkę (z odbiciem).
    bool handlePaddleCollision(const paletka& paddle);
    // Zwraca liczbę trafionych bloków (z odbiciem pionowym przy pierwszym).
    int handleBricksCollision(std::vector<Brick>& bricks);
};
