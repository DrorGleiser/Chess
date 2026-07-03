#include <SFML/Graphics.hpp>
#include "renderer.cpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "Chess");
    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
            if (event->is<sf::Event::Closed>())
                window.close();

        window.clear();
        drawBoard(window);
        window.display();
    }
    return 0;
}