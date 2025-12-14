#include "bloki.h"

void Bloki::generateDefault(float areaWidth, float startY)
{
    bricks.clear();
    const int kolumny = 10;
    const int wiersze = 5;
    float rozmiarX = (areaWidth / kolumny) - 5.f;
    float rozmiarY = 25.f;

    for (int i = 0; i < wiersze; i++) {
        for (int j = 0; j < kolumny; j++) {
            float x = j * (rozmiarX + 5.f) + 2.5f;
            float y = i * (rozmiarY + 5.f) + startY;
            int zycie = (i == 0 ? 5 : (i < 3 ? 3 : (i == 3 ? 2 : 1)));
            bricks.emplace_back(sf::Vector2f(x, y), sf::Vector2f(rozmiarX, rozmiarY), zycie);
        }
    }
}

void Bloki::reset()
{
    for (auto& blok : bricks)
        blok.reset();
}
