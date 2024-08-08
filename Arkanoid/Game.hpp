#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <vector>
#include <memory>

#include "Block.hpp"
#include "Ball.hpp"

const int BRICK_WIDTH = 40;
const int BRICK_HEIGHT = 20;
const int WIDTH = 500;
const int HEIGHT = 500;

static float const SCALE = 2;

const std::vector<std::vector<int>> BRICKS_MAP_HEART = {
    
    {0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
    {0, 1, 2, 2, 1, 1, 2, 2, 1, 0},
    {1, 2, 3, 3, 2, 2, 3, 3, 2, 1},
    {1, 2, 3, 4, 3, 3, 4, 3, 2, 1},
    {1, 2, 3, 4, 5, 5, 4, 3, 2, 1},
    {1, 2, 3, 4, 5, 5, 4, 3, 2, 1},
    {0, 1, 2, 3, 4, 4, 3, 2, 1, 0},
    {0, 0, 1, 2, 3, 3, 2, 1, 0, 0},
    {0, 0, 0, 1, 2, 2, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
};

class Game
{
private:
    bool paused = false;

    int _nBlocks = 0;
    std::vector<Block> _blocks;
    Ball _ball;

    std::unique_ptr<sf::RenderWindow> window;
    sf::Texture tBlock1, tBlock2, tBlock3, tBlock4, tBlock5, tBackground, tBall, tPaddle;
    std::vector<sf::Texture> tBlocks = {tBlock1, tBlock2, tBlock3, tBlock4, tBlock5};
    sf::Sprite sBackground, sPaddle;

    sf::SoundBuffer bWin, bLose, bHit, bBounce;
    sf::Sound sWin, sLose, sHit, sBounce;

public:
    Game();
    ~Game();
    void Init();
    void SoundInit();
    void Play();
    void End();
    void Pause();

    void paddleMove();

    void bounceWithEdge(Ball& ball);
    bool isCollide(Ball& ball, std::vector<Block>& blocks);

    bool isCollide(sf::Sprite s1, sf::Sprite s2);

    template <typename T1> 
    bool isCollide(T1 s1, sf::Sprite s2);

    template <typename T1, typename T2> 
    bool isCollide(T1 s1, T2 s2);
};




