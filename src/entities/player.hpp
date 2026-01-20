#pragma once
#include <SFML/Graphics.hpp>

class Player
{
    public:
    float xVelocity = 0.2f;
    float yVelocity = 2000.0f;
    sf::Sprite playerSprite;
    Player(sf::Texture& texture);
};