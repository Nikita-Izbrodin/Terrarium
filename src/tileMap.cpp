#include <SFML/Graphics.hpp>
#include <iostream>
#include "tileMap.hpp"

bool TileMap::load(
    const std::filesystem::path &tileset,
    sf::Vector2u tileSize,
    const int *tiles,
    unsigned int worldWidthTiles,
    unsigned int worldHeightTiles,
    unsigned int worldWidthPixels,
    unsigned int worldHeightPixels,
    float cameraCenterx,
    float cameraCentery,
    float cameraSizex,
    float cameraSizey
)
{
    // load the tileset texture
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // calculate which tiles the player can see
    float left = cameraCenterx - cameraSizex / 2;
    float right = cameraCenterx + cameraSizex / 2;
    float top = cameraCentery - cameraSizey / 2;
    float bottom = cameraCentery + cameraSizey / 2;

    unsigned int xTileStart = left / 180;
    unsigned int xTileEnd = right / 180;
    unsigned int yTileStart = top / 180;
    unsigned int yTileEnd = bottom / 180;

    //std::cout << xTileStart << "\n";
    //std::cout << xTileEnd << "\n";
    //std::cout << yTileStart << "\n";
    //std::cout << yTileEnd << "\n";

    // resize the vertex array to fit the level size
    unsigned int numOfVisibleTilesx = xTileEnd - xTileStart;
    unsigned int numOfVisibleTilesy = yTileEnd - yTileStart;
    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    m_vertices.resize(numOfVisibleTilesx * numOfVisibleTilesy * 6);

    // populate the vertex array, with two triangles per tile
    for (unsigned int x = xTileStart; x < xTileEnd; ++x)
    {
        for (unsigned int y = yTileStart; y < yTileEnd; ++y)
        {
            // get the current tile number
            const int tileNumber = tiles[x + y * worldWidthTiles];

            // find its position in the tileset texture
            const int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            const int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // get a pointer to the triangles' vertices of the current tile
            unsigned int localX = x - xTileStart;
            unsigned int localY = y - yTileStart;
            sf::Vertex *triangles = &m_vertices[(localX + localY * numOfVisibleTilesx) * 6];

            // define the 6 corners of the two triangles
            triangles[0].position = sf::Vector2f(x * worldWidthPixels / worldWidthTiles, y * worldHeightPixels / worldHeightTiles);
            triangles[1].position = sf::Vector2f((x + 1) * worldWidthPixels / worldWidthTiles, y * worldHeightPixels / worldHeightTiles);
            triangles[2].position = sf::Vector2f(x * worldWidthPixels / worldWidthTiles, (y + 1) * worldHeightPixels / worldHeightTiles);
            triangles[3].position = sf::Vector2f(x * worldWidthPixels / worldWidthTiles, (y + 1) * worldHeightPixels / worldHeightTiles);
            triangles[4].position = sf::Vector2f((x + 1) * worldWidthPixels / worldWidthTiles, y * worldHeightPixels / worldHeightTiles);
            triangles[5].position = sf::Vector2f((x + 1) * worldWidthPixels / worldWidthTiles, (y + 1) * worldHeightPixels / worldHeightTiles);

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

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    // draw the vertex array
    target.draw(m_vertices, states);
}