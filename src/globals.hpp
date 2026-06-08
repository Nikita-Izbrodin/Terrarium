#pragma once
#include "entities/player.hpp"
#include <SFML/Graphics.hpp>

extern unsigned int horizontal;
extern unsigned int vertical;
extern sf::RenderWindow window;
extern sf::Time dt;
extern sf::Texture texture;
extern Player player;
extern sf::View camera;
constexpr int WORLD_WIDTH = 4200;
constexpr int WORLD_HEIGHT = 1000;
extern std::array<int, WORLD_HEIGHT*WORLD_WIDTH> level;
constexpr float gravity = 1000.f;