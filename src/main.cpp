#include "Graphics.hpp"  // IWYU pragma: keep
#include "Window.hpp"    // IWYU pragma: keep
#include "render.h"
#include "player.h"
#include "structs.h"
#include "arial.h"

Player player;
Map map;
sf::Font font;

bool render3D = true;
bool showPauseMenu = false;
bool shouldExit = false;

#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
    _In_     HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_     LPSTR     lpCmdLine,
    _In_     int       nCmdShow
)
#else
int main()
#endif
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "RayCaster - Midly", sf::Style::None, sf::ContextSettings(24));
    window.setVerticalSyncEnabled(true);

    Init();

    bool dragging = false;
    sf::Vector2i dragOffset;
    sf::Clock clock;

    bool mouseLocked = true;
    sf::Mouse::setPosition(sf::Vector2i(WIDTH / 2, HEIGHT / 2), window);
    window.setMouseCursorVisible(false);
    
    font.loadFromMemory(arial_ttf, arial_ttf_len);

    while (window.isOpen())
    {
        sf::Event event;
        float deltaTime = clock.restart().asSeconds();

        sf::Vector2i center = sf::Vector2i(WIDTH / 2, HEIGHT / 2);
        static bool firstMouse = true;
        static int lastMouseX = center.x;

        if (firstMouse) 
        {
            sf::Mouse::setPosition(center, window);
            firstMouse = false;
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::LostFocus)
            {
                mouseLocked = false;
                window.setMouseCursorVisible(true);
            }

            if (event.type == sf::Event::GainedFocus && !showPauseMenu)
            {
                mouseLocked = true;
                window.setMouseCursorVisible(false);
                sf::Mouse::setPosition(center, window);
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    mouseLocked = !mouseLocked;
                    showPauseMenu = !showPauseMenu;
                    window.setMouseCursorVisible(!mouseLocked);

                    if (mouseLocked)
                        sf::Mouse::setPosition(center, window);
                }
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (mousePos.y < 30)
                {
                    dragging = true;
                    dragOffset = mousePos;
                }
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                dragging = false;
            }
        }

        if (dragging)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition();
            window.setPosition(mousePos - dragOffset);
        }

        if (mouseLocked)
        {
            int mouseX = sf::Mouse::getPosition(window).x;
            int deltaX = mouseX - center.x;

            const float mouseSensitivity = 0.002f;
            player.angle += deltaX * mouseSensitivity;
            if (player.angle < 0) player.angle += 2 * PI;
            if (player.angle > 2 * PI) player.angle -= 2 * PI;
            player.dirX = cos(player.angle);
            player.dirY = sin(player.angle);

            sf::Mouse::setPosition(center, window);
        }

        PlayerMove(deltaTime);
        Display(window);
        window.display();

        if (shouldExit)
            window.close();
    }

    return 0;
}