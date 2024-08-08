#include "Ball.hpp"

Ball::Ball()
{
}

Ball::~Ball()
{
}

void Ball::addTexture(sf::Texture *tBall)
{
    _tBall = tBall;
}

void Ball::setTexture()
{
    sprite.setTexture(*_tBall);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

void Ball::setSpeed(float x, float y)
{
    _speedX = x;
    _speedY = y;
}

void Ball::changeSpeed(float x, float y)
{
    _speedX += x;
    _speedY += y;
}

void Ball::move()
{
    sprite.move(_speedX, _speedY);
}

void Ball::moveX()
{
    sprite.move(_speedX, 0);
}

void Ball::moveY()
{
    sprite.move(0, _speedY);
}

void Ball::bounceX()
{
    _speedX = -_speedX;
}

void Ball::bounceY()
{
    _speedY = -_speedY;
}

void Ball::setSpeedX(float x)
{
    _speedX = x;
}

void Ball::setSpeedY(float y)
{
    _speedY = y;
}
