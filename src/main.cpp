#include <SFML/Graphics.hpp>
#include <iostream>
#include "wtypes.h"
#include "tileMap.hpp"
#include "entities/player.hpp"
#include "logic/collision.hpp"
#include "logic/keyboardInput.hpp"
#include "globals.hpp"

unsigned int horizontal;
unsigned int vertical;
float gravity;
sf::RenderWindow window;
sf::Time dt;
sf::Texture texture;
Player player(texture);
std::array<int, 128> level; // !! Hardcoded size

int main()
{
    gravity = 1000.f;

    level = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
        3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    };

    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    horizontal = desktop.right;
    vertical = desktop.bottom;
    
    window.create(sf::VideoMode({horizontal, vertical}), "Terrarium", sf::State::Fullscreen);

    TileMap map;
    if (!map.load("tileset.png", {32, 32}, level.data(), 16, 8, horizontal, vertical))
        return -1;

    sf::View camera = sf::View({static_cast<float>(horizontal)/2, static_cast<float>(vertical)/2}, {static_cast<float>(horizontal), static_cast<float>(vertical)});
    camera.zoom(0.8f);

    if (!texture.loadFromFile("red.png", false, sf::IntRect({0, 0}, {static_cast<int>(horizontal)/16, static_cast<int>(vertical)/8})))
    {
        return -1;
    }

    //Player player(texture);
    player.init(texture);

    player.playerSprite.setPosition({static_cast<float>(horizontal/16*6), static_cast<float>(vertical/8*3)});
    
    sf::Clock clock; // starts the clock
    sf::Time lastTime = clock.getElapsedTime();
    sf::Time currentTime;

    //std::cout << &window << "\n";
    //std::cout << &::window << "\n";
    std::cout << &player << "\n";

    while (window.isOpen())
    {
        currentTime = clock.getElapsedTime();
        dt = currentTime - lastTime;

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();            
        }

        processKeyboardInput();
        camera.setCenter({
            player.playerSprite.getPosition().x + player.playerSprite.getTexture().getSize().x/ 2,
            player.playerSprite.getPosition().y + player.playerSprite.getTexture().getSize().y/ 2
        });

        window.setView(camera);
        window.clear();
        window.draw(map);
        window.draw(player.playerSprite);
        window.display();
        //std::cout << player.playerSprite.getPosition().x << "\n";

        lastTime = currentTime;
    }
}