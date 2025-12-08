#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "brick.h"
#include "ball.h"
#include "paddle.h"
#include "gamestate.h"

class Game {
private:
    paletka m_paletka;
    pilka m_pilka;
    std::unique_ptr<pilka> m_pilka2;
    std::vector<Brick> m_bloki;
    bool przegrana = false;
    bool bonusApplied = false;
    int licznik_odbic = 0;
    const float basePaddleSpeed = 8.f;
    bool scoreRecorded = false;

    sf::Font font;
    sf::Text tekstPrzegrana;
    sf::Text tekstOdbicia;
    sf::Text tekstTabela;
    std::vector<sf::CircleShape> m_gwiazdki;
    std::vector<sf::Vector2f> m_gwiazdkiVel;
    float m_animTimer = 0.f;
    std::vector<int> m_scores;

public:
    Game(); 

    int run();
    void update(sf::Time dt); 
    void render(sf::RenderTarget& target); 
    bool saveState(const std::string& filename) const;
    bool loadState(const std::string& filename);
    void applyBonusIfNeeded();
    void restoreSecondBall(bool hasSecond, const sf::Vector2f& pos, const sf::Vector2f& vel);
    void recordScore();
    void loadScores();
    void saveScores() const;
    void updateScoreText();

    bool isGameOver() const { return przegrana; }
    void reset();
    int getOdbicia() const { return licznik_odbic; }
};
