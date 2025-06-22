#include "render.h"
#include "Graphics.hpp"
#include "OpenGL.hpp"
#include "structs.h"
#include "player.h"

extern Player player;
extern Map map;

void Init()
{
    glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
    InitPlayer();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1024, 512, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void Display() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DrawMap();
    DrawPlayer();
	CastRay();
}

void DrawPlayer()
{
    // Player location
    glColor3f(1, 1, 0);
    glPointSize(8);
	glBegin(GL_POINTS);
    glVertex2i(player.posX, player.posY);
	glEnd();

    // Player direction
    glLineWidth(3);
	glBegin(GL_LINES);
    glVertex2i(player.posX, player.posY);
	glVertex2i(player.posX + player.dirX * 5, player.posY + player.dirY * 5);
    glEnd();
}

void DrawMap()
{
    int tileX, tileY, offsetX, offsetY;
    for (tileY = 0; tileY < map.height; ++tileY)
    {
        for (tileX = 0; tileX < map.width; ++tileX)
        {
            if (map.map[tileY * map.width + tileX] == 1)
                glColor3f(1, 1, 1); // White for tile
            else
                glColor3f(0, 0, 0); // Black for empty space

            offsetX = tileX * map.size;
            offsetY = tileY * map.size;

            glBegin(GL_QUADS);
            glVertex2i(offsetX + 1, offsetY + 1);
            glVertex2i(offsetX + 1, offsetY + map.size - 1);
            glVertex2i(offsetX + map.size - 1, offsetY + map.size - 1);
            glVertex2i(offsetX + map.size - 1, offsetY + 1);
            glEnd();
        }
    }
}

void CastRay()
{
    int rayIndex{}, mapX{}, mapY{}, mapPosition{}, depthOfField{};
    float rayX{}, rayY{}, rayAngle{}, offsetX{}, offsetY{};

    rayAngle = player.angle - DEGREE * 30;
	if (rayAngle < 0) 
        rayAngle += 2 * PI;
	if (rayAngle > 2 * PI)
		rayAngle -= 2 * PI;

    // rayAngle = player.angle;
    for (rayIndex = 0; rayIndex < 60; ++rayIndex)
    {
        depthOfField = 0;
        float horizontalDistance = 1000000.0f;
        float horizontalX = player.posX;
		float horizontalY = player.posY;
        float aTan = -1 / tan(rayAngle);
        if (rayAngle > PI)
        {
            rayY = (((int)player.posY >> 6) << 6) - 0.0001f;
            rayX = (player.posY - rayY) * aTan + player.posX;
            offsetY = -64;
            offsetX = -offsetY * aTan;
        }
        if (rayAngle < PI)
        {
            rayY = (((int)player.posY >> 6) << 6) + 64;
            rayX = (player.posY - rayY) * aTan + player.posX;
            offsetY = 64;
            offsetX = -offsetY * aTan;
        }
        if (rayAngle == 0 || rayAngle == PI)
        {
            rayX = player.posX;
            rayY = player.posY;
            depthOfField = 8;
        }
        while (depthOfField < 8)
        {
            mapX = (int)(rayX) >> 6;
            mapY = (int)(rayY) >> 6;
            mapPosition = mapY * map.width + mapX;
            if (mapPosition > 0 && mapPosition < map.width * map.height && map.map[mapPosition] > 0)
            {
				horizontalX = rayX;
				horizontalY = rayY;
				horizontalDistance = Distance(player.posX, player.posY, horizontalX, horizontalY, rayAngle);
                depthOfField = 8;
            }
            else
            {
                rayX += offsetX;
                rayY += offsetY;
                depthOfField++;
            }
        }

        // Vertical line check
        depthOfField = 0;
        float verticalDistance = 1000000.0f;
        float verticalX = player.posX;
        float verticalY = player.posY;
        float nTan = -tan(rayAngle);
        if (rayAngle > PI2 && rayAngle < PI3)
        {
            rayX = (((int)player.posX >> 6) << 6) - 0.0001f;
            rayY = (player.posX - rayX) * nTan + player.posY;
            offsetX = -64;
            offsetY = -offsetX * nTan;
        }
        if (rayAngle < PI2 || rayAngle > PI3)
        {
            rayX = (((int)player.posX >> 6) << 6) + 64;
            rayY = (player.posX - rayX) * nTan + player.posY;
            offsetX = 64;
            offsetY = -offsetX * nTan;
        }
        if (rayAngle == 0 || rayAngle == PI)
        {
            rayX = player.posX;
            rayY = player.posY;
            depthOfField = 8;
        }
        while (depthOfField < 8)
        {
            mapX = (int)(rayX) >> 6;
            mapY = (int)(rayY) >> 6;
            mapPosition = mapY * map.width + mapX;
            if (mapPosition > 0 && mapPosition < map.width * map.height && map.map[mapPosition] > 0)
            {
                verticalX = rayX;
                verticalY = rayY;
                verticalDistance = Distance(player.posX, player.posY, verticalX, verticalY, rayAngle);
                depthOfField = 8;
            }
            else
            {
                rayX += offsetX;
                rayY += offsetY;
                depthOfField++;
            }
        }
        
        if (verticalDistance < horizontalDistance)
        {
            rayX = verticalX;
            rayY = verticalY;
        }
        else
        {
            rayX = horizontalX;
            rayY = horizontalY;
		}
        
        glColor3f(1, 0, 0);
        glLineWidth(3);
        glBegin(GL_LINES);
        glVertex2i(player.posX, player.posY);
        glVertex2i(rayX, rayY);
        glEnd();
        rayAngle += DEGREE;
        if (rayAngle < 0)
            rayAngle += 2 * PI;
        if (rayAngle > 2 * PI)
            rayAngle -= 2 * PI;
    }
}

float Distance(float startX, float startY, float endX, float endY, float angle)
{
    float deltaX = endX - startX;
    float deltaY = endY - startY;

    float euclideanDistance = sqrt(deltaX * deltaX + deltaY * deltaY);
    float adjustedDistance = euclideanDistance * cos(player.angle - angle);

    return adjustedDistance;
}