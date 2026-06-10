#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream> 
#include <wtypes.h>
#include <sys/stat.h>
#include "world/tileMap.hpp"
#include <vector>
#include "entities/player.hpp"
#include "logic/collision.hpp"
#include "logic/keyboardInput.hpp"
#include "globals.hpp"
#include "world/worldGeneration.hpp"

// TODO improve globals

unsigned int horizontal;
unsigned int vertical;
sf::RenderWindow window;
sf::Time dt;
sf::Texture texture;
sf::View camera;
Player player(texture);
std::array<int, WORLD_HEIGHT*WORLD_WIDTH> level;

void createWorld()
{
    int *tiles = level.data();
    
    int* pWorld = generateTerrain();

    for (int i = 0; i < WORLD_HEIGHT * WORLD_WIDTH; i++)
    {
        tiles[i] = pWorld[i];
    }

    std::ofstream file;
    file.open("../../src/worldSaves/defaultWorld.txt");
    for (int i = 0; i < WORLD_HEIGHT*WORLD_WIDTH; i++)
    {
        file << (tiles[i]);
        file << ("\n");
    }
    file.close();
}

void loadWorld()
{
    int *tiles = level.data();

    std::string tileValue;
    std::ifstream file;
    file.open("../../src/worldSaves/defaultWorld.txt");
    for (int i=0; i < WORLD_HEIGHT*WORLD_WIDTH; i++)
    {
        getline(file, tileValue);
        char * c = tileValue.data();
        tiles[i] = atoi(c);
    }
    file.close();
}

void initWindow()
{
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    horizontal = desktop.right;
    vertical = desktop.bottom;
    window.create(sf::VideoMode({horizontal, vertical}), "Terrarium", sf::State::Fullscreen);
    window.setVerticalSyncEnabled(false);
}

int main()
{
    const char* file = "../../src/worldSaves/defaultWorld.txt";
    struct stat sb;
    if (!((stat(file, &sb) == 0 && !(sb.st_mode & S_IFDIR)))) // if file does not exist
    {
        createWorld();
    } else
    {
        loadWorld();
    }

    initWindow();
    
    camera = sf::View({
        static_cast<float>(horizontal)/2,
        static_cast<float>(vertical)/2},
        {static_cast<float>(horizontal),
        static_cast<float>(vertical)
    });
    camera.zoom(2.f);

    if (!texture.loadFromFile("red.png", false, sf::IntRect({0, 0}, {180, 180}))) {return -1;}
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
        window.setView(camera);
        window.clear();

        TileMap map;
        if (!map.load(
            "tileset.png",
            {32, 32},
            level.data(),
            WORLD_WIDTH,
            WORLD_HEIGHT,
            WORLD_WIDTH*180,
            WORLD_HEIGHT*180,
            camera.getCenter().x,
            camera.getCenter().y,
            camera.getSize().x,
            camera.getSize().y
        )) {return -1;}

        window.draw(map);
        window.draw(player.playerSprite);
        window.display();

        lastTime = currentTime;
    }
}