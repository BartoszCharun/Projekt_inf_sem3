#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class Brick : public sf::RectangleShape {
private:
    int zycie;
    bool zniszczony = false;
    const std::array<sf::Color, 5> colorLUT = {
        sf::Color::White,
        sf::Color::Blue,
        sf::Color::Green,
        sf::Color::Yellow,
        sf::Color::Magenta,
    };

public:
    Brick(sf::Vector2f pos, sf::Vector2f size, int zycie_) {
        zycie = zycie_;
        setSize(size);
        setPosition(pos);
        setFillColor(colorLUT[zycie]);
        setOutlineThickness(1.f);
    }

    void trafienie() {
        if (zniszczony) return;
        zycie--;
        if (zycie <= 0) zniszczony = true;
        aktualizujkolor();
    }

    void aktualizujkolor() {
        if (!zniszczony && zycie > 0 && zycie <= (int)colorLUT.size()) {
            setFillColor(colorLUT[zycie - 1]);
        }
    }

    bool isDestroyed() const { return zniszczony; }

    sf::FloatRect getBounds() const { return getGlobalBounds(); }

    void draw(sf::RenderWindow &window) {
        if (!zniszczony)
            window.draw(static_cast<sf::RectangleShape&>(*this));
    }

};
