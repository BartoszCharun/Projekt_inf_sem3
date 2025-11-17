#include <SFML/Graphics.hpp>
#include <vector>
#include "paddle.h"
#include "ball.h"
#include "brick.h"


bool checkCollision(const sf::FloatRect &a, const sf::FloatRect &b) {
    return (a.position.x < b.position.x + b.size.x &&
            a.position.x + a.size.x > b.position.x &&
            a.position.y < b.position.y + b.size.y &&
            a.position.y + a.size.y > b.position.y);
}

int main() {
    const int szerokoscOkna = 800;
    const int wysokoscOkna = 600;
    sf::RenderWindow window(sf::VideoMode({szerokoscOkna, wysokoscOkna}), "Breakout");
    window.setFramerateLimit(60);

    Paletka paletka(szerokoscOkna / 2.f - 50.f, wysokoscOkna - 40.f);
    Pilka pilka(szerokoscOkna / 2.f, wysokoscOkna / 2.f);

    std::vector<Brick> bloki;
    const int kolumny = 10, wiersze = 5;
    float rozmiarX = (szerokoscOkna / kolumny) - 5.f;
    float rozmiarY = 25.f;

    for(int i = 0; i < wiersze; i++)
        for(int j = 0; j < kolumny; j++) {
            float x = j * (rozmiarX + 5.f) + 2.5f;
            float y = i * (rozmiarY + 5.f) + 50.f;
            int zycie = (i == 0 ? 4 : (i < 3 ? 3 : (i == 3 ? 2 : 1)));
            bloki.emplace_back(sf::Vector2f(x, y), sf::Vector2f(rozmiarX, rozmiarY), zycie);
        }

    bool przegrana = false;

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
    


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) paletka.moveLeft();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) paletka.moveRight();
        if(przegrana && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
            przegrana = false;
            pilka.setPosition(szerokoscOkna / 2.f, wysokoscOkna / 2.f);
        }

        paletka.update();
        pilka.update();

        auto ballBounds = pilka.getBounds();

        // Odb sc
        if(ballBounds.position.x <= 0 || ballBounds.position.x + ballBounds.size.x >= szerokoscOkna)
            pilka.bounceHorizontally();

        if(ballBounds.position.y <= 0)
            pilka.bounceVertically();

        // Odb pal
        if(checkCollision(ballBounds, paletka.getBounds()))
            pilka.bounceVertically();

        // Odb blok
        for(auto &blok : bloki) {
            if(blok.isDestroyed()) continue;
            if(checkCollision(ballBounds, blok.getBounds())) {
                blok.trafienie();
                blok.aktualizujkolor();
                pilka.bounceVertically();
            }
        }


        if(ballBounds.position.y + ballBounds.size.y >= wysokoscOkna)
            przegrana = true;

        if(przegrana)
            pilka.setPosition(szerokoscOkna / 2.f, wysokoscOkna / 2.f);

      
        window.clear(sf::Color::White);
        paletka.draw(window);
        pilka.draw(window);
        for(auto &blok : bloki)
            blok.draw(window); 
        window.display();
    }

    return 0;
}
