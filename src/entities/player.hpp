#pragma once
#include <SFML/Graphics.hpp>

class Player
{
    public:
    float xVelocity = 2000.0f;
    float yVelocity = 2000.0f;
    sf::Sprite playerSprite;
    Player(sf::Texture& texture);
    void init(sf::Texture& texture);
};