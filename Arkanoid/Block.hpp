#include <SFML/Graphics.hpp>

class Block
{
private:
    std::vector<sf::Texture> *_tBlocks;
    int _durability;
public:
    Block(std::vector<sf::Texture> *tBlocks, int durability);
    ~Block();
    void setTexture();
    sf::Sprite sprite;
    
};