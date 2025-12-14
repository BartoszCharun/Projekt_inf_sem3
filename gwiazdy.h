#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

// Prosta scena z latającymi gwiazdkami w tle.
class Starfield {
private:
    std::vector<sf::CircleShape> stars;
    std::vector<sf::Vector2f> velocities;
    float width = 0.f;
    float height = 0.f;

public:
    Starfield() = default;
    Starfield(int count, float w, float h);

    void init(int count, float w, float h);
    void update();
    void draw(sf::RenderTarget& target) const;
};

class StarryMenuBackground {
private:
    Starfield starfield;

public:
    StarryMenuBackground(float width, float height, int count);
    void update();
    void draw(sf::RenderTarget& target) const;
};
