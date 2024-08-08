#include "Game.hpp"
#include <iostream>

Game::Game()
{
    srand(time(nullptr));

    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(520*SCALE, 450*SCALE), "Arkanoid Game!");
    window->setFramerateLimit(60);

    // Blocks Textures
    tBlocks[0].loadFromFile("assets/Arkanoid/block01.png");
    tBlocks[1].loadFromFile("assets/Arkanoid/block02.png");
    tBlocks[2].loadFromFile("assets/Arkanoid/block03.png");
    tBlocks[3].loadFromFile("assets/Arkanoid/block04.png");
    tBlocks[4].loadFromFile("assets/Arkanoid/block05.png");
    

    // Other Textures
    tBackground.loadFromFile("assets/Arkanoid/background.jpg");
    tBall.loadFromFile("assets/Arkanoid/ball.png");
    tPaddle.loadFromFile("assets/Arkanoid/paddle.png");

    // Objects Sprites
    sBackground.setTexture(tBackground);
    sBall.setTexture(tBall);
    sPaddle.setTexture(tPaddle);


    // Set centers points and scale
    sPaddle.setOrigin(sPaddle.getLocalBounds().width / 2, sPaddle.getLocalBounds().height / 2);
    sPaddle.setPosition(260*SCALE, 440*SCALE);

    sBall.setOrigin(sBall.getLocalBounds().width / 2, sBall.getLocalBounds().height / 2);
    sBall.setPosition(260*SCALE, 300*SCALE);

    sBackground.setScale(SCALE, SCALE);
    sBall.setScale(SCALE, SCALE);
    sPaddle.setScale(SCALE, SCALE);;
}

Game::~Game()
{
}

void Game::Run()
{
    Blocks.clear();
    _blocks = 0;

    for(int i = 1; i <= 10; i++)
    {
        for(int j = 1; j <= 10; j++)
        {
            Blocks.push_back(Block(&tBlocks, 2));
            Blocks[_blocks].setTexture();
            Blocks[_blocks].sprite.setPosition(i*43*SCALE, j*20*SCALE);
            Blocks[_blocks].sprite.setScale(SCALE, SCALE);
            
            _blocks++;
        }
    }

    float dx = 0, dy=4*SCALE;

    sf::Event event;
    
    while(window->isOpen())
    {
        
        while(window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window->close();
            }
        }

        sBall.move(dx, 0);
        for(int i = 0; i < _blocks; i++)
        {
            if(isCollide(Blocks[i], sBall))
            {
                Blocks.erase(Blocks.begin() + i);
                _blocks--;
                dx = -dx;
            }
        }

        sBall.move(0, dy);
        for(int i = 0; i < _blocks; i++)
        {
            if(isCollide(Blocks[i], sBall))
            {
                Blocks.erase(Blocks.begin() + i);
                _blocks--;
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
        

        window->clear();
        window->draw(sBackground);
        window->draw(sBall);
        window->draw(sPaddle);

        for(int i = 0; i < _blocks; i++)
        {
            window->draw(Blocks[i].sprite);
        }

        window->display();
    }
}


bool Game::isCollide(sf::Sprite s1, sf::Sprite s2)
{
    return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}

template <typename T1> 
bool Game::isCollide(T1 s1, sf::Sprite s2)
{
    return s1.sprite.getGlobalBounds().intersects(s2.getGlobalBounds());
}

template <typename T1, typename T2> 
bool Game::isCollide(T1 s1, T2 s2)
{
    return s1.sprite.getGlobalBounds().intersects(s2.sprite.getGlobalBounds());
}