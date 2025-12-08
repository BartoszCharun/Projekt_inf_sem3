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
    Brick(sf::Vector2f pos, sf::Vector2f size, int zycie_) {
        maxHP = std::min((int)colorLUT.size(), zycie_);
        zycie = maxHP;
        shape.setSize(size);
        shape.setPosition(pos);
        shape.setFillColor(colorLUT[zycie - 1]);
        shape.setOutlineThickness(1.f);
        shape.setOutlineColor(sf::Color::Black);
    }

    void trafienie() {
        if (zniszczony) return;
        zycie--;
        if (zycie <= 0)
            zniszczony = true;
        else
            aktualizujkolor();
    }

    void aktualizujkolor() {
        if (!zniszczony && zycie > 0) {
            int idx = std::max(0, std::min((int)colorLUT.size() - 1, zycie - 1));
            shape.setFillColor(colorLUT[idx]);
        }
    }

    void setState(const sf::Vector2f& pos, int hp, bool destroyed) {
        shape.setPosition(pos);
        zycie = std::max(0, std::min(maxHP, hp));
        zniszczony = destroyed || zycie <= 0;
        if (!zniszczony)
            aktualizujkolor();
    }

    void reset() {
        zniszczony = false;
        zycie = maxHP;
        aktualizujkolor();
    }

    bool isDestroyed() const { return zniszczony; }
    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }

    void draw(sf::RenderTarget &target) {
        if (!zniszczony)
            target.draw(shape);
    }
    sf::Vector2f getPosition() const {
        return shape.getPosition();
    }
    int getHP() const {
        return zycie;
    }
};
