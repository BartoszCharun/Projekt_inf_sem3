#include "Menu.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> d1fffdb418111654297beb545fc433367a96616c
#include <fstream>
#include <algorithm>

namespace {
const char* SCORE_FILE = "scores.txt";
}
<<<<<<< HEAD
=======
>>>>>>> 62e84fae8dc45d5e8d4eb90a1818b6b6ab4340ba
=======
>>>>>>> d1fffdb418111654297beb545fc433367a96616c

Menu::Menu(float width, float height)
{
    viewWidth = width;
    viewHeight = height;

    if (!font.loadFromFile("Arimo-Regular.ttf")) {
        
    }


    starfield.init(20, width, height);

<<<<<<< HEAD
    
        float outerR = 3.4f + static_cast<float>(std::rand() % 5) * 1.45f; // ~2.4 - 4.2
        float innerR = outerR * 0.5f;
        sf::ConvexShape star(10);
        for (int p = 0; p < 10; ++p) {
            float angle = p * 36.f * 3.14159265f / 180.f;
            float radius = (p % 2 == 0) ? outerR : innerR;
            star.setPoint(p, {radius * std::cos(angle), radius * std::sin(angle)});
        }
        auto lb = star.getLocalBounds();
        star.setOrigin(lb.width / 2.f, lb.height / 2.f);
        star.setFillColor(sf::Color(200, 220, 255, 180));
        star.setPosition(x, y);
        stars.push_back(star);
        float vx = (static_cast<float>(std::rand() % 11) - 5.f) * 0.02f; // -0.1..0.1
        float vy = (static_cast<float>(std::rand() % 11) - 5.f) * 0.02f;
        starVel.push_back({vx, vy});
    }

<<<<<<< HEAD
    panel.setSize(sf::Vector2f(width * 0.6f, height * 0.62f));
    panel.setFillColor(sf::Color(20, 25, 40, 200));
    panel.setOutlineThickness(2.f);
    panel.setOutlineColor(sf::Color(80, 150, 255, 180));
    panel.setPosition(width * 0.2f, height * 0.30f);
=======
    panel.setSize(sf::Vector2f(width * 0.6f, height * 0.5f));
    panel.setFillColor(sf::Color(20, 25, 40, 200));
    panel.setOutlineThickness(2.f);
    panel.setOutlineColor(sf::Color(80, 150, 255, 180));
    panel.setPosition(width * 0.2f, height * 0.35f);
>>>>>>> 62e84fae8dc45d5e8d4eb90a1818b6b6ab4340ba
=======
    panel.setSize(sf::Vector2f(width * 0.6f, height * 0.62f));
    panel.setFillColor(sf::Color(20, 25, 40, 200));
    panel.setOutlineThickness(2.f);
    panel.setOutlineColor(sf::Color(80, 150, 255, 180));
    panel.setPosition(width * 0.2f, height * 0.30f);
>>>>>>> d1fffdb418111654297beb545fc433367a96616c

    title.setFont(font);
    title.setString("ARKANOID");
    title.setCharacterSize(64);
    title.setFillColor(sf::Color(120, 190, 255));
    auto bounds = title.getLocalBounds();
    title.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
<<<<<<< HEAD
<<<<<<< HEAD
    title.setPosition(width / 2.f, height * 0.14f);
=======
    title.setPosition(width / 2.f, height * 0.18f);
>>>>>>> 62e84fae8dc45d5e8d4eb90a1818b6b6ab4340ba
=======
    title.setPosition(width / 2.f, height * 0.14f);
>>>>>>> d1fffdb418111654297beb545fc433367a96616c

    std::vector<std::string> labels = {
        "Nowa gra",
        "Wczytaj gre",
<<<<<<< HEAD
<<<<<<< HEAD
        "Tabela wynikow",
=======
>>>>>>> 62e84fae8dc45d5e8d4eb90a1818b6b6ab4340ba
=======
        "Tabela wynikow",
>>>>>>> d1fffdb418111654297beb545fc433367a96616c
        "Wyjscie"
    };

    for (int i = 0; i < labels.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(labels[i]);
        text.setCharacterSize(36);
        text.setFillColor(i == 0 ? sf::Color(120, 190, 255) : sf::Color(230, 230, 235));

        auto b = text.getLocalBounds();
        text.setOrigin(b.width / 2.f, b.height / 2.f);
<<<<<<< HEAD
<<<<<<< HEAD
        text.setPosition(width / 2.f, height * 0.45f + i * 65.f);

        items.push_back(text);
    }

    refreshScores();
=======
        text.setPosition(width / 2.f, height / 2.f + i * 70.f);

        items.push_back(text);
    }
>>>>>>> 62e84fae8dc45d5e8d4eb90a1818b6b6ab4340ba
=======
        text.setPosition(width / 2.f, height * 0.45f + i * 65.f);

        items.push_back(text);
    }

    refreshScores();
>>>>>>> d1fffdb418111654297beb545fc433367a96616c
}

void Menu::update(sf::Time dt)
{
    animTimer += dt.asSeconds();
    float scale = 1.f + 0.04f * std::sin(animTimer * 2.5f);
    title.setScale(scale, scale);

    starfield.update();
}

void Menu::draw(sf::RenderTarget& target)
{
<<<<<<< HEAD
    for (auto& star : stars)
        target.draw(star);
<<<<<<< HEAD
        target.draw(panel);
        target.draw(title);
=======
=======
    starfield.draw(target);
>>>>>>> d1fffdb418111654297beb545fc433367a96616c
    target.draw(panel);
    target.draw(title);
>>>>>>> 62e84fae8dc45d5e8d4eb90a1818b6b6ab4340ba
    for (auto& item : items)
        target.draw(item);
}

<<<<<<< HEAD
<<<<<<< HEAD
void Menu::drawScores(sf::RenderTarget& target)
{
    for (auto& star : stars)
        target.draw(star);
        target.draw(panel);
        target.draw(scoreTitle);
=======
void Menu::drawScores(sf::RenderTarget& target)
{
    starfield.draw(target);
    target.draw(panel);
    target.draw(scoreTitle);
>>>>>>> d1fffdb418111654297beb545fc433367a96616c
    for (auto& line : scoreTexts)
        target.draw(line);
}

<<<<<<< HEAD
=======
>>>>>>> 62e84fae8dc45d5e8d4eb90a1818b6b6ab4340ba
=======
>>>>>>> d1fffdb418111654297beb545fc433367a96616c
void Menu::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            selectedIndex--;
            if (selectedIndex < 0) selectedIndex = items.size() - 1;
        }
        else if (event.key.code == sf::Keyboard::Down) {
            selectedIndex++;
            if (selectedIndex >= items.size()) selectedIndex = 0;
        }

        // aktualizacja kolorów
        for (int i = 0; i < items.size(); i++)
            items[i].setFillColor(i == selectedIndex ? sf::Color(120, 190, 255) : sf::Color(230, 230, 235));
    }
}
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> d1fffdb418111654297beb545fc433367a96616c

void Menu::loadScores()
{
    scores.clear();
    std::ifstream file(SCORE_FILE);
    if (!file.is_open()) return;

    int v = 0;
    while (file >> v) scores.push_back(v);
    std::sort(scores.begin(), scores.end(), std::greater<int>());
    if (scores.size() > 5) scores.resize(5);
}

void Menu::updateScoreTexts()
{
    scoreTexts.clear();
    auto b = scoreTitle.getLocalBounds();
    scoreTitle.setOrigin(b.width / 2.f, b.height / 2.f);
    scoreTitle.setPosition(viewWidth / 2.f, viewHeight * 0.36f);

    float startY = viewHeight * 0.48f;
    float step = 42.f;
    if (scores.empty()) {
        sf::Text line;
        line.setFont(font);
        line.setCharacterSize(28);
        line.setFillColor(sf::Color(230, 230, 235));
        line.setString("Brak wynikow");
        auto lb = line.getLocalBounds();
        line.setOrigin(lb.width / 2.f, lb.height / 2.f);
        line.setPosition(viewWidth / 2.f, startY);
        scoreTexts.push_back(line);
        return;
    }

    for (size_t i = 0; i < scores.size(); ++i) {
        sf::Text line;
        line.setFont(font);
        line.setCharacterSize(28);
        line.setFillColor(sf::Color(230, 230, 235));
        line.setString(std::to_string(i + 1) + ". " + std::to_string(scores[i]) + " odbic");
        auto lb = line.getLocalBounds();
        line.setOrigin(lb.width / 2.f, lb.height / 2.f);
        line.setPosition(viewWidth / 2.f, startY + step * static_cast<float>(i));
        scoreTexts.push_back(line);
    }
}

void Menu::refreshScores()
{
    loadScores();
    updateScoreTexts();
}
<<<<<<< HEAD
=======
>>>>>>> 62e84fae8dc45d5e8d4eb90a1818b6b6ab4340ba
=======
>>>>>>> d1fffdb418111654297beb545fc433367a96616c
