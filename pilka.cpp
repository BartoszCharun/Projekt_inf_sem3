#include "pilka.h"
#include "paletka.h"

pilka::pilka(float x, float y)
{
    shape.setRadius(10.f);
    shape.setFillColor(sf::Color(241, 196, 15));
    shape.setPosition(sf::Vector2f(x, y));
}

void pilka::update()
{
    shape.move(velocity);
}

void pilka::draw(sf::RenderTarget& target)
{
    target.draw(shape);
}

void pilka::bounceHorizontally()
{
    velocity.x = -velocity.x;
}

void pilka::bounceVertically()
{
    velocity.y = -velocity.y;
}

sf::FloatRect pilka::getBounds() const
{
    return shape.getGlobalBounds();
}

sf::Vector2f pilka::getPosition() const
{
    return shape.getPosition();
}

sf::Vector2f pilka::getVelocity() const
{
    return velocity;
}

void pilka::setVelocity(const sf::Vector2f& newVelocity)
{
    velocity = newVelocity;
}

void pilka::scaleVelocity(float factor)
{
    velocity.x *= factor;
    velocity.y *= factor;
}

void pilka::setPosition(float x, float y)
{
    shape.setPosition(sf::Vector2f(x, y));
}

bool pilka::handleWallCollision(float areaWidth, float areaHeight)
{
    auto bounds = getBounds();
    if (bounds.left <= 0.f || bounds.left + bounds.width >= areaWidth)
        bounceHorizontally();
    if (bounds.top <= 0.f)
        bounceVertically();

    return bounds.top + bounds.height >= areaHeight;
}

bool pilka::handlePaddleCollision(const paletka& paddle)
{
    auto ballBounds = getBounds();
    const auto paddleBounds = paddle.getBounds();
    if (!ballBounds.intersects(paddleBounds))
        return false;

    float overlapLeft = (ballBounds.left + ballBounds.width) - paddleBounds.left;
    float overlapRight = (paddleBounds.left + paddleBounds.width) - ballBounds.left;
    float overlapTop = (ballBounds.top + ballBounds.height) - paddleBounds.top;
    float overlapBottom = (paddleBounds.top + paddleBounds.height) - ballBounds.top;

    bool ballFromLeft = overlapLeft < overlapRight;
    bool ballFromTop = overlapTop < overlapBottom;
    float minOverlapX = ballFromLeft ? overlapLeft : overlapRight;
    float minOverlapY = ballFromTop ? overlapTop : overlapBottom;

    if (minOverlapX < minOverlapY) {
        bounceHorizontally();
        float adjust = ballFromLeft ? -minOverlapX : minOverlapX;
        setPosition(ballBounds.left + adjust, ballBounds.top);
    } else {
        bounceVertically();
        float adjust = ballFromTop ? -minOverlapY : minOverlapY;
        setPosition(ballBounds.left, ballBounds.top + adjust);
    }
    return true;
}

int pilka::handleBricksCollision(std::vector<Brick>& bricks)
{
    int hits = 0;
    auto ballBounds = getBounds();
    for (auto& blok : bricks) {
        if (blok.isDestroyed()) continue;
        if (ballBounds.intersects(blok.getBounds())) {
            blok.trafienie();
            if (hits == 0)
                bounceVertically();
            hits++;
        }
    }
    return hits;
}
