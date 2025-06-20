#include "Graphics.hpp"  // IWYU pragma: keep
#include "Window.hpp"    // IWYU pragma: keep
#include "render.h"

#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else
int main()
#endif
{
    // Create SFML window with OpenGL context
    sf::Window window(sf::VideoMode(1024, 512), "RayCaster - Midly", sf::Style::Default, sf::ContextSettings(24));
    window.setVerticalSyncEnabled(true);

    // Init GL
    init();

    // Main loop
    while (window.isOpen())
    {
        // Event polling
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Render
        display();

        // Swap buffers
        window.display();
    }

    return 0;
}
