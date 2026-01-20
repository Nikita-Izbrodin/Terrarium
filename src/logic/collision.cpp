#include "collision.hpp"
#include <cmath>

bool isTopEntityCollidingMap(Player player, const int* tiles) {
    bool topLeftColliding = false;
    unsigned int cornerX = static_cast<unsigned int>(floor(player.playerSprite.getPosition().x / 160.f));
    unsigned int cornerY = static_cast<unsigned int>(floor(player.playerSprite.getPosition().y / 180.f));
    if (tiles[cornerX + cornerY * 16] == 0 || tiles[cornerX + cornerY * 16] == 3) {
        topLeftColliding = true;
    }

    bool topRightColliding = false;
    cornerX = static_cast<unsigned int>(floor((player.playerSprite.getPosition().x + 160 - 1)/ 160.f));
    cornerY = static_cast<unsigned int>(floor(player.playerSprite.getPosition().y / 180.f));
    if (tiles[cornerX + cornerY * 16] == 0 || tiles[cornerX + cornerY * 16] == 3) {
        topRightColliding = true;
    }

    return topLeftColliding || topRightColliding;
}


bool isBotEntityCollidingMap(Player player, const int* tiles) {
    bool botLeftColliding = false;
    unsigned int cornerX = static_cast<unsigned int>(floor(player.playerSprite.getPosition().x / 160.f));
    unsigned int cornerY = static_cast<unsigned int>(floor((player.playerSprite.getPosition().y +180) / 180.f));
    if (tiles[cornerX + cornerY * 16] == 0 || tiles[cornerX + cornerY * 16] == 3) {
        botLeftColliding = true;
    }

    bool botRightColliding = false;
    cornerX = static_cast<unsigned int>(floor((player.playerSprite.getPosition().x + 160 - 1)/ 160.f));
    cornerY = static_cast<unsigned int>(floor((player.playerSprite.getPosition().y +180)/ 180.f));
    if (tiles[cornerX + cornerY * 16] == 0 || tiles[cornerX + cornerY * 16] == 3) {
        botRightColliding = true;
    }

    return botLeftColliding || botRightColliding;
}

bool isLeftEntityCollidingMap(Player player, const int* tiles) {
    bool topLeftColliding = false;
    unsigned int cornerX = static_cast<unsigned int>(floor(player.playerSprite.getPosition().x / 160.f));
    unsigned int cornerY = static_cast<unsigned int>(floor(player.playerSprite.getPosition().y / 180.f));
    if (tiles[cornerX + cornerY * 16] == 0 || tiles[cornerX + cornerY * 16] == 3) {
        topLeftColliding = true;
    }

    bool botLeftColliding = false;
    cornerX = static_cast<unsigned int>(floor(player.playerSprite.getPosition().x / 160.f));
    cornerY = static_cast<unsigned int>(floor((player.playerSprite.getPosition().y +180 - 1) / 180.f));
    if (tiles[cornerX + cornerY * 16] == 0 || tiles[cornerX + cornerY * 16] == 3) {
        botLeftColliding = true;
    }

    return topLeftColliding || botLeftColliding;
}

bool isRightEntityCollidingMap(Player player, const int* tiles) {
    bool botRightColliding = false;
    unsigned int cornerX = static_cast<unsigned int>(floor((player.playerSprite.getPosition().x + 160 - 1)/ 160.f));
    unsigned int cornerY = static_cast<unsigned int>(floor((player.playerSprite.getPosition().y +180 -1) / 180.f));
    if (tiles[cornerX + cornerY * 16] == 0 || tiles[cornerX + cornerY * 16] == 3) {
        botRightColliding = true;
    }


    bool topRightColliding = false;
    cornerX = static_cast<unsigned int>(floor((player.playerSprite.getPosition().x + 160 - 1)/ 160.f));
    cornerY = static_cast<unsigned int>(floor(player.playerSprite.getPosition().y / 180.f));
    if (tiles[cornerX + cornerY * 16] == 0 || tiles[cornerX + cornerY * 16] == 3) {
        topRightColliding = true;
    }

    return botRightColliding || topRightColliding;
}