#include <SFML/Graphics.hpp>

class Block
{
private:
    std::vector<sf::Texture> *_tBlocks;
    int _durability;
    bool _destroyed = false;

public:
    Block(std::vector<sf::Texture> *tBlocks, int durability);
    ~Block();
    void setTexture();
    void hit();
    bool isDestroyed() {return _destroyed;};
    sf::Sprite sprite;
};