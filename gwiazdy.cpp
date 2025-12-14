#include "gwiazdy.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

Starfield::Starfield(int count, float w, float h)
{
    init(count, w, h);
}

void Starfield::init(int count, float w, float h)
{
    width = w;
    height = h;
    stars.clear();
    velocities.clear();

    static bool seeded = false;
    if (!seeded) { std::srand(static_cast<unsigned>(std::time(nullptr))); seeded = true; }

    stars.reserve(count);
    velocities.reserve(count);
    for (int i = 0; i < count; ++i) {
        float x = static_cast<float>(std::rand() % static_cast<int>(width));
        float y = static_cast<float>(std::rand() % static_cast<int>(height));
        float r = static_cast<float>(1.f + std::rand() % 4) * 0.3f; // 1.0 - 2.2
        sf::CircleShape star(r);
        star.setFillColor(sf::Color(200, 220, 255, 200));
        star.setPosition(x, y);
        stars.push_back(star);
        float vx = (static_cast<float>(std::rand() % 11) - 5.f) * 0.03f; // -0.15..0.15
        float vy = (static_cast<float>(std::rand() % 11) - 5.f) * 0.03f;
        velocities.push_back({vx, vy});
    }
}

void Starfield::update()
{
    for (size_t i = 0; i < stars.size(); ++i) {
        stars[i].move(velocities[i]);
        auto pos = stars[i].getPosition();
        float r = stars[i].getRadius();
        if (pos.x < -r) pos.x = width;
        if (pos.x > width) pos.x = -r;
        if (pos.y < -r) pos.y = height;
        if (pos.y > height) pos.y = -r;
        stars[i].setPosition(pos);
    }
}

void Starfield::draw(sf::RenderTarget& target) const
{
    for (const auto& star : stars)
        target.draw(star);
}

StarryMenuBackground::StarryMenuBackground(float width, float height, int count)
{
    starfield.init(count, width, height);
}

void StarryMenuBackground::update()
{
    starfield.update();
}

void StarryMenuBackground::draw(sf::RenderTarget& target) const
{
    starfield.draw(target);
}
