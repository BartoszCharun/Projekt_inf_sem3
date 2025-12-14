#include "Napisy.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace {
const std::vector<std::string> MENU_OPTIONS = {
    "Nowa gra",
    "Wczytaj gre",
    "Tabela wynikow",
    "Wyjscie"
};
}

const char* Napisy::Pliki::font()
{
    return "Arimo-Regular.ttf";
}

const char* Napisy::Pliki::score()
{
    return "scores.txt";
}

const char* Napisy::Pliki::save()
{
    return "savedgame.txt";
}

const char* Napisy::Menu::title()
{
    return "ARKANOID";
}

const std::vector<std::string>& Napisy::Menu::options()
{
    return MENU_OPTIONS;
}

const char* Napisy::Menu::scoresTitle()
{
    return "Tabela wynikow";
}

const char* Napisy::Menu::noScoresLabel()
{
    return "Brak wynikow";
}

void Napisy::Menu::initLayout(const sf::Font& font, sf::RectangleShape& panel, sf::Text& title,
                              float width, float height)
{
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
}

std::vector<sf::Text> Napisy::Menu::createMenuItems(const sf::Font& font, float width, float height)
{
    std::vector<sf::Text> items;
    const auto& labels = options();
    items.reserve(labels.size());

    for (size_t i = 0; i < labels.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(labels[i]);
        text.setCharacterSize(36);
        text.setFillColor(i == 0 ? sf::Color(120, 190, 255) : sf::Color(230, 230, 235));

        auto b = text.getLocalBounds();
        text.setOrigin(b.width / 2.f, b.height / 2.f);
        text.setPosition(width / 2.f, height * 0.45f + static_cast<float>(i) * 65.f);

        items.push_back(text);
    }

    return items;
}

std::vector<sf::Text> Napisy::Menu::createScoreTexts(const sf::Font& font, const std::vector<int>& scores,
                                                     float viewWidth, float viewHeight, sf::Text& scoreTitle)
{
    std::vector<sf::Text> scoreTexts;
    scoreTexts.reserve(scores.empty() ? 1 : scores.size());

    scoreTitle.setString(scoresTitle());
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
        line.setString(noScoresLabel());
        auto lb = line.getLocalBounds();
        line.setOrigin(lb.width / 2.f, lb.height / 2.f);
        line.setPosition(viewWidth / 2.f, startY);
        scoreTexts.push_back(line);
        return scoreTexts;
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

    return scoreTexts;
}

const char* Napisy::Gra::windowTitle()
{
    return "Arkanoid";
}

const char* Napisy::Gra::gameOver()
{
    return "Game over! Nacisnij R aby zrestartowac";
}

const char* Napisy::Gra::loadSaveError()
{
    return "Brak zapisu gry lub uszkodzony plik.";
}

std::string Napisy::Gra::hitsLabel(int count)
{
    return "Odbicia: " + std::to_string(count);
}

std::string Napisy::Gra::scoreEntry(int position, int score)
{
    return std::to_string(position) + ". " + std::to_string(score) + " odbic";
}

const char* Napisy::Gra::emptyScorePlaceholder()
{
    return "-";
}

void Napisy::Gra::initTexts(const sf::Font& font, sf::Text& tekstPrzegrana, sf::Text& tekstOdbicia,
                            sf::Text& tekstTabela, float gameWidth, float gameHeight)
{
    tekstPrzegrana.setFont(font);
    tekstPrzegrana.setString(gameOver());
    tekstPrzegrana.setCharacterSize(30);
    tekstPrzegrana.setFillColor(sf::Color::White);
    auto przegranaBounds = tekstPrzegrana.getLocalBounds();
    tekstPrzegrana.setOrigin(przegranaBounds.width / 2.f, przegranaBounds.height / 2.f);
    tekstPrzegrana.setPosition(gameWidth / 2.f, gameHeight / 2.f - 20.f);

    tekstOdbicia.setFont(font);
    tekstOdbicia.setCharacterSize(20);
    tekstOdbicia.setFillColor(sf::Color::White);
    tekstOdbicia.setPosition(10.f, 10.f);

    tekstTabela.setFont(font);
    tekstTabela.setCharacterSize(22);
    tekstTabela.setFillColor(sf::Color(200, 220, 255));
}
