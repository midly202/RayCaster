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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        player.posX += player.dirX * deltaTime * moveSpeed;
        player.posY += player.dirY * deltaTime * moveSpeed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        player.posX -= player.dirX * deltaTime * moveSpeed;
        player.posY -= player.dirY * deltaTime * moveSpeed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (useMouse)
        {
            float strafeX = cos(player.angle - PI / 2.0f);
            float strafeY = sin(player.angle - PI / 2.0f);
            player.posX += strafeX * deltaTime * moveSpeed;
            player.posY += strafeY * deltaTime * moveSpeed;
        }
        else
        {
            player.angle -= rotSpeed * deltaTime;
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
            player.posX += strafeX * deltaTime * moveSpeed;
            player.posY += strafeY * deltaTime * moveSpeed;
        }
        else
        {
            player.angle += rotSpeed * deltaTime;
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
