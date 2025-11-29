#include "gamestate.h"
#include <fstream>

Gamestate::Gamestate(const paletka& paddle,
                     const pilka& ball,
                     const std::vector<Brick>& bricksList,
                     const pilka* secondBall)
{
    paddlePosition = paddle.getPosition();
    ballPosition = ball.getPosition();
    ballVelocity = ball.getVelocity();
    if (secondBall) {
        secondBallPresent = true;
        ball2Position = secondBall->getPosition();
        ball2Velocity = secondBall->getVelocity();
    }
    bricks.reserve(bricksList.size());
    for (const auto& block : bricksList) {
        bricks.push_back({block.getPosition(), block.getHP(), block.isDestroyed()});
    }
}

bool Gamestate::saveToFile(const std::string& savedgame) const
{
    std::ofstream file(savedgame);
    if (!file.is_open()) return false;

    // Paletka
    file << paddlePosition.x << " " << paddlePosition.y << "\n";

    // Piłka
    file << ballPosition.x << " " << ballPosition.y << " "
         << ballVelocity.x << " " << ballVelocity.y << "\n";
    // Druga piłka
    file << secondBallPresent << "\n";
    if (secondBallPresent) {
        file << ball2Position.x << " " << ball2Position.y << " "
             << ball2Velocity.x << " " << ball2Velocity.y << "\n";
    }

    // Bloki
    file << bricks.size() << "\n";
    for (const auto& block : bricks) {
        file << block.position.x << " " << block.position.y << " "
             << block.hp << " " << block.destroyed << "\n";
    }


    file.close();
    return true;
}

bool Gamestate::loadFromFile(const std::string& savedgame,
                             paletka& paddle,
                             pilka& ball,
                             std::vector<Brick>& bricksList,
                             bool& hasSecondBall,
                             sf::Vector2f& secondPos,
                             sf::Vector2f& secondVel)
{
    std::ifstream file(savedgame);
    if (!file.is_open()) return false;

    sf::Vector2f paddlePos;
    sf::Vector2f ballPos;
    sf::Vector2f ballVel;
    hasSecondBall = false;
    secondPos = {};
    secondVel = {};

    if (!(file >> paddlePos.x >> paddlePos.y)) return false;
    if (!(file >> ballPos.x >> ballPos.y >> ballVel.x >> ballVel.y)) return false;
    int secondFlag = 0;
    if (!(file >> secondFlag)) return false;
    hasSecondBall = (secondFlag != 0);
    if (hasSecondBall) {
        if (!(file >> secondPos.x >> secondPos.y >> secondVel.x >> secondVel.y)) return false;
    }

    size_t brickCount = 0;
    if (!(file >> brickCount)) return false;
    if (brickCount != bricksList.size()) return false;

    for (size_t i = 0; i < brickCount; ++i) {
        float x = 0.f, y = 0.f;
        int hp = 0;
        bool destroyed = false;
        if (!(file >> x >> y >> hp >> destroyed)) return false;
        bricksList[i].setState({x, y}, hp, destroyed);
    }

    paddle.setPosition(paddlePos.x, paddlePos.y);
    ball.setPosition(ballPos.x, ballPos.y);
    ball.setVelocity(ballVel);
    return true;
}
