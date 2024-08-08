#include "Block.hpp"

Block::Block(std::vector<sf::Texture> *tBlocks, int durability) : _tBlocks(tBlocks), _durability(durability)
{
}

Block::~Block()
{
}

void Block::setTexture()
{
    sprite.setTexture((*_tBlocks)[_durability - 1]);
}

void Block::hit()
{
    _durability--;
    if(_durability > 0)
    {
        sprite.setTexture((*_tBlocks)[_durability - 1]);
    }
    else
    {
        _destroyed = true;
    }
}
