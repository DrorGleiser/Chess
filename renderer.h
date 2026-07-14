#pragma once
#include <SFML/Graphics.hpp>
#include "types.h"

class Renderer
{
public:
    static const int TILE = 100;

    Renderer();  // loads textures once
    void draw(sf::RenderWindow& window, const Piece mailbox[64],
        int selectedSquare = -1, Bitboard targets = 0ULL);

private:
    void drawHighlights(sf::RenderWindow& window, int selectedSquare, Bitboard targets);
    void drawSquares(sf::RenderWindow& window);
    void drawPieces(sf::RenderWindow& window, const Piece mailbox[64]);

    sf::Texture pieceTextures[13];
};