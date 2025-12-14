#include <SFML/Graphics.hpp>
#include "gra.h"
#include "Menu.h"
#include "Napisy.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <functional>
#include <iostream>

namespace {
const float GAME_WIDTH = 800.f;
const float GAME_HEIGHT = 600.f;
}


Game::Game()
    : m_paletka(GAME_WIDTH / 2.f - 50.f, GAME_HEIGHT - 40.f), m_pilka(400.f, 300.f)
{
    m_bloki.generateDefault(GAME_WIDTH);

    if (!font.loadFromFile(Napisy::Pliki::font())) {
    
    }

    tekstPrzegrana.setFont(font);
    tekstPrzegrana.setString(Napisy::Gra::gameOver());
    tekstPrzegrana.setCharacterSize(30);
    tekstPrzegrana.setFillColor(sf::Color::White);
    auto przegranaBounds = tekstPrzegrana.getLocalBounds();
    tekstPrzegrana.setOrigin(przegranaBounds.width / 2.f, przegranaBounds.height / 2.f);
    tekstPrzegrana.setPosition(GAME_WIDTH / 2.f, GAME_HEIGHT / 2.f - 20.f);

    tekstOdbicia.setFont(font);
    tekstOdbicia.setCharacterSize(20);
    tekstOdbicia.setFillColor(sf::Color::White);
    tekstOdbicia.setPosition(10.f, 10.f);

    tekstTabela.setFont(font);
    tekstTabela.setCharacterSize(22);
    tekstTabela.setFillColor(sf::Color(200, 220, 255));
    loadScores();
    updateScoreText();
 
    m_starfield.init(120, GAME_WIDTH, GAME_HEIGHT);
}

int Game::run()
{
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(GAME_WIDTH),
                                          static_cast<unsigned int>(GAME_HEIGHT)), Napisy::Gra::windowTitle());
    window.setFramerateLimit(60);

    Menu menu(window.getSize().x, window.getSize().y);

    enum class State { Menu, Playing, Scores };
    State currentState = State::Menu;

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                continue;
            }

            if (currentState == State::Menu) {
                menu.handleEvent(event);

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    if (menu.getSelectedItem() == 0) { 
                        reset();
                        currentState = State::Playing;
                    } else if (menu.getSelectedItem() == 1) { // Wczytaj gre
                        if (loadState(Napisy::Pliki::save()))
                            currentState = State::Playing;
                        else
                            std::cout << Napisy::Gra::loadSaveError() << std::endl;
                    } else if (menu.getSelectedItem() == 2) { // Tabela wynikow
                        menu.refreshScores();
                        currentState = State::Scores;
                    } else if (menu.getSelectedItem() == 3) { // Wyjscie
                        window.close();
                    }
                }
            } else if (currentState == State::Playing) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                    currentState = State::Menu;
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
                    saveState(Napisy::Pliki::save());
            } else if (currentState == State::Scores) {
                if (event.type == sf::Event::KeyPressed &&
                    (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter)) {
                    currentState = State::Menu;
                }
            }
        }

        sf::Time dt = clock.restart();

        if (currentState == State::Playing)
            update(dt);
        else if (currentState == State::Menu || currentState == State::Scores)
            menu.update(dt);

        window.clear(sf::Color::Black);

        if (currentState == State::Menu)
            menu.draw(window);
        else if (currentState == State::Playing)
            render(window);
        else if (currentState == State::Scores)
            menu.drawScores(window);

        window.display();
    }

    return 0;
}


void Game::update(sf::Time dt)
{
    m_animTimer += dt.asSeconds();

 
    if (przegrana) {
        float loseScale = 1.f + 0.04f * std::sin(m_animTimer * 2.5f);
        tekstPrzegrana.setScale(loseScale, loseScale);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            reset();
        return;
    }

    m_paletka.update();
    m_pilka.update();
    if (m_pilka2) m_pilka2->update();

    auto processBall = [&](pilka& ball) {
        bool lost = ball.handleWallCollision(GAME_WIDTH, GAME_HEIGHT);
        if (ball.handlePaddleCollision(m_paletka))
            licznik_odbic++;
        ball.handleBricksCollision(m_bloki.getBricks());

        if (lost) {
            przegrana = true;
            ball.setVelocity({0.f, 0.f});
            recordScore();
        }
    };

    processBall(m_pilka);
    if (m_pilka2) processBall(*m_pilka2);

    if (przegrana) {
        m_pilka.setPosition(GAME_WIDTH / 2.f, GAME_HEIGHT / 2.f);
        if (m_pilka2) m_pilka2->setPosition(GAME_WIDTH / 2.f, GAME_HEIGHT / 2.f);
    }

    applyBonusIfNeeded();
        
    tekstOdbicia.setString(Napisy::Gra::hitsLabel(licznik_odbic));
    float scale = 1.f + 0.05f * std::sin(m_animTimer * 3.f);
    tekstOdbicia.setScale(scale, scale);

    m_starfield.update();

}

void Game::render(sf::RenderTarget& target)
{
    m_starfield.draw(target);
    m_paletka.draw(target);
    m_pilka.draw(target);
    if (m_pilka2) m_pilka2->draw(target);
    for(auto &blok : m_bloki.getBricks()) {
        blok.draw(target);
    }
    target.draw(tekstOdbicia);

    if (przegrana)
        target.draw(tekstPrzegrana);

}

void Game::reset()
{
    przegrana = false;
    bonusApplied = false;
    scoreRecorded = false;
    licznik_odbic = 0;
    m_pilka.setPosition(400.f, 300.f);
    m_pilka.setVelocity({6.f, -6.f});
    m_pilka2.reset();
    m_paletka.setPosition(GAME_WIDTH / 2.f - 50.f, GAME_HEIGHT - 40.f);
    m_paletka.setSpeed(basePaddleSpeed);

    m_bloki.reset(); 
}

bool Game::saveState(const std::string& filename) const
{
    Gamestate state(m_paletka, m_pilka, m_bloki.getBricks(), m_pilka2.get());
    return state.saveToFile(filename);
}

bool Game::loadState(const std::string& filename)
{
    bool hasSecondBall = false;
    sf::Vector2f pos2, vel2;
    bool loaded = Gamestate::loadFromFile(filename, m_paletka, m_pilka, m_bloki.getBricks(), hasSecondBall, pos2, vel2);
    if (loaded) {
        przegrana = false;
        scoreRecorded = false;
        licznik_odbic = 0;
        tekstOdbicia.setString(Napisy::Gra::hitsLabel(0));
        bonusApplied = hasSecondBall;
        m_paletka.setSpeed(basePaddleSpeed * (hasSecondBall ? 1.2f : 1.f));
        restoreSecondBall(hasSecondBall, pos2, vel2);
    }
    return loaded;
}

void Game::applyBonusIfNeeded()
{
    if (bonusApplied || licznik_odbic < 5) return;
    bonusApplied = true;
    m_paletka.setSpeed(m_paletka.getSpeed() * 1.2f);
    auto slowDown = [](pilka& b) {
        b.scaleVelocity(0.7f);
    };

    slowDown(m_pilka);
    if (m_pilka2) slowDown(*m_pilka2);

 
    sf::Vector2f pos(400.f, 300.f);
    sf::Vector2f baseVel = m_pilka.getVelocity();
  
    if (std::abs(baseVel.x) < 0.01f && std::abs(baseVel.y) < 0.01f)
        baseVel = {4.2f, -4.2f};

    m_pilka2 = std::make_unique<pilka>(pos.x, pos.y);
    m_pilka2->setVelocity(sf::Vector2f(-baseVel.x, baseVel.y));
    slowDown(*m_pilka2);
}

void Game::restoreSecondBall(bool hasSecond, const sf::Vector2f& pos, const sf::Vector2f& vel)
{
    if (!hasSecond) {
        m_pilka2.reset();
        return;
    }
    m_pilka2 = std::make_unique<pilka>(pos.x, pos.y);
    m_pilka2->setVelocity(vel);
}

void Game::loadScores()
{
    m_scores.clear();
    std::ifstream file(Napisy::Pliki::score());
    if (!file.is_open()) return;

    int value = 0;
    while (file >> value) {
        m_scores.push_back(value);
    }
    std::sort(m_scores.begin(), m_scores.end(), std::greater<int>());
    if (m_scores.size() > 5) m_scores.resize(5);
}

void Game::saveScores() const
{
    std::ofstream file(Napisy::Pliki::score());
    if (!file.is_open()) return;

    size_t limit = std::min<size_t>(5, m_scores.size());
    for (size_t i = 0; i < limit; ++i)
        file << m_scores[i] << "\n";
}

void Game::updateScoreText()
{
    std::string text = std::string(Napisy::Menu::scoresTitle()) + "\n";
    if (m_scores.empty()) {
        text += std::string(Napisy::Gra::emptyScorePlaceholder()) + "\n";
    } else {
        for (size_t i = 0; i < m_scores.size() && i < 5; ++i) {
            text += Napisy::Gra::scoreEntry(static_cast<int>(i + 1), m_scores[i]) + "\n";
        }
    }
    tekstTabela.setString(text);
    auto b = tekstTabela.getLocalBounds();
    tekstTabela.setOrigin(b.width / 2.f, 0.f);
    tekstTabela.setPosition(GAME_WIDTH / 2.f, GAME_HEIGHT / 2.f + 40.f);
}

void Game::recordScore()
{
    if (scoreRecorded) return;
    scoreRecorded = true;
    m_scores.push_back(licznik_odbic);
    std::sort(m_scores.begin(), m_scores.end(), std::greater<int>());
    if (m_scores.size() > 5) m_scores.resize(5);
    saveScores();
    updateScoreText();
}
