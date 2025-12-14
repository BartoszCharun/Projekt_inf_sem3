#include "Menu.h"
#include "Napisy.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <algorithm>

Menu::Menu(float width, float height)
{
    viewWidth = width;
    viewHeight = height;

    if (!font.loadFromFile(Napisy::Pliki::font())) {
        
    }


    starfield.init(20, width, height);

    panel.setSize(sf::Vector2f(width * 0.6f, height * 0.62f));
    panel.setFillColor(sf::Color(20, 25, 40, 200));
    panel.setOutlineThickness(2.f);
    panel.setOutlineColor(sf::Color(80, 150, 255, 180));
    panel.setPosition(width * 0.2f, height * 0.30f);

    title.setFont(font);
    title.setString(Napisy::Menu::title());
    title.setCharacterSize(64);
    title.setFillColor(sf::Color(120, 190, 255));
    auto bounds = title.getLocalBounds();
    title.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    title.setPosition(width / 2.f, height * 0.14f);

    const auto& labels = Napisy::Menu::options();
    for (int i = 0; i < labels.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(labels[i]);
        text.setCharacterSize(36);
        text.setFillColor(i == 0 ? sf::Color(120, 190, 255) : sf::Color(230, 230, 235));

        auto b = text.getLocalBounds();
        text.setOrigin(b.width / 2.f, b.height / 2.f);
        text.setPosition(width / 2.f, height * 0.45f + i * 65.f);

        items.push_back(text);
    }

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

    starfield.update();
}

void Menu::draw(sf::RenderTarget& target)
{
    starfield.draw(target);
    target.draw(panel);
    target.draw(title);
    for (auto& item : items)
        target.draw(item);
}

void Menu::drawScores(sf::RenderTarget& target)
{
    starfield.draw(target);
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
    scoreTexts.clear();
    scoreTitle.setString(Napisy::Menu::scoresTitle());
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
        line.setString(Napisy::Menu::noScoresLabel());
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
        line.setString(Napisy::Gra::scoreEntry(static_cast<int>(i + 1), scores[i]));
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
