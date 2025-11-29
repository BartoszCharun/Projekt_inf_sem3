#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Game.h"
#include "gamestate.h"
#include <iostream>


enum class GameState { Menu, Playing, Exiting };

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(window.getSize().x, window.getSize().y);
    Game game;

    GameState currentState = GameState::Menu;

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (currentState == GameState::Menu) {
                menu.handleEvent(event);

                // Enter w menu
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    if (menu.getSelectedItem() == 0) { // Nowa gra
                        game.reset();
                        currentState = GameState::Playing;
                    } else if (menu.getSelectedItem() == 1) { // Wczytaj gre
                        if (game.loadState("savedgame.txt"))
                            currentState = GameState::Playing;
                        else
                            std::cout << "Brak zapisu gry lub uszkodzony plik." << std::endl;
                    } else if (menu.getSelectedItem() == 2) { // Wyjście
                        window.close();
                    }
                }
            } else if (currentState == GameState::Playing) {
                // ESC kończy grę
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                    currentState = GameState::Menu;
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
                    game.saveState("savedgame.txt");
            }
        }

        sf::Time dt = clock.restart();

        // update
        if (currentState == GameState::Playing)
            game.update(dt);
        else if (currentState == GameState::Menu)
            menu.update(dt);

        // render
        window.clear(sf::Color::Black);

        if (currentState == GameState::Menu)
            menu.draw(window);
        else if (currentState == GameState::Playing)
            game.render(window);

        window.display();
    }

    return 0;
}
