#include "Game.hpp"
#include <iostream>

Game::Game()
{
    Init();
    while(window->isOpen())
    {
        Play();
    }

}

Game::~Game()
{
}

void Game::Init()
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

    // Background Init
    sBackground.setTexture(tBackground);
    sBackground.setScale(SCALE, SCALE);

    // Paddle Init
    sPaddle.setTexture(tPaddle);
    sPaddle.setOrigin(sPaddle.getLocalBounds().width / 2, sPaddle.getLocalBounds().height / 2);
    sPaddle.setPosition(260*SCALE, 440*SCALE);
    sPaddle.setScale(SCALE, SCALE);

    // Blocks Init
    _blocks.clear();
    _nBlocks = 0;

    for(int row = 1; row <= 10; row++)
    {
        for(int col = 1; col <= 10; col++)
        {
            _blocks.push_back(Block(&tBlocks, row%5+1));
            _blocks[_nBlocks].setTexture();
            _blocks[_nBlocks].sprite.setPosition(col*43*SCALE, row*20*SCALE);
            _blocks[_nBlocks].sprite.setScale(SCALE, SCALE);
            
            _nBlocks++;
        }
    }

    // Ball init
    _ball.addTexture(&tBall);
    _ball.setTexture();
    _ball.sprite.setPosition(260*SCALE, 300*SCALE);
    _ball.sprite.setScale(SCALE, SCALE);
    _ball.setSpeed(((rand()%31-15)/10.f)*SCALE, 4*SCALE);
    
}

void Game::Play()
{
    sf::Event event;

    while(window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window->close();
        }
    }
    
    // Check collision with edge
    bounceWithEdge(_ball);

    // Check collison with blocks
    _ball.moveX();
    if(isCollide(_ball, _blocks)) _ball.bounceX();

    _ball.moveY();
    if(isCollide(_ball, _blocks)) _ball.bounceY();
    
    // Check collision with paddle
    if(isCollide(_ball, sPaddle))
    {
        _ball.bounceY();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            _ball.setSpeedX((rand()%4-4)*SCALE);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            _ball.setSpeedX((rand()%4+1)*SCALE);
        }
    }

    paddleMove();

    window->clear();
    window->draw(sBackground);
    window->draw(_ball.sprite);
    window->draw(sPaddle);

    for(int i = 0; i < _nBlocks; i++)
    {
        window->draw(_blocks[i].sprite);
    }

    window->display();
}

void Game::End()
{
    window->close();
}

void Game::paddleMove()
{
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
}

void Game::bounceWithEdge(Ball &ball)
{
    sf::Vector2f b = ball.sprite.getPosition();
    if (b.x < 0 || b.x > 520*SCALE) ball.bounceX();
    if (b.y < 0 || b.y > 450*SCALE) ball.bounceY();

    if(ball.sprite.getPosition().y >= 450*SCALE)
    {
        End();
    }
}

bool Game::isCollide(Ball &ball, std::vector<Block> &blocks)
{
    bool collide = false;
    for(int i = 0; i < _nBlocks; i++)
    {
        if(isCollide(_blocks[i], _ball))
        {
            _blocks.erase(_blocks.begin() + i);
            _nBlocks--;
            collide = true;
        }
    }
    return collide;
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