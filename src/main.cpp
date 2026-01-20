#include <SFML/Graphics.hpp>
#include <iostream>
#include "wtypes.h"
#include "tileMap.hpp"
#include "entities/player.hpp"
#include "logic/collision.hpp"

unsigned int horizontal;
unsigned int vertical;

int main()
{
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    horizontal = desktop.right;
    vertical = desktop.bottom;
    float gravity = 400.f;

    sf::RenderWindow window(sf::VideoMode({horizontal, vertical}), "Terrarium", sf::State::Fullscreen);

    constexpr std::array level = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1,
        1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
        3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    };

    TileMap map;
    if (!map.load("tileset.png", {32, 32}, level.data(), 16, 8, horizontal, vertical))
        return -1;

    sf::Texture texture;
    if (!texture.loadFromFile("red.png", false, sf::IntRect({0, 0}, {static_cast<int>(horizontal)/16, static_cast<int>(vertical)/8})))
    {
        return -1;
    }

    Player player(texture);

    player.playerSprite.setPosition({static_cast<float>(horizontal/16*6), static_cast<float>(vertical/8*3)});
    
    sf::Clock clock; // starts the clock
    sf::Time lastTime = clock.getElapsedTime();
    sf::Time currentTime;

    // run the main loop
    while (window.isOpen())
    {
        currentTime = clock.getElapsedTime();
        sf::Time dt = currentTime - lastTime;

        // handle events
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();            
        }

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
        }

        window.clear();
        window.draw(map);
        window.draw(player.playerSprite);
        window.display();

        lastTime = currentTime;
    }
}