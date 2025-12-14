#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "pilka.h"
#include "paletka.h"
#include "blok.h"
#include "gwiazdy.h"

class Menu {
private:
    sf::Font font;
    std::vector<sf::Text> items;
    int selectedIndex = 0;
    sf::Text title;
    sf::RectangleShape panel;
    std::vector<int> scores;
    sf::Text scoreTitle;
    std::vector<sf::Text> scoreTexts;
    float animTimer = 0.f;
    StarryMenuBackground starBackground;
    float viewWidth = 0.f;
    float viewHeight = 0.f;
    void loadScores();
    void updateScoreTexts();

public:
    Menu(float width, float height);

    void update(sf::Time dt);
    void draw(sf::RenderTarget& target);
    void drawScores(sf::RenderTarget& target);
    void handleEvent(const sf::Event& event);

    int getSelectedItem() const { return selectedIndex; }
    void refreshScores();
};
