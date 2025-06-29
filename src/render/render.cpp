#if !defined(_WIN32)
#include <GL/gl.h>
#endif

#include <cmath>

#include "Graphics.hpp"  // IWYU pragma: keep
#include "OpenGL.hpp"    // IWYU pragma: keep
#include "player.h"
#include "render.h"
#include "structs.h"

extern Player player;
extern Map map;
extern sf::Font font;

extern bool render3D;
extern bool showPauseMenu;
extern bool shouldExit;

void Init()
{
    glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
    InitPlayer();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void Display(sf::RenderWindow& window)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!render3D)
    {
        DrawMap(WIDTH, HEIGHT);
        DrawPlayer(WIDTH, HEIGHT);
    }
    CastRay(WIDTH, HEIGHT);

    if (showPauseMenu)
        DrawPauseMenu(window, font);
}

void DrawPauseMenu(sf::RenderWindow& window, const sf::Font& font)
{
    const int menuWidth = 200;
    const int menuHeight = 100;
    const int centerX = WIDTH / 2;
    const int centerY = HEIGHT / 2;
    const int menuX = centerX - menuWidth / 2;
    const int menuY = centerY - menuHeight / 2;

    // Background rectangle
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2i(menuX, menuY);
    glVertex2i(menuX + menuWidth, menuY);
    glVertex2i(menuX + menuWidth, menuY + menuHeight);
    glVertex2i(menuX, menuY + menuHeight);
    glEnd();

    // Simple "Exit" button
    const int buttonWidth = 120;
    const int buttonHeight = 30;
    const int buttonX = centerX - buttonWidth / 2;
    const int buttonY = centerY - buttonHeight / 2;

    // Button color
    glColor3f(0.8f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2i(buttonX, buttonY);
    glVertex2i(buttonX + buttonWidth, buttonY);
    glVertex2i(buttonX + buttonWidth, buttonY + buttonHeight);
    glVertex2i(buttonX, buttonY + buttonHeight);
    glEnd();

    // Exit text
    sf::Text exitText;
    exitText.setFont(font);
    exitText.setString("EXIT");
    exitText.setCharacterSize(18);
    exitText.setFillColor(sf::Color::White);
    exitText.setStyle(sf::Text::Bold);

    exitText.setPosition((float)(buttonX + (float)buttonWidth / 2 - 20), (float)(buttonY + 5));

    // Draw text
    window.pushGLStates();
    window.draw(exitText);
    window.popGLStates();

    // Handle mouse click
    static bool mousePressedLastFrame = false;
    bool mousePressedNow = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (mousePressedNow && !mousePressedLastFrame)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (mousePos.x >= buttonX && mousePos.x <= buttonX + buttonWidth &&
            mousePos.y >= buttonY && mousePos.y <= buttonY + buttonHeight)
        {
            shouldExit = true;
        }
    }

    mousePressedLastFrame = mousePressedNow;
}

void DrawPlayer(int windowWidth, int windowHeight)
{
    int centerX = windowWidth / 2;
    int centerY = windowHeight / 2;
    int startX = centerX - (map.width * map.size) / 2;
    int startY = centerY - (map.height * map.size) / 2;

    int adjustedPosX = player.posX + startX;
    int adjustedPosY = player.posY + startY;

    // Player location
    glColor3f(1, 1, 0);
    glPointSize((int)5);
    glBegin(GL_POINTS);
    glVertex2i(adjustedPosX, adjustedPosY);
    glEnd();

    // Player direction
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(adjustedPosX, adjustedPosY);
    glVertex2i(adjustedPosX + player.dirX * 5, adjustedPosY + player.dirY * 5);
    glEnd();
}

void DrawMap(int windowWidth, int windowHeight)
{
    int tileX, tileY, offsetX, offsetY;

    int centerX = windowWidth / 2;
    int centerY = windowHeight / 2;
    int startX = centerX - (map.width * map.size) / 2;
    int startY = centerY - (map.height * map.size) / 2;

    for (tileY = 0; tileY < map.height; ++tileY)
    {
        for (tileX = 0; tileX < map.width; ++tileX)
        {
            if (map.map[tileY * map.width + tileX] == 1)
                glColor3f(1, 1, 1);
            else if (map.map[tileY * map.width + tileX] == 2)
                glColor3f(0.5, 0.5, 0.5);
            else
                glColor3f(0, 0, 0);

            offsetX = startX + tileX * map.size;
            offsetY = startY + tileY * map.size;

            glBegin(GL_QUADS);
            glVertex2i(offsetX + 1, offsetY + 1);
            glVertex2i(offsetX + 1, offsetY + map.size - 1);
            glVertex2i(offsetX + map.size - 1, offsetY + map.size - 1);
            glVertex2i(offsetX + map.size - 1, offsetY + 1);
            glEnd();
        }
    }
}

void Render3D(int rayIndex, float distance, float rayAngle, int wallType, bool shading, int windowWidth, int windowHeight)
{
    float ca = player.angle - rayAngle;

    if (ca < 0) ca += 2 * PI;
    if (ca > 2 * PI) ca -= 2 * PI;

    float projectionPlaneDist = (windowWidth / 2.0f) / tan(FOV / 2.0f);
    float lineH = (map.size / distance) * projectionPlaneDist;
    if (lineH > windowHeight) lineH = windowHeight;

    float lineO = (windowHeight / 2.0f) - (lineH / 2.0f);

    // Color based on wall type and ray side
    if (wallType == 1 && shading)
        glColor3f(0.9, 0, 0);
    else if (wallType == 1 && !shading)
        glColor3f(0.5, 0, 0);
    else if (wallType == 2 && shading)
        glColor3f(0, 0.9, 0);
    else if (wallType == 2 && !shading)
        glColor3f(0, 0.5, 0);

    float rayScreenStep = (float)windowWidth / NUM_RAYS;
    float x = rayIndex * rayScreenStep;

    glLineWidth(rayScreenStep);
    glBegin(GL_LINES);
    glVertex2i(x, lineO);
    glVertex2i(x, lineO + lineH);
    glEnd();
}

void CastRay(int windowWidth, int windowHeight)
{
    int rayIndex{}, mapX{}, mapY{}, mapPosition{}, depthOfField{}, wallTypeHorizontal{}, wallTypeVertical{};
    double rayX{}, rayY{}, rayAngle{}, offsetX{}, offsetY{};
    bool shading{};

    int centerX = windowWidth / 2;
    int centerY = windowHeight / 2;
    int startX = centerX - (map.width * map.size) / 2;
    int startY = centerY - (map.height * map.size) / 2;

    rayAngle = player.angle - (FOV / 2);
    if (rayAngle < 0) rayAngle += 2 * PI;
    if (rayAngle > 2 * PI) rayAngle -= 2 * PI;

    for (rayIndex = 0; rayIndex < NUM_RAYS; ++rayIndex)
    {
        depthOfField = 0;
        float horizontalDistance = 1e6f;
        float horizontalX = player.posX;
        float horizontalY = player.posY;
        float aTan = -1.0f / tan(rayAngle);

        // Horizontal ray-grid intersection
        if (rayAngle > PI)
        {
            rayY = floor(player.posY / map.size) * map.size - 0.0001f;
            rayX = (player.posY - rayY) * aTan + player.posX;
            offsetY = -map.size;
            offsetX = -offsetY * aTan;
        }
        else if (rayAngle < PI)
        {
            rayY = floor(player.posY / map.size) * map.size + map.size;
            rayX = (player.posY - rayY) * aTan + player.posX;
            offsetY = map.size;
            offsetX = -offsetY * aTan;
        }
        else
        {
            rayX = player.posX;
            rayY = player.posY;
            depthOfField = std::max(map.width, map.height);
        }

        while (depthOfField < std::max(map.width, map.height))
        {
            mapX = (int)(rayX / map.size);
            mapY = (int)(rayY / map.size);
            mapPosition = mapY * map.width + mapX;

            if (mapX >= 0 && mapX < map.width && mapY >= 0 && mapY < map.height && map.map[mapPosition] > 0)
            {
                wallTypeHorizontal = map.map[mapPosition];
                horizontalX = rayX;
                horizontalY = rayY;
                horizontalDistance = Distance(player.posX, player.posY, horizontalX, horizontalY, rayAngle);
                depthOfField = std::max(map.width, map.height);
            }
            else
            {
                rayX += offsetX;
                rayY += offsetY;
                depthOfField++;
            }
        }

        // Vertical ray-grid intersection
        depthOfField = 0;
        float verticalDistance = 1e6f;
        float verticalX = player.posX;
        float verticalY = player.posY;
        float nTan = -tan(rayAngle);

        if (rayAngle < PI2 || rayAngle > PI3)
        {
            rayX = floor(player.posX / map.size) * map.size + map.size;
            rayY = (player.posX - rayX) * nTan + player.posY;
            offsetX = map.size;
            offsetY = -offsetX * nTan;
        }
        else if (rayAngle > PI2 && rayAngle < PI3)
        {
            rayX = floor(player.posX / map.size) * map.size - 0.0001f;
            rayY = (player.posX - rayX) * nTan + player.posY;
            offsetX = -map.size;
            offsetY = -offsetX * nTan;
        }
        else
        {
            rayX = player.posX;
            rayY = player.posY;
            depthOfField = std::max(map.width, map.height);
        }

        while (depthOfField < std::max(map.width, map.height))
        {
            mapX = (int)(rayX / map.size);
            mapY = (int)(rayY / map.size);
            mapPosition = mapY * map.width + mapX;

            if (mapX >= 0 && mapX < map.width && mapY >= 0 && mapY < map.height && map.map[mapPosition] > 0)
            {
                wallTypeVertical = map.map[mapPosition];
                verticalX = rayX;
                verticalY = rayY;
                verticalDistance = Distance(player.posX, player.posY, verticalX, verticalY, rayAngle);
                depthOfField = std::max(map.width, map.height);
            }
            else
            {
                rayX += offsetX;
                rayY += offsetY;
                depthOfField++;
            }
        }

        // Choose closer hit
        float finalDistance;
        if (verticalDistance < horizontalDistance)
        {
            shading = false;
            rayX = verticalX;
            rayY = verticalY;
            finalDistance = verticalDistance;

            glColor3f(0.9f, 0, 0);
            if (wallTypeVertical == 2) glColor3f(0, 0.9f, 0);
        }
        else
        {
            shading = true;
            rayX = horizontalX;
            rayY = horizontalY;
            finalDistance = horizontalDistance;

            glColor3f(0.5f, 0, 0);
            if (wallTypeHorizontal == 2) glColor3f(0, 0.5f, 0);
        }

        if (!render3D)
        {
            glLineWidth(3);
            glBegin(GL_LINES);
            glVertex2i(player.posX + startX, player.posY + startY);
            glVertex2i(rayX + startX, rayY + startY);
            glEnd();
        }
        else
        {
            Render3D(rayIndex, finalDistance, rayAngle,
                (verticalDistance < horizontalDistance) ? wallTypeVertical : wallTypeHorizontal,
                shading, windowWidth, windowHeight);
        }

        rayAngle += FOV / static_cast<float>(NUM_RAYS);
        rayAngle = fmod(rayAngle + 2 * PI, 2 * PI);
    }
}

float Distance(float startX, float startY, float endX, float endY, float angle)
{
    float deltaX = endX - startX;
    float deltaY = endY - startY;

    float euclideanDistance = sqrt(deltaX * deltaX + deltaY * deltaY);
    float correctedAngle = fmod(player.angle - angle + 2 * PI, 2 * PI);
    float adjustedDistance = euclideanDistance * cos(correctedAngle);

    return adjustedDistance;
}
