#include <SFML/Graphics.hpp>

const int TILE = 100; // 800px window / 8

void drawBoard(sf::RenderWindow& window)
{
    sf::RectangleShape square({ TILE, TILE });   // ONE shape, reused 64 times

    for (int rank = 0; rank < 8; ++rank)
    {
        for (int file = 0; file < 8; ++file)
        {
            bool isDark = ((rank + file) % 2 == 0);
            square.setFillColor(isDark ? sf::Color(118, 150, 86)     // green
                : sf::Color(238, 238, 210));  // cream

            square.setPosition({ float(file * TILE), float((7 - rank) * TILE) });
            window.draw(square);
        }
    }
}
