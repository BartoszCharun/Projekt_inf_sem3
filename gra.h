#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "blok.h"
#include "pilka.h"
#include "paletka.h"
#include "stan_gry.h"
#include "bloki.h"
#include "gwiazdy.h"

class Game {
private:
    paletka m_paletka;
    pilka m_pilka;
    std::unique_ptr<pilka> m_pilka2;
    Bloki m_bloki;
    bool przegrana = false;
    bool bonusApplied = false;
    int licznik_odbic = 0;
    const float basePaddleSpeed = 8.f;
    bool scoreRecorded = false;

    sf::Font font;
    sf::Text tekstPrzegrana;
    sf::Text tekstOdbicia;
    sf::Text tekstTabela;
    float m_animTimer = 0.f;
    std::vector<int> m_scores;
    Starfield m_starfield;

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
