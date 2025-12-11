#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "blok.h"
#include "paletka.h"
#include "pilka.h"

class Gamestate {
private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    bool secondBallPresent = false;
    sf::Vector2f ball2Position;
    sf::Vector2f ball2Velocity;
    struct BrickState {
        sf::Vector2f position;
        int hp;
        bool destroyed;
    };
    std::vector<BrickState> bricks;

public:
    Gamestate(const paletka& paddle,
              const pilka& ball,
              const std::vector<Brick>& bricksList,
              const pilka* secondBall = nullptr);

    bool saveToFile(const std::string& filename) const;
    static bool loadFromFile(const std::string& filename,
                             paletka& paddle,
                             pilka& ball,
                             std::vector<Brick>& bricksList,
                             bool& hasSecondBall,
                             sf::Vector2f& secondPos,
                             sf::Vector2f& secondVel);
};
