#include <SFML/Graphics.hpp>
#include <iostream>
#include "wtypes.h"
#include "tileMap.hpp"
#include "entities/player.hpp"
#include "logic/collision.hpp"
#include "logic/keyboardInput.hpp"
#include "globals.hpp"
#include <vector>

//const int WORLD_WIDTH = 4200;
//const int WORLD_HEIGHT = 1200;

unsigned int horizontal;
unsigned int vertical;
float gravity;
sf::RenderWindow window;
sf::Time dt;
sf::Texture texture;
Player player(texture);
std::array<int, WORLD_HEIGHT*WORLD_WIDTH> level; // !! Hardcoded size

int main()
{
    gravity = 1000.f;
    //gravity = 0.f;

    int *tiles = level.data();

    for (int i  = 0; i < (WORLD_HEIGHT/4)*WORLD_WIDTH; i++)
    {
        tiles[i] = 1; // air
    }
    for (int i  = (WORLD_HEIGHT/4)*WORLD_WIDTH; i < (WORLD_HEIGHT/4)*WORLD_WIDTH + WORLD_WIDTH; i++)
    {
        tiles[i] = 0; // grass
    }
    for (int i = (WORLD_HEIGHT/4)*WORLD_WIDTH + WORLD_WIDTH; i < WORLD_HEIGHT*WORLD_WIDTH; i++)
    {
        tiles[i] = 3; // stone
    }

    /*
    level = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
        3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    };
    */

    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    horizontal = desktop.right;
    vertical = desktop.bottom;
    
    window.create(sf::VideoMode({horizontal, vertical}), "Terrarium", sf::State::Fullscreen);
    window.setVerticalSyncEnabled(false);

    TileMap map;
    if (!map.load("tileset.png", {32, 32}, level.data(), WORLD_WIDTH, WORLD_HEIGHT, WORLD_WIDTH*180, WORLD_HEIGHT*180))
        return -1;

    sf::View camera = sf::View({static_cast<float>(horizontal)/2, static_cast<float>(vertical)/2}, {static_cast<float>(horizontal), static_cast<float>(vertical)});
    //float zoom = 0.8;
    //camera.zoom(zoom);
    camera.zoom(2.f);

    if (!texture.loadFromFile("red.png", false, sf::IntRect({0, 0}, {180, 180})))
    {
        return -1;
    }

    player.init(texture);

    player.playerSprite.setPosition({(WORLD_WIDTH/2)*180, ((WORLD_HEIGHT/4)-1)*180});
    
    sf::Clock clock; // starts the clock
    sf::Time lastTime = clock.getElapsedTime();
    sf::Time currentTime;

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Q)) {
            //zoom += 10.f * dt.asSeconds();
            camera.zoom(2.25f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::E)) {
            //zoom += 10.f * dt.asSeconds();
            camera.zoom(1/2.25f);
        }

        window.setView(camera);
        window.clear();
        window.draw(map);
        window.draw(player.playerSprite);
        window.display();
        //std::cout << player.playerSprite.getPosition().x << "\n";

        lastTime = currentTime;
    }
}