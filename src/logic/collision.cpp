#include "collision.hpp"
#include <cmath>
#include "../globals.hpp"

bool isTopEntityCollidingMap(Player player, const int* tiles) {
    bool topLeftColliding = false;
    unsigned int cornerX = static_cast<unsigned int>(floor(player.playerSprite.getPosition().x / (static_cast<float>(horizontal)/16.f)));
    unsigned int cornerY = static_cast<unsigned int>(floor(player.playerSprite.getPosition().y / (static_cast<float>(vertical)/8.f)));
    if (tiles[cornerX + cornerY * WORLD_WIDTH] == 0 || tiles[cornerX + cornerY * WORLD_WIDTH] == 3) {
        topLeftColliding = true;
    }

    bool topRightColliding = false;
    cornerX = static_cast<unsigned int>(floor((player.playerSprite.getPosition().x + (static_cast<float>(horizontal)/16.f) - 1)/ (static_cast<float>(horizontal)/16.f)));
    cornerY = static_cast<unsigned int>(floor(player.playerSprite.getPosition().y / (static_cast<float>(vertical)/8.f)));
    if (tiles[cornerX + cornerY * WORLD_WIDTH] == 0 || tiles[cornerX + cornerY * WORLD_WIDTH] == 3) {
        topRightColliding = true;
    }

    return topLeftColliding || topRightColliding;
}


bool isBotEntityCollidingMap(Player player, const int* tiles) {
    bool botLeftColliding = false;
    unsigned int cornerX = static_cast<unsigned int>(floor(player.playerSprite.getPosition().x / (static_cast<float>(horizontal)/16.f)));
    unsigned int cornerY = static_cast<unsigned int>(floor((player.playerSprite.getPosition().y + (static_cast<float>(vertical)/8.f)) / (static_cast<float>(vertical)/8.f)));
    if (tiles[cornerX + cornerY * WORLD_WIDTH] == 0 || tiles[cornerX + cornerY * WORLD_WIDTH] == 3) {
        botLeftColliding = true;
    }

    bool botRightColliding = false;
    cornerX = static_cast<unsigned int>(floor((player.playerSprite.getPosition().x + (static_cast<float>(horizontal)/16.f) - 1)/ (static_cast<float>(horizontal)/16.f)));
    cornerY = static_cast<unsigned int>(floor((player.playerSprite.getPosition().y + (static_cast<float>(vertical)/8.f))/ (static_cast<float>(vertical)/8.f)));
    if (tiles[cornerX + cornerY * WORLD_WIDTH] == 0 || tiles[cornerX + cornerY * WORLD_WIDTH] == 3) {
        botRightColliding = true;
    }

    return botLeftColliding || botRightColliding;
}

bool isLeftEntityCollidingMap(Player player, const int* tiles) {
    bool topLeftColliding = false;
    unsigned int cornerX = static_cast<unsigned int>(floor(player.playerSprite.getPosition().x / (static_cast<float>(horizontal)/16.f)));
    unsigned int cornerY = static_cast<unsigned int>(floor(player.playerSprite.getPosition().y / (static_cast<float>(vertical)/8.f)));
    if (tiles[cornerX + cornerY * WORLD_WIDTH] == 0 || tiles[cornerX + cornerY * WORLD_WIDTH] == 3) {
        topLeftColliding = true;
    }

    bool botLeftColliding = false;
    cornerX = static_cast<unsigned int>(floor(player.playerSprite.getPosition().x / (static_cast<float>(horizontal)/16.f)));
    cornerY = static_cast<unsigned int>(floor((player.playerSprite.getPosition().y + (static_cast<float>(vertical)/8.f) - 1) / (static_cast<float>(vertical)/8.f)));
    if (tiles[cornerX + cornerY * WORLD_WIDTH] == 0 || tiles[cornerX + cornerY * WORLD_WIDTH] == 3) {
        botLeftColliding = true;
    }

    return topLeftColliding || botLeftColliding;
}

bool isRightEntityCollidingMap(Player player, const int* tiles) {
    bool botRightColliding = false;
    unsigned int cornerX = static_cast<unsigned int>(floor((player.playerSprite.getPosition().x + (static_cast<float>(horizontal)/16.f) - 1)/ (static_cast<float>(horizontal)/16.f)));
    unsigned int cornerY = static_cast<unsigned int>(floor((player.playerSprite.getPosition().y + (static_cast<float>(vertical)/8.f) -1) / (static_cast<float>(vertical)/8.f)));
    if (tiles[cornerX + cornerY * WORLD_WIDTH] == 0 || tiles[cornerX + cornerY * WORLD_WIDTH] == 3) {
        botRightColliding = true;
    }


    bool topRightColliding = false;
    cornerX = static_cast<unsigned int>(floor((player.playerSprite.getPosition().x + (static_cast<float>(horizontal)/16.f) - 1)/ (static_cast<float>(horizontal)/16.f)));
    cornerY = static_cast<unsigned int>(floor(player.playerSprite.getPosition().y / (static_cast<float>(vertical)/8.f)));
    if (tiles[cornerX + cornerY * WORLD_WIDTH] == 0 || tiles[cornerX + cornerY * WORLD_WIDTH] == 3) {
        topRightColliding = true;
    }

    return botRightColliding || topRightColliding;
}