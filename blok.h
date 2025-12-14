#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <algorithm>

class Brick {
private:
    sf::RectangleShape shape;
    int zycie;
    int maxHP = 1;
    bool zniszczony = false;

    static const std::array<sf::Color, 5> colorLUT;

public:
    Brick(sf::Vector2f pos, sf::Vector2f size, int zycie_);

    void trafienie();
    void aktualizujkolor();
    void setState(const sf::Vector2f& pos, int hp, bool destroyed);
    void reset();

    bool isDestroyed() const { return zniszczony; }
    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }

    void draw(sf::RenderTarget &target);
    sf::Vector2f getPosition() const;
    int getHP() const;
};
