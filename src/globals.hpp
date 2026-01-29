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
extern std::array<int, 128> level;

#endif