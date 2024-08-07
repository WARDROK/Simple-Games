#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>

float const SCALE = 2;

bool isCollide(sf::Sprite s1, sf::Sprite s2)
{
    return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}

int main()
{
    srand(time(nullptr));

    sf::RenderWindow window(sf::VideoMode(520*SCALE, 450*SCALE), "Arkanoid Game!");
    window.setFramerateLimit(60);

    sf::Texture tBlock1, tBackground, tBall, tPaddle;
    tBlock1.loadFromFile("assets/Arkanoid/block01.png");
    tBackground.loadFromFile("assets/Arkanoid/background.jpg");
    tBall.loadFromFile("assets/Arkanoid/ball.png");
    tPaddle.loadFromFile("assets/Arkanoid/paddle.png");

    sf::Sprite sBackground(tBackground), sBall(tBall), sPaddle(tPaddle);
    sPaddle.setOrigin(sPaddle.getLocalBounds().width / 2, sPaddle.getLocalBounds().height / 2);
    sPaddle.setPosition(260*SCALE, 440*SCALE);

    sBall.setOrigin(sBall.getLocalBounds().width / 2, sBall.getLocalBounds().height / 2);
    sBall.setPosition(260*SCALE, 300*SCALE);

    sBackground.setScale(SCALE, SCALE);
    sBall.setScale(SCALE, SCALE);
    sPaddle.setScale(SCALE, SCALE);;

    sf::Sprite sBlock[1000];

    int n = 0;
    for(int i = 1; i <= 10; i++)
    {
        for(int j = 1; j <= 10; j++)
        {
            sBlock[n].setTexture(tBlock1);
            sBlock[n].setPosition(i*43*SCALE, j*20*SCALE);
            sBlock[n].setScale(SCALE, SCALE);
            
            n++;
        }
    }

    float dx = 0, dy=4*SCALE;

    sf::Event event;
    
    while(window.isOpen())
    {
        
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        sBall.move(dx, 0);
        for(int i = 0; i < n; i++)
        {
            if(isCollide(sBall, sBlock[i]))
            {
                sBlock[i].setPosition(-100, 0);
                dx = -dx;
            }
        }

        sBall.move(0, dy);
        for(int i = 0; i < n; i++)
        {
            if(isCollide(sBall, sBlock[i]))
            {
                sBlock[i].setPosition(-100, 0);
                dy = -dy;
            }
        }

        sf::Vector2f b = sBall.getPosition();
        if (b.x < 0 || b.x > 520*SCALE) dx = -dx;
        if (b.y < 0 || b.y > 450*SCALE) dy = -dy;

        if(sBall.getPosition().y >= 450*SCALE) break;

        if(isCollide(sPaddle, sBall))
        {
            dy = -dy;
            dx = (rand()%8-4)*SCALE;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            sPaddle.move(-6*SCALE, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            sPaddle.move(6*SCALE, 0);
        }

        sf::Vector2f p = sPaddle.getPosition();
        if (p.x < 0*SCALE) sPaddle.move(6*SCALE, 0);
        if (p.x > 520*SCALE) sPaddle.move(-6*SCALE, 0);
        

        window.clear();
        window.draw(sBackground);
        window.draw(sBall);
        window.draw(sPaddle);

        for(int i = 0; i < n; i++)
        {
            window.draw(sBlock[i]);
        }

        window.display();
    }

    return 0;
}