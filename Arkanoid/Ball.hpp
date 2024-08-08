#include <SFML/Graphics.hpp>

class Ball
{
private:
    float _speedX, _speedY;
    sf::Texture *_tBall;
public:
    Ball();
    ~Ball();
    void addTexture(sf::Texture *tBall);
    void setTexture();
    void setSpeed(float x, float y);
    void changeSpeed(float x, float y);
    void move();
    void moveX();
    void moveY();
    void bounceX();
    void bounceY();
    void setSpeedX(float x);
    void setSpeedY(float y);
    sf::Sprite sprite;
};