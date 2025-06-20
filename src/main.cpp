#include <iostream>
#include "Graphics.hpp"
#include "Window.hpp"

#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else
int main()
#endif
{

    sf::RenderWindow window(sf::VideoMode(1280, 720), "RayCaster - Midly", sf::Style::Default);
    window.setFramerateLimit(144);
    int windowStyle = 0;

    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
        }

        if (e.type == sf::Event::KeyPressed && e.key.scancode == sf::Keyboard::Scan::Scancode::F11)
        {
            windowStyle = (windowStyle + 1) % 3;  // Increment and reset after 2.

            window.close();
            switch (windowStyle)
            {
            case 0:
                window.create(sf::VideoMode(1280, 720), "RayCaster, windowed", sf::Style::Default);
                break;
            case 1:
                window.create(sf::VideoMode(1920, 1080), "RayCaster, windowed fullscreen", sf::Style::None);
                break;
            case 2:
                window.create(sf::VideoMode(1920, 1080), "RayCaster, fullscreen", sf::Style::Fullscreen);
                break;
            }
        }
    }

    return 0;
}