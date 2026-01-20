#pragma once
#include "../entities/player.hpp"

bool isTopEntityCollidingMap(Player player, const int* tiles);
bool isBotEntityCollidingMap(Player player, const int* tiles);
bool isLeftEntityCollidingMap(Player player, const int* tiles);
bool isRightEntityCollidingMap(Player player, const int* tiles);