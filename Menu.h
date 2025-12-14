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
<<<<<<< HEAD
<<<<<<< HEAD
    std::vector<int> scores;
    sf::Text scoreTitle;
    std::vector<sf::Text> scoreTexts;
=======
>>>>>>> 62e84fae8dc45d5e8d4eb90a1818b6b6ab4340ba
=======
    std::vector<int> scores;
    sf::Text scoreTitle;
    std::vector<sf::Text> scoreTexts;
>>>>>>> d1fffdb418111654297beb545fc433367a96616c
    float animTimer = 0.f;
    Starfield starfield;
    float viewWidth = 0.f;
    float viewHeight = 0.f;
<<<<<<< HEAD
<<<<<<< HEAD
    void loadScores();
    void updateScoreTexts();
=======
>>>>>>> 62e84fae8dc45d5e8d4eb90a1818b6b6ab4340ba
=======
    void loadScores();
    void updateScoreTexts();
>>>>>>> d1fffdb418111654297beb545fc433367a96616c

public:
    Menu(float width, float height);

    void update(sf::Time dt);
    void draw(sf::RenderTarget& target);
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> d1fffdb418111654297beb545fc433367a96616c
    void drawScores(sf::RenderTarget& target);
    void handleEvent(const sf::Event& event);

    int getSelectedItem() const { return selectedIndex; }
    void refreshScores();
<<<<<<< HEAD
=======
    void handleEvent(const sf::Event& event);

    int getSelectedItem() const { return selectedIndex; }
>>>>>>> 62e84fae8dc45d5e8d4eb90a1818b6b6ab4340ba
=======
>>>>>>> d1fffdb418111654297beb545fc433367a96616c
};
