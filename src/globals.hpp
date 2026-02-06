#pragma once
#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "entities/player.hpp"
#include <SFML/Graphics.hpp>

// TEMPORARY FIX

extern unsigned int horizontal;
extern unsigned int vertical;
extern float gravity;
extern sf::RenderWindow window;
extern sf::Time dt;
extern sf::Texture texture;
extern Player player;
constexpr int WORLD_WIDTH = 4200;
constexpr int WORLD_HEIGHT = 1000;
extern std::array<int, WORLD_HEIGHT*WORLD_WIDTH> level;


#endif