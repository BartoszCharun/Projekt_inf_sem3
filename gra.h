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
<<<<<<< HEAD:Game.h
<<<<<<< HEAD
    bool scoreRecorded = false;
=======
>>>>>>> 62e84fae8dc45d5e8d4eb90a1818b6b6ab4340ba
=======
    bool scoreRecorded = false;
>>>>>>> d1fffdb418111654297beb545fc433367a96616c:gra.h

    sf::Font font;
    sf::Text tekstPrzegrana;
    sf::Text tekstOdbicia;
<<<<<<< HEAD:Game.h
<<<<<<< HEAD
    sf::Text tekstTabela;
    std::vector<sf::CircleShape> m_gwiazdki;
    std::vector<sf::Vector2f> m_gwiazdkiVel;
    float m_animTimer = 0.f;
    std::vector<int> m_scores;
=======
    std::vector<sf::CircleShape> m_gwiazdki;
    std::vector<sf::Vector2f> m_gwiazdkiVel;
    float m_animTimer = 0.f;
>>>>>>> 62e84fae8dc45d5e8d4eb90a1818b6b6ab4340ba
=======
    sf::Text tekstTabela;
    float m_animTimer = 0.f;
    std::vector<int> m_scores;
    Starfield m_starfield;
>>>>>>> d1fffdb418111654297beb545fc433367a96616c:gra.h

public:
    Game(); 

<<<<<<< HEAD:Game.h
<<<<<<< HEAD
    int run();
=======
>>>>>>> 62e84fae8dc45d5e8d4eb90a1818b6b6ab4340ba
=======
    int run();
>>>>>>> d1fffdb418111654297beb545fc433367a96616c:gra.h
    void update(sf::Time dt); 
    void render(sf::RenderTarget& target); 
    bool saveState(const std::string& filename) const;
    bool loadState(const std::string& filename);
    void applyBonusIfNeeded();
    void restoreSecondBall(bool hasSecond, const sf::Vector2f& pos, const sf::Vector2f& vel);
<<<<<<< HEAD:Game.h
<<<<<<< HEAD
=======
>>>>>>> d1fffdb418111654297beb545fc433367a96616c:gra.h
    void recordScore();
    void loadScores();
    void saveScores() const;
    void updateScoreText();
<<<<<<< HEAD:Game.h
=======
>>>>>>> 62e84fae8dc45d5e8d4eb90a1818b6b6ab4340ba
=======
>>>>>>> d1fffdb418111654297beb545fc433367a96616c:gra.h

    bool isGameOver() const { return przegrana; }
    void reset();
    int getOdbicia() const { return licznik_odbic; }
};
