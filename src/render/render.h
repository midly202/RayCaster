#include "Graphics.hpp"  // IWYU pragma: keep

void Display(sf::RenderWindow& window);

void Init();

void DrawPauseMenu(sf::RenderWindow& window, const sf::Font& font);

void DrawPlayer(int windowWidth, int windowHeight);

void DrawMap(int windowWidth, int windowHeight);

void Render3D(int rayIndex, float distance, float rayAngle, int wallType, bool shading, int windowWidth, int windowHeight);

void CastRay(int windowWidth, int windowHeight);

float Distance(float startX, float startY, float endX, float endY, float angle);
