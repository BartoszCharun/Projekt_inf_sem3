#include "Menu.h"
#include "Napisy.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <algorithm>

Menu::Menu(float width, float height)
    : starBackground(width, height, 20), viewWidth(width), viewHeight(height)
{

    if (!font.loadFromFile(Napisy::Pliki::font())) {
        
    }

    Napisy::Menu::initLayout(font, panel, title, width, height);

    items = Napisy::Menu::createMenuItems(font, width, height);

    scoreTitle.setFont(font);
    scoreTitle.setCharacterSize(40);
    scoreTitle.setFillColor(sf::Color(120, 190, 255));
    scoreTitle.setString(Napisy::Menu::scoresTitle());

    refreshScores();
}

void Menu::update(sf::Time dt)
{
    animTimer += dt.asSeconds();
    float scale = 1.f + 0.04f * std::sin(animTimer * 2.5f);
    title.setScale(scale, scale);

    starBackground.update();
}

void Menu::draw(sf::RenderTarget& target)
{
    starBackground.draw(target);
    target.draw(panel);
    target.draw(title);
    for (auto& item : items)
        target.draw(item);
}

void Menu::drawScores(sf::RenderTarget& target)
{
    starBackground.draw(target);
    target.draw(panel);
    target.draw(scoreTitle);
    for (auto& line : scoreTexts)
        target.draw(line);
}

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

void Menu::loadScores()
{
    scores.clear();
    std::ifstream file(Napisy::Pliki::score());
    if (!file.is_open()) return;

    int v = 0;
    while (file >> v) scores.push_back(v);
    std::sort(scores.begin(), scores.end(), std::greater<int>());
    if (scores.size() > 5) scores.resize(5);
}

void Menu::updateScoreTexts()
{
    scoreTexts = Napisy::Menu::createScoreTexts(font, scores, viewWidth, viewHeight, scoreTitle);
}

void Menu::refreshScores()
{
    loadScores();
    updateScoreTexts();
}
