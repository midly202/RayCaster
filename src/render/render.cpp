#include "render.h"
#include "Graphics.hpp"
#include "OpenGL.hpp"
#include "structs.h"
#include "player.h"

extern Player player;
extern Map map;

void init()
{
    // Set clear color (dark gray background)
    glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
    InitPlayer();

    // Set orthographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1024, 512, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void display() 
{
    // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawMap();
    drawPlayer();    
}

void drawPlayer()
{
    glColor3f(1, 1, 0);
    glPointSize(8);
	glBegin(GL_POINTS);
    glVertex2i(player.posX, player.posY);
	glEnd();

    glLineWidth(3);
	glBegin(GL_LINES);
    glVertex2i(player.posX, player.posY);
	glVertex2i(player.posX + player.dirX * 5, player.posY + player.dirY * 5);
    glEnd();
}

void drawMap()
{
    int x, y, xo, yo;
    for (y = 0; y < map.height; ++y)
    {
        for (x = 0; x < map.width; ++x)
        {
            if (map.map[y*map.width+x] == 1)
                glColor3f(1, 1, 1);
            else
				glColor3f(0, 0, 0);

            xo = x * map.size;
            yo = y * map.size;
			glBegin(GL_QUADS);
            glVertex2i(xo + 1, yo + 1);
            glVertex2i(xo + 1, yo + map.size - 1);
            glVertex2i(xo + map.size - 1, yo + map.size - 1);
			glVertex2i(xo + map.size - 1, yo + 1);
            glEnd();
		}
    }
}