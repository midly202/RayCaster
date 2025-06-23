#include "player.h"
#include "structs.h"
#include <Window.hpp>
#include <math.h>

Player player;
Map map;

bool render3D = true;

void InitPlayer()
{
	player.posX = 100;
	player.posY = 100;
    player.angle = 90 * DEGREE;
    player.dirX = cos(player.angle) * 5;
    player.dirY = sin(player.angle) * 5;
}

void PlayerMove(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::W) 
    {
        player.posX += player.dirX;
        player.posY += player.dirY;
    }

    if (key == sf::Keyboard::A)
    {
        player.angle -= 0.1f;
        if (player.angle < 0)
            player.angle += 2 * PI;

        player.dirX = cos(player.angle) * 5;
        player.dirY = sin(player.angle) * 5;
    }

    if (key == sf::Keyboard::S)
    {
        player.posX -= player.dirX;
		player.posY -= player.dirY;
    }

    if (key == sf::Keyboard::D)
    {
        player.angle += 0.1f;
        if (player.angle > 2 * PI)
            player.angle -= 2 * PI;

        player.dirX = cos(player.angle) * 5;
        player.dirY = sin(player.angle) * 5;
    }

    if (key == sf::Keyboard::V)
    {
		render3D = !render3D;
    }
}