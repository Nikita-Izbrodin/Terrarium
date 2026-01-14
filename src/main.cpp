#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "wtypes.h"

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    bool load(const std::filesystem::path& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height, unsigned int horizontal, unsigned int vertical)
    {
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
        m_vertices.resize(width * height * 6);

        // populate the vertex array, with two triangles per tile
        for (unsigned int i = 0; i < width; ++i)
        {
            for (unsigned int j = 0; j < height; ++j)
            {
                // get the current tile number
                const int tileNumber = tiles[i + j * width];

                // find its position in the tileset texture
                const int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                const int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the triangles' vertices of the current tile
                sf::Vertex* triangles = &m_vertices[(i + j * width) * 6];

                // define the 6 corners of the two triangles
                triangles[0].position = sf::Vector2f(i * horizontal/width, j * vertical/height);
                triangles[1].position = sf::Vector2f((i + 1) * horizontal/width, j * vertical/height);
                triangles[2].position = sf::Vector2f(i * horizontal/width, (j + 1) * vertical/height);
                triangles[3].position = sf::Vector2f(i * horizontal/width, (j + 1) * vertical/height);
                triangles[4].position = sf::Vector2f((i + 1) * horizontal/width, j * vertical/height);
                triangles[5].position = sf::Vector2f((i + 1) * horizontal/width, (j + 1) * vertical/height);

                // define the 6 matching texture coordinates
                triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
                triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
                triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            }
        }

        return true;
    }

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture     m_tileset;
};



unsigned int horizontal;
unsigned int vertical;

class Player
{
    public:
    sf::Sprite playerSprite;
    Player(sf::Texture& texture) : playerSprite(texture) {
    }
    sf::Vector2f getTopLeftPos ()
    {
        return playerSprite.getPosition();
    }
    sf::Vector2f getTopRightPos ()
    {
        sf::Vector2f topRight(playerSprite.getPosition().x + static_cast<int>(horizontal)/16, playerSprite.getPosition().y);
        return topRight;
    }
    sf::Vector2f getBotLeftPos ()
    {
        return playerSprite.getPosition();
    }
    sf::Vector2f getBotRightPos ()
    {
        return playerSprite.getPosition();
    }
};

bool isTopEntityCollidingMap(Player player, const int* tiles) {
    bool topLeftColliding = false;
    unsigned int cornerX = static_cast<unsigned int>(floor(player.getTopLeftPos().x / 160.f));
    unsigned int cornerY = static_cast<unsigned int>(floor(player.getTopLeftPos().y / 180.f));
    if (tiles[cornerX + cornerY * 16] == 1 || tiles[cornerX + cornerY * 16] == 2) {
        topLeftColliding = true;
    }

    bool topRightColliding = false;
    cornerX = static_cast<unsigned int>(floor((player.getTopLeftPos().x + 160 - 1)/ 160.f));
    cornerY = static_cast<unsigned int>(floor(player.getTopLeftPos().y / 180.f));
    if (tiles[cornerX + cornerY * 16] == 1 || tiles[cornerX + cornerY * 16] == 2) {
        topRightColliding = true;
    }

    return topLeftColliding || topRightColliding;
}


bool isBotEntityCollidingMap(Player player, const int* tiles) {
    bool botLeftColliding = false;
    unsigned int cornerX = static_cast<unsigned int>(floor(player.getTopLeftPos().x / 160.f));
    unsigned int cornerY = static_cast<unsigned int>(floor((player.getTopLeftPos().y +180 - 1) / 180.f));
    if (tiles[cornerX + cornerY * 16] == 1 || tiles[cornerX + cornerY * 16] == 2) {
        botLeftColliding = true;
    }

    bool botRightColliding = false;
    cornerX = static_cast<unsigned int>(floor((player.getTopLeftPos().x + 160 - 1)/ 160.f));
    cornerY = static_cast<unsigned int>(floor((player.getTopLeftPos().y +180 - 1)/ 180.f));
    if (tiles[cornerX + cornerY * 16] == 1 || tiles[cornerX + cornerY * 16] == 2) {
        botRightColliding = true;
    }

    return botLeftColliding || botRightColliding;
}

bool isLeftEntityCollidingMap(Player player, const int* tiles) {
    bool topLeftColliding = false;
    unsigned int cornerX = static_cast<unsigned int>(floor(player.getTopLeftPos().x / 160.f));
    unsigned int cornerY = static_cast<unsigned int>(floor(player.getTopLeftPos().y / 180.f));
    if (tiles[cornerX + cornerY * 16] == 1 || tiles[cornerX + cornerY * 16] == 2) {
        topLeftColliding = true;
    }

    bool botLeftColliding = false;
    cornerX = static_cast<unsigned int>(floor(player.getTopLeftPos().x / 160.f));
    cornerY = static_cast<unsigned int>(floor((player.getTopLeftPos().y +180 - 1) / 180.f));
    if (tiles[cornerX + cornerY * 16] == 1 || tiles[cornerX + cornerY * 16] == 2) {
        botLeftColliding = true;
    }

    return topLeftColliding || botLeftColliding;
}

bool isRightEntityCollidingMap(Player player, const int* tiles) {
    bool botRightColliding = false;
    unsigned int cornerX = static_cast<unsigned int>(floor((player.getTopLeftPos().x + 160 - 1)/ 160.f));
    unsigned int cornerY = static_cast<unsigned int>(floor((player.getTopLeftPos().y +180 -1) / 180.f));
    if (tiles[cornerX + cornerY * 16] == 1 || tiles[cornerX + cornerY * 16] == 2) {
        botRightColliding = true;
    }


    bool topRightColliding = false;
    cornerX = static_cast<unsigned int>(floor((player.getTopLeftPos().x + 160 - 1)/ 160.f));
    cornerY = static_cast<unsigned int>(floor(player.getTopLeftPos().y / 180.f));
    if (tiles[cornerX + cornerY * 16] == 1 || tiles[cornerX + cornerY * 16] == 2) {
        topRightColliding = true;
    }

    return botRightColliding || topRightColliding;
}

int main()
{
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    horizontal = desktop.right;
    vertical = desktop.bottom;

    // create the window
    sf::RenderWindow window(sf::VideoMode({horizontal, vertical}), "Terrarium", sf::State::Fullscreen);

    // define the level with an array of tile indices
    constexpr std::array level = {
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    };

    // create the tilemap from the level definition
    TileMap map;
    if (!map.load("tileset.png", {32, 32}, level.data(), 16, 8, horizontal, vertical))
        return -1;

    sf::Texture texture;
    if (!texture.loadFromFile("red.png", false, sf::IntRect({0, 0}, {static_cast<int>(horizontal)/16, static_cast<int>(vertical)/8})))
    {
        return -1;
    }

    Player player(texture);

    //sf::Sprite player(texture);
    player.playerSprite.setPosition({static_cast<float>(horizontal/16*6), static_cast<float>(vertical/8*3)});
    

    // run the main loop
    while (window.isOpen())
    {
        // handle events
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();            
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape))
            window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
            player.playerSprite.move({0.f, -.2f});
            if (isTopEntityCollidingMap(player, level.data())) {
                player.playerSprite.move({0.f, .2f});
            }
        } 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
            player.playerSprite.move({0.f, .2f});
            if (isBotEntityCollidingMap(player, level.data())) {
                player.playerSprite.move({0.f, -.2f});
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
            std::cout << "X: " << player.getTopRightPos().x << " " << "Y: " << player.getTopRightPos().y << "\n";
        }

        // draw the map
        window.clear();
        window.draw(map);
        window.draw(player.playerSprite);
        window.display();
    }
}