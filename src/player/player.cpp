#include "player.h"

#include <math.h>

#include <Window.hpp>

#include "structs.h"

extern Player player;
extern Map map;
extern bool render3D;
extern bool useMouse;

void InitPlayer()
{
    player.posX = 100;
    player.posY = 100;
    player.angle = 90 * DEGREE;
    player.dirX = cos(player.angle);
    player.dirY = sin(player.angle);
}

void PlayerMove(float deltaTime)
{
    const float moveSpeed = 200.0f;
    const float rotSpeed = 3.0f;
    const float tileSize = Map::size;
    const float collisionRadius = 10.0f;

    float moveStep = deltaTime * moveSpeed;
    float rotStep = deltaTime * rotSpeed;

    float newX, newY;

    auto isWalkable = [&](float x, float y) -> bool
    {
        float checkOffsets[4][2] =
        {
            {-collisionRadius, -collisionRadius},
            {-collisionRadius, collisionRadius},
            {collisionRadius, -collisionRadius},
            {collisionRadius, collisionRadius},
        };

        for (int i = 0; i < 4; ++i)
        {
            float checkX = x + checkOffsets[i][0];
            float checkY = y + checkOffsets[i][1];

            int mapX = int(checkX / tileSize);
            int mapY = int(checkY / tileSize);

            if (mapX < 0 || mapX >= Map::width || mapY < 0 || mapY >= Map::height)
                return false;

            if (map.map[mapY * Map::width + mapX] != 0)
                return false;
        }

        return true;
    };


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        newX = player.posX + player.dirX * moveStep;
        newY = player.posY + player.dirY * moveStep;

        if (isWalkable(newX, player.posY)) player.posX = newX;
        if (isWalkable(player.posX, newY)) player.posY = newY;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        newX = player.posX - player.dirX * moveStep;
        newY = player.posY - player.dirY * moveStep;

        if (isWalkable(newX, player.posY)) player.posX = newX;
        if (isWalkable(player.posX, newY)) player.posY = newY;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (useMouse)
        {
            float strafeX = cos(player.angle - PI / 2.0f);
            float strafeY = sin(player.angle - PI / 2.0f);

            newX = player.posX + strafeX * moveStep;
            newY = player.posY + strafeY * moveStep;

            if (isWalkable(newX, player.posY)) player.posX = newX;
            if (isWalkable(player.posX, newY)) player.posY = newY;
        }
        else
        {
            player.angle -= rotStep;
            if (player.angle < 0) player.angle += 2 * PI;
            player.dirX = cos(player.angle);
            player.dirY = sin(player.angle);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (useMouse)
        {
            float strafeX = cos(player.angle + PI / 2.0f);
            float strafeY = sin(player.angle + PI / 2.0f);

            newX = player.posX + strafeX * moveStep;
            newY = player.posY + strafeY * moveStep;

            if (isWalkable(newX, player.posY)) player.posX = newX;
            if (isWalkable(player.posX, newY)) player.posY = newY;
        }
        else
        {
            player.angle += rotStep;
            if (player.angle > 2 * PI) player.angle -= 2 * PI;
            player.dirX = cos(player.angle);
            player.dirY = sin(player.angle);
        }
    }

    static bool togglePressed = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
    {
        if (!togglePressed)
        {
            render3D = !render3D;
            togglePressed = true;
        }
    }
    else
        togglePressed = false;
}
