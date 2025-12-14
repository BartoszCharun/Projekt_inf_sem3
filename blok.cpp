#include "blok.h"

const std::array<sf::Color, 5> Brick::colorLUT = {
    sf::Color(255, 99, 132),   
    sf::Color(255, 195, 0),    
    sf::Color(88, 214, 141),   
    sf::Color(52, 152, 219),  
    sf::Color(155, 89, 182),  
};

Brick::Brick(sf::Vector2f pos, sf::Vector2f size, int zycie_)
{
    maxHP = std::min(static_cast<int>(colorLUT.size()), zycie_);
    zycie = maxHP;
    shape.setSize(size);
    shape.setPosition(pos);
    shape.setFillColor(colorLUT[zycie - 1]);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(sf::Color::Black);
}

void Brick::trafienie()
{
    if (zniszczony) return;
    zycie--;
    if (zycie <= 0)
        zniszczony = true;
    else
        aktualizujkolor();
}

void Brick::aktualizujkolor()
{
    if (!zniszczony && zycie > 0) {
        int idx = std::max(0, std::min(static_cast<int>(colorLUT.size()) - 1, zycie - 1));
        shape.setFillColor(colorLUT[idx]);
    }
}

void Brick::setState(const sf::Vector2f& pos, int hp, bool destroyed)
{
    shape.setPosition(pos);
    zycie = std::max(0, std::min(maxHP, hp));
    zniszczony = destroyed || zycie <= 0;
    if (!zniszczony)
        aktualizujkolor();
}

void Brick::reset()
{
    zniszczony = false;
    zycie = maxHP;
    aktualizujkolor();
}

void Brick::draw(sf::RenderTarget& target)
{
    if (!zniszczony)
        target.draw(shape);
}

sf::Vector2f Brick::getPosition() const
{
    return shape.getPosition();
}

int Brick::getHP() const
{
    return zycie;
}
