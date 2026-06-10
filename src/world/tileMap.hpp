#pragma once

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    bool load(
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
    );

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};