#include "Menu.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

Menu::Menu(float width, float height)
{
    viewWidth = width;
    viewHeight = height;

    if (!font.loadFromFile("Arimo-Regular.ttf")) {
        
    }


    static bool seeded = false;
    if (!seeded) { std::srand(static_cast<unsigned>(std::time(nullptr))); seeded = true; }
    const int starCount = 20;
    stars.reserve(starCount);
    starVel.reserve(starCount);
    for (int i = 0; i < starCount; ++i) {
        float x = static_cast<float>(std::rand() % static_cast<int>(width));
        float y = static_cast<float>(std::rand() % static_cast<int>(height));

    
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

    panel.setSize(sf::Vector2f(width * 0.6f, height * 0.5f));
    panel.setFillColor(sf::Color(20, 25, 40, 200));
    panel.setOutlineThickness(2.f);
    panel.setOutlineColor(sf::Color(80, 150, 255, 180));
    panel.setPosition(width * 0.2f, height * 0.35f);

    title.setFont(font);
    title.setString("ARKANOID");
    title.setCharacterSize(64);
    title.setFillColor(sf::Color(120, 190, 255));
    auto bounds = title.getLocalBounds();
    title.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    title.setPosition(width / 2.f, height * 0.18f);

    std::vector<std::string> labels = {
        "Nowa gra",
        "Wczytaj gre",
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
        text.setPosition(width / 2.f, height / 2.f + i * 70.f);

        items.push_back(text);
    }
}

void Menu::update(sf::Time dt)
{
    animTimer += dt.asSeconds();
    float scale = 1.f + 0.04f * std::sin(animTimer * 2.5f);
    title.setScale(scale, scale);

    for (size_t i = 0; i < stars.size(); ++i) {
        stars[i].move(starVel[i]);
        auto pos = stars[i].getPosition();
        auto bounds = stars[i].getGlobalBounds();
        float halfW = bounds.width * 0.5f;
        float halfH = bounds.height * 0.5f;
        if (pos.x < -halfW) pos.x = viewWidth;
        if (pos.x > viewWidth + halfW) pos.x = -halfW;
        if (pos.y < -halfH) pos.y = viewHeight;
        if (pos.y > viewHeight + halfH) pos.y = -halfH;
        stars[i].setPosition(pos);
    }
}

void Menu::draw(sf::RenderTarget& target)
{
    for (auto& star : stars)
        target.draw(star);
    target.draw(panel);
    target.draw(title);
    for (auto& item : items)
        target.draw(item);
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
