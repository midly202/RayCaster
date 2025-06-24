#include "player.h"
#include "structs.h"
#include <Window.hpp>
#include <math.h>

extern Player player;
extern Map map;
extern bool render3D;

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
        float strafeX = cos(player.angle - PI / 2.0f);
        float strafeY = sin(player.angle - PI / 2.0f);
        player.posX += strafeX * deltaTime * moveSpeed;
        player.posY += strafeY * deltaTime * moveSpeed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        float strafeX = cos(player.angle + PI / 2.0f);
        float strafeY = sin(player.angle + PI / 2.0f);
        player.posX += strafeX * deltaTime * moveSpeed;
        player.posY += strafeY * deltaTime * moveSpeed;
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