#include "player.hpp"

Player::Player(sf::Texture& texture) : playerSprite(texture) 
{
}

void Player::init(sf::Texture& texture)
{
    playerSprite.setTexture(texture, true);
}