#include "keyboardInput.hpp"
#include "../logic/collision.hpp"
#include "../globals.hpp"
#include <iostream>

void processKeyboardInput ()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape))
            window.close();

        player.playerSprite.move({0.0f, gravity * dt.asSeconds()});
        if (isBotEntityCollidingMap(player, level.data())) {
            player.playerSprite.move({-0.0f, -gravity * dt.asSeconds()});
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space)) {
            player.playerSprite.move({0.f, -player.yVelocity * dt.asSeconds()});
            if (isTopEntityCollidingMap(player, level.data())) {
                player.playerSprite.move({0.f, player.yVelocity * dt.asSeconds()});
            }
        } 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
            player.playerSprite.move({-.2f, 0.f});
            if (isLeftEntityCollidingMap(player, level.data())) {
                player.playerSprite.move({.2f, 0.f});
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
            player.playerSprite.move({.2f, 0.f});
            if (isRightEntityCollidingMap(player, level.data())) {
                player.playerSprite.move({-.2f, 0.f});
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Q)) {
            std::cout << &player << "\n";
            //std::cout << player.playerSprite.getPosition().x << "\n";
        }
}