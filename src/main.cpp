#include "Graphics.hpp"  // IWYU pragma: keep
#include "Window.hpp"    // IWYU pragma: keep
#include "render.h"
#include "player.h"

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
    sf::Window window(sf::VideoMode(800, 600), "RayCaster - Midly", sf::Style::Close, sf::ContextSettings(24));
    window.setVerticalSyncEnabled(true);

    Init();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
                PlayerMove(event.key.code);
        }

        Display();
        window.display();
    }

    return 0;
}
