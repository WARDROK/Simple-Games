#include "Game.hpp"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Run()
{
    Init();

    _menu = std::make_unique<MainMenu>(window);
    _menu->Init();

    while(window->isOpen())
    {
        Play();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            Pause();
            _sleep(100);
        }
    }
}

void Game::Init()
{
    srand(time(nullptr));

    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(WIDTH*SCALE, HEIGHT*SCALE), "Arkanoid Game!", sf::Style::Close);
    window->setFramerateLimit(60);

    // Blocks Textures
    tBlocks[0].loadFromFile("assets/Arkanoid/block1.png");
    tBlocks[1].loadFromFile("assets/Arkanoid/block2.png");
    tBlocks[2].loadFromFile("assets/Arkanoid/block3.png");
    tBlocks[3].loadFromFile("assets/Arkanoid/block4.png");
    tBlocks[4].loadFromFile("assets/Arkanoid/block5.png");
    

    // Other Textures
    tBackground.loadFromFile("assets/Arkanoid/background.png");
    tBall.loadFromFile("assets/Arkanoid/ball.png");
    tPaddle.loadFromFile("assets/Arkanoid/paddle.png");

    // Background Init
    sBackground.setTexture(tBackground);
    sBackground.setScale(SCALE, SCALE);

    // Paddle Init
    sPaddle.setTexture(tPaddle);
    sPaddle.setOrigin(sPaddle.getLocalBounds().width / 2, sPaddle.getLocalBounds().height / 2);
    sPaddle.setPosition(WIDTH/2*SCALE, (HEIGHT-30)*SCALE);
    sPaddle.setScale(SCALE, SCALE);

    // Blocks Init
    _blocks.clear();
    _nBlocks = 0;

    for (int row = 1; row <= BRICKS_MAP_HEART.size(); row++)
    {
        for (int col = 1; col <= BRICKS_MAP_HEART[0].size(); col++)
        {
            
            if(BRICKS_MAP_HEART[row-1][col-1] != 0)
            {
                _blocks.push_back(Block(&tBlocks, BRICKS_MAP_HEART[row-1][col-1]));
                _blocks[_nBlocks].setTexture();
                _blocks[_nBlocks].sprite.setPosition(col*42*SCALE, row*22*SCALE + 22*SCALE);
                _blocks[_nBlocks].sprite.setScale(SCALE/2, SCALE/2);
                
                _nBlocks++;
            }
        }
    }

    // Ball init
    _ball.addTexture(&tBall);
    _ball.setTexture();
    _ball.sprite.setPosition(WIDTH/2*SCALE, (HEIGHT-200)*SCALE);
    _ball.sprite.setScale(SCALE/2, SCALE/2);
    _ball.setSpeed(((rand()%31-15)/10.f)*SCALE, 4*SCALE);
    

    SoundInit();
}

void Game::SoundInit()
{
    bWin.loadFromFile("assets/Arkanoid/win.wav");
    bLose.loadFromFile("assets/Arkanoid/lose.wav");
    bHit.loadFromFile("assets/Arkanoid/hit.wav");
    bBounce.loadFromFile("assets/Arkanoid/bounce.wav");
    sWin.setBuffer(bWin);
    sLose.setBuffer(bLose);
    sHit.setBuffer(bHit);
    sBounce.setBuffer(bBounce);
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
    
    if(!paused)
    {
        // Check collision with edge
        bounceWithEdge(_ball);

        // Check collison with blocks
        _ball.moveX();
        if(isCollide(_ball, _blocks)) 
        {
            _ball.bounceX();
            _ball.moveX();
        }

        _ball.moveY();
        if(isCollide(_ball, _blocks))
        {
            _ball.bounceY();
            _ball.moveY();
        }

        // Check collision with paddle
        if(isCollide(_ball, sPaddle))
        {
            sBounce.play();
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

    if(_nBlocks == 0)
    {
        sWin.play();
        End();
    }
}

void Game::End()
{
    _sleep(3000);
    window->close();
    Run();
    
}

void Game::Pause()
{
    paused = !paused;
}

void Game::paddleMove()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        sPaddle.move(-5*SCALE, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        sPaddle.move(5*SCALE, 0);
    }

    sf::Vector2f p = sPaddle.getPosition();
    if (p.x < 60*SCALE) sPaddle.move(5*SCALE, 0);
    if (p.x > (WIDTH-60)*SCALE) sPaddle.move(-5*SCALE, 0);
}

void Game::bounceWithEdge(Ball &ball)
{
    sf::Vector2f b = ball.sprite.getPosition();
    if (b.x < 23*SCALE || b.x > (WIDTH-23)*SCALE)
    {
        sBounce.play();
        ball.bounceX();
    }
    if (b.y < 23*SCALE)
    {
        sBounce.play();
        ball.bounceY();
    }

    if(ball.sprite.getPosition().y >= (HEIGHT-10)*SCALE)
    {
        sLose.play();
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
            sHit.play();
            _blocks[i].hit();
            if(_blocks[i].isDestroyed())
            {
                _blocks.erase(_blocks.begin() + i);
                _nBlocks--;
            }
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