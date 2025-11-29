#include <SFML/Graphics.hpp>
#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <cmath>


Game::Game()
    : m_paletka(800 / 2.f - 50.f, 600 - 40.f), m_pilka(400.f, 300.f)
{
    // tworzenie bloków
    const int kolumny = 10, wiersze = 5;
    float rozmiarX = (800 / kolumny) - 5.f;
    float rozmiarY = 25.f;

    for(int i = 0; i < wiersze; i++)
        for(int j = 0; j < kolumny; j++) {
            float x = j * (rozmiarX + 5.f) + 2.5f;
            float y = i * (rozmiarY + 5.f) + 50.f;
            int zycie = (i == 0 ? 5 : (i < 3 ? 3 : (i == 3 ? 2 : 1)));
            m_bloki.emplace_back(sf::Vector2f(x, y), sf::Vector2f(rozmiarX, rozmiarY), zycie);
        }

    if (!font.loadFromFile("Arimo-Regular.ttf")) {
    
    }

    tekstPrzegrana.setFont(font);
    tekstPrzegrana.setString("Game over! Nacisnij R aby zrestartowac");
    tekstPrzegrana.setCharacterSize(30);
    tekstPrzegrana.setFillColor(sf::Color::White);
    auto przegranaBounds = tekstPrzegrana.getLocalBounds();
    tekstPrzegrana.setOrigin(przegranaBounds.width / 2.f, przegranaBounds.height / 2.f);
    tekstPrzegrana.setPosition(800.f / 2.f, 600.f / 2.f - 20.f);

    tekstOdbicia.setFont(font);
    tekstOdbicia.setCharacterSize(20);
    tekstOdbicia.setFillColor(sf::Color::White);
    tekstOdbicia.setPosition(10.f, 10.f);

 
    static bool seeded = false;
    if (!seeded) { std::srand(static_cast<unsigned>(std::time(nullptr))); seeded = true; }
    const int starCount = 120;
    m_gwiazdki.reserve(starCount);
    m_gwiazdkiVel.reserve(starCount);
    for (int i = 0; i < starCount; ++i) {
        float x = static_cast<float>(std::rand() % 800);
        float y = static_cast<float>(std::rand() % 600);
        float r = 1.f + static_cast<float>(std::rand() % 4) * 0.3f; // 1.0 - 2.2
        sf::CircleShape star(r);
        star.setFillColor(sf::Color(200, 220, 255, 200));
        star.setPosition(x, y);
        m_gwiazdki.push_back(star);
        float vx = (static_cast<float>(std::rand() % 11) - 5.f) * 0.03f; // -0.15..0.15
        float vy = (static_cast<float>(std::rand() % 11) - 5.f) * 0.03f;
        m_gwiazdkiVel.push_back({vx, vy});
    }
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

    auto ballControl = [&](pilka& ball) {
        auto ballBounds = ball.getBounds();

        // odbicie od ścian
        if(ballBounds.left <= 0.f || ballBounds.left + ballBounds.width >= 800.f)
            ball.bounceHorizontally();
        if(ballBounds.top <= 0.f)
            ball.bounceVertically();

        // odbicie od paletki
        if(ballBounds.intersects(m_paletka.getBounds())){
            ball.bounceVertically();
            licznik_odbic++;
        }

        // odbicie od bloków
        for(auto &blok : m_bloki) {
            if(blok.isDestroyed()) continue;
            if(ballBounds.intersects(blok.getBounds())) {
                blok.trafienie();
                ball.bounceVertically();
            }
        }

        // sprawdzanie przegranej
        if(ballBounds.top + ballBounds.height >= 600) {
            przegrana = true;
            ball.setVelocity({0.f, 0.f});
        }
    };

    ballControl(m_pilka);
    if (m_pilka2) ballControl(*m_pilka2);

    if (przegrana) {
        m_pilka.setPosition(800 / 2.f, 600 / 2.f);
        if (m_pilka2) m_pilka2->setPosition(800 / 2.f, 600 / 2.f);
    }

    applyBonusIfNeeded();
        
    tekstOdbicia.setString("Odbicia: " + std::to_string(licznik_odbic));
    float scale = 1.f + 0.05f * std::sin(m_animTimer * 3.f);
    tekstOdbicia.setScale(scale, scale);

    for (size_t i = 0; i < m_gwiazdki.size(); ++i) {
        m_gwiazdki[i].move(m_gwiazdkiVel[i]);
        auto pos = m_gwiazdki[i].getPosition();
        float r = m_gwiazdki[i].getRadius();
        if (pos.x < -r) pos.x = 800.f;
        if (pos.x > 800.f) pos.x = -r;
        if (pos.y < -r) pos.y = 600.f;
        if (pos.y > 600.f) pos.y = -r;
        m_gwiazdki[i].setPosition(pos);
    }

}

void Game::render(sf::RenderTarget& target)
{
    for (auto& star : m_gwiazdki)
        target.draw(star);
    m_paletka.draw(target);
    m_pilka.draw(target);
    if (m_pilka2) m_pilka2->draw(target);
    for(auto &blok : m_bloki) {
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
    licznik_odbic = 0;
    m_pilka.setPosition(400.f, 300.f);
    m_pilka.setVelocity({6.f, -6.f});
    m_pilka2.reset();
    m_paletka.setPosition(800 / 2.f - 50.f, 600 - 40.f);
    m_paletka.setSpeed(basePaddleSpeed);

    for(auto &blok : m_bloki)
        blok.reset(); 
}

bool Game::saveState(const std::string& filename) const
{
    Gamestate state(m_paletka, m_pilka, m_bloki, m_pilka2.get());
    return state.saveToFile(filename);
}

bool Game::loadState(const std::string& filename)
{
    bool hasSecondBall = false;
    sf::Vector2f pos2, vel2;
    bool loaded = Gamestate::loadFromFile(filename, m_paletka, m_pilka, m_bloki, hasSecondBall, pos2, vel2);
    if (loaded) {
        przegrana = false;
        licznik_odbic = 0;
        tekstOdbicia.setString("Odbicia: 0");
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
