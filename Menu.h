#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "ball.h"
#include "paddle.h"
#include "brick.h"

class Menu {
private:
    sf::Font font;
    std::vector<sf::Text> items;
    int selectedIndex = 0;
    sf::Text title;
    sf::RectangleShape panel;
    float animTimer = 0.f;
    std::vector<sf::ConvexShape> stars;
    std::vector<sf::Vector2f> starVel;
    float viewWidth = 0.f;
    float viewHeight = 0.f;

public:
    Menu(float width, float height);

    void update(sf::Time dt);
    void draw(sf::RenderTarget& target);
    void handleEvent(const sf::Event& event);

    int getSelectedItem() const { return selectedIndex; }
};
