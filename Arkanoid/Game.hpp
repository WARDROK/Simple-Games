#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
#include <memory>

#include "Block.hpp"
#include "Ball.hpp"

static float const SCALE = 3;


class Game
{
private:
    int _nBlocks = 0;
    std::vector<Block> _blocks;
    Ball _ball;

    std::unique_ptr<sf::RenderWindow> window;
    sf::Texture tBlock1, tBlock2, tBlock3, tBlock4, tBlock5, tBackground, tBall, tPaddle;
    std::vector<sf::Texture> tBlocks = {tBlock1, tBlock2, tBlock3, tBlock4, tBlock5};
    sf::Sprite sBackground, sPaddle;

public:
    Game();
    ~Game();
    void Init();
    void Play();
    void End();

    void paddleMove();

    void bounceWithEdge(Ball& ball);
    bool isCollide(Ball& ball, std::vector<Block>& blocks);

    bool isCollide(sf::Sprite s1, sf::Sprite s2);

    template <typename T1> 
    bool isCollide(T1 s1, sf::Sprite s2);

    template <typename T1, typename T2> 
    bool isCollide(T1 s1, T2 s2);
};




