#include "keyboardInput.hpp"
#include "../logic/collision.hpp"
#include "../globals.hpp"
#include <iostream>
#include <cmath>

void processKeyboardInput()
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
            player.playerSprite.move({-player.xVelocity * dt.asSeconds(), 0.f});
            if (isLeftEntityCollidingMap(player, level.data())) {
                player.playerSprite.move({player.xVelocity * dt.asSeconds(), 0.f});
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
            player.playerSprite.move({player.xVelocity * dt.asSeconds(), 0.f});
            if (isRightEntityCollidingMap(player, level.data())) {
                player.playerSprite.move({-player.xVelocity * dt.asSeconds(), 0.f});
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Q)) {
            camera.zoom(1.05f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::E)) {
            camera.zoom(1/1.05f);
        }
}

void processMouseInput()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        int xOffset = window.getSize().x/2 - localPosition.x;
        int yOffset = window.getSize().y/2 - localPosition.y;
        float xZoom = window.getSize().x / camera.getSize().x;
        float yZoom = window.getSize().y / camera.getSize().y;
        int targetTileX = (camera.getCenter().x - xOffset/xZoom)/180;
        int targetTileY = (camera.getCenter().y - yOffset/yZoom)/180;

        int *tiles = level.data();
        tiles[targetTileX + targetTileY * WORLD_WIDTH] = 1;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
    {
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        int xOffset = window.getSize().x/2 - localPosition.x;
        int yOffset = window.getSize().y/2 - localPosition.y;
        float xZoom = window.getSize().x / camera.getSize().x;
        float yZoom = window.getSize().y / camera.getSize().y;
        int targetTileX = (camera.getCenter().x - xOffset/xZoom)/180;
        int targetTileY = (camera.getCenter().y - yOffset/yZoom)/180;

        int *tiles = level.data();
        tiles[targetTileX + targetTileY * WORLD_WIDTH] = 0;
    }
}