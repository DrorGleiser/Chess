#pragma once
#include <SFML/Graphics.hpp>
#include "types.h"

class Renderer
{
public:
    Renderer();  // loads textures once
    void draw(sf::RenderWindow& window, const Piece mailbox[64]);

private:
    void drawSquares(sf::RenderWindow& window);
    void drawPieces(sf::RenderWindow& window, const Piece mailbox[64]);

    sf::Texture pieceTextures[13];
    static const int TILE = 100;
};