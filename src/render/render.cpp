#include "render.h"
#include "Graphics.hpp"
#include "OpenGL.hpp"

void display() 
{
    // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Swap handled by window.display() in SFML
}

void init() 
{
    // Set clear color (dark gray background)
    glClearColor(0.3f, 0.3f, 0.3f, 0.0f);

    // Set orthographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1024, 512, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}