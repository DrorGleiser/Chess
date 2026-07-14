#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "renderer.h"
#include "mailbox.h"
#include "board.h"
#include "movegen.h"

int returnSquareFromClick(int x, int y)
{
    int file = x / 100;            // TODO: use shared TILE constant
    int rank = 7 - (y / 100);
    if (file < 0 || file > 7 || rank < 0 || rank > 7)
        return -1;
    return rank * 8 + file;
}

// 27 -> "d4", for readable logs
std::string squareName(int square)
{
    if (square == -1) return "none";
    std::string name;
    name += char('a' + square % 8);
    name += char('1' + square / 8);
    return name;
}

const char* pieceName(Piece p)
{
    const char* names[13] = { "empty",
        "white pawn", "white knight", "white bishop",
        "white rook", "white queen",  "white king",
        "black pawn", "black knight", "black bishop",
        "black rook", "black queen",  "black king" };
    return names[p];
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "Chess - White to move");

    Renderer renderer;

    Piece mailbox[64];
    bool isWhiteTurn = true;
    int selectedSquare = -1;

    refreshOccupancy();
    toMailbox(mailbox);
    std::cout << "[init] occupancy refreshed, game on. White to move.\n";

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* click = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (click->button != sf::Mouse::Button::Left)
                    continue;

                int clicked = returnSquareFromClick(click->position.x, click->position.y);

                std::cout << "[click] pixel (" << click->position.x << ", "
                    << click->position.y << ") -> " << squareName(clicked);

                if (clicked == -1)
                {
                    std::cout << " (outside board, ignored)\n";
                    continue;
                }

                Piece clickedPiece = pieceAt(clicked);
                std::cout << ", holds: " << pieceName(clickedPiece) << "\n";

                bool clickedIsOwn = clickedPiece != EMPTY &&
                    (clickedPiece <= WHITE_KING) == isWhiteTurn;

                if (selectedSquare == -1)
                {
                    if (clickedIsOwn)
                    {
                        selectedSquare = clicked;
                        Bitboard targets = targetsFor(clickedPiece, clicked);
                        std::cout << "[select] " << pieceName(clickedPiece)
                            << " on " << squareName(clicked)
                            << ", targets: 0x" << std::hex << targets << std::dec
                            << "\n";
                    }
                    else
                        std::cout << "[ignore] not your piece / empty square\n";
                }
                else
                {
                    Piece mover = pieceAt(selectedSquare);

                    if (targetsFor(mover, selectedSquare) & (1ULL << clicked))
                    {
                        Piece victim = pieceAt(clicked);
                        std::cout << "[move] " << pieceName(mover) << " "
                            << squareName(selectedSquare) << " -> "
                            << squareName(clicked);
                        if (victim != EMPTY)
                            std::cout << ", captures " << pieceName(victim);
                        std::cout << "\n";

                        makeMove(selectedSquare, clicked);
                        isWhiteTurn = !isWhiteTurn;
                        toMailbox(mailbox);
                        window.setTitle(isWhiteTurn ? "Chess - White to move"
                            : "Chess - Black to move");
                        selectedSquare = -1;
                        std::cout << "[turn] " << (isWhiteTurn ? "white" : "black")
                            << " to move\n";
                    }
                    else if (clickedIsOwn)
                    {
                        selectedSquare = clicked;
                        std::cout << "[reselect] switched to " << pieceName(clickedPiece)
                            << " on " << squareName(clicked) << "\n";
                    }
                    else
                    {
                        selectedSquare = -1;
                        std::cout << "[cancel] " << squareName(clicked)
                            << " not a legal target, selection cleared\n";
                    }
                }
            }
        }

        window.clear();
        Bitboard targets = (selectedSquare != -1)
            ? targetsFor(pieceAt(selectedSquare), selectedSquare)
            : 0ULL;
        renderer.draw(window, mailbox, selectedSquare, targets);
        window.display();
    }
    return 0;
}