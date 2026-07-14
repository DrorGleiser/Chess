#include "renderer.h"
#include <iostream>

Renderer::Renderer()
{
    const char* files[13] = {
        nullptr,
        "pieces/wP.png", "pieces/wN.png", "pieces/wB.png",
        "pieces/wR.png", "pieces/wQ.png", "pieces/wK.png",
        "pieces/bP.png", "pieces/bN.png", "pieces/bB.png",
        "pieces/bR.png", "pieces/bQ.png", "pieces/bK.png"
    };

    for (int p = 1; p <= 12; ++p)
        if (!pieceTextures[p].loadFromFile(files[p]))
            std::cout << "FAILED to load " << files[p] << '\n';

    for (int p = 1; p <= 12; ++p)
        pieceTextures[p].setSmooth(true);   // nicer scaling
}

void Renderer::draw(sf::RenderWindow& window, const Piece mailbox[64],
    int selectedSquare, Bitboard targets)
{
    drawSquares(window);
    drawHighlights(window, selectedSquare, targets); 
    drawPieces(window, mailbox);
}

void Renderer::drawHighlights(sf::RenderWindow& window, int selectedSquare, Bitboard targets)
{
    if (selectedSquare == -1) return;

    // yellow overlay on the picked square
    sf::RectangleShape overlay({ float(TILE), float(TILE) });
    overlay.setFillColor(sf::Color(246, 234, 105, 150));   // alpha 150 = translucent
    overlay.setPosition({ float(selectedSquare % 8 * TILE),
                          float((7 - selectedSquare / 8) * TILE) });
    window.draw(overlay);

    // a dot on every set bit of the targets bitboard
    const float r = TILE / 6.f;
    sf::CircleShape dot(r);
    dot.setFillColor(sf::Color(0, 0, 0, 70));

    for (int sq = 0; sq < 64; ++sq)
    {
        if (!(targets & (1ULL << sq)))
            continue;

        dot.setPosition({ sq % 8 * TILE + TILE / 2.f - r,
                          (7 - sq / 8) * TILE + TILE / 2.f - r });
        window.draw(dot);
    }
}

void Renderer::drawSquares(sf::RenderWindow& window)
{
    sf::RectangleShape square({ float(TILE), float(TILE) });

    for (int rank = 0; rank < 8; ++rank)
    {
        for (int file = 0; file < 8; ++file)
        {
            bool isDark = ((rank + file) % 2 == 0);
            square.setFillColor(isDark ? sf::Color(118, 150, 86)
                : sf::Color(238, 238, 210));

            square.setPosition({ float(file * TILE), float((7 - rank) * TILE) });
            window.draw(square);
        }
    }
}

void Renderer::drawPieces(sf::RenderWindow& window, const Piece mailbox[64])
{
    for (int sq = 0; sq < 64; ++sq)
    {
        if (mailbox[sq] == EMPTY) continue;

        int file = sq % 8;
        int rank = sq / 8;

        sf::Sprite sprite(pieceTextures[mailbox[sq]]);
        sprite.setScale({ float(TILE) / 256.f, float(TILE) / 256.f });
        sprite.setPosition({ float(file * TILE), float((7 - rank) * TILE) });
        window.draw(sprite);
    }
}