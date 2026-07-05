#include "board.h"
#include "display.h"
#include "movegen.h"
#include <iostream>
#include <string>

// Converts "e2" -> square index, or -1 if the text is invalid
int parseSquare(char fileChar, char rankChar)
{
	if (fileChar < 'a' || fileChar > 'h') return -1;
	if (rankChar < '1' || rankChar > '8') return -1;

	int file = fileChar - 'a';
	int rank = rankChar - '1';
	return rank * 8 + file;
}

int main()
{
	bool isWhiteTurn = true;
	std::string input;

	refreshOccupancy();

	while (true)
	{
		updateVisualBoard();
		printVisualBoard();
		std::cout << std::endl;

		std::cout << (isWhiteTurn ? "White" : "Black") << " to move (e.g. e2e4, q to quit): ";
		std::cin >> input;

		if (input == "q")
			break;

		if (input.length() != 4)
		{
			std::cout << "Bad format - four characters like e2e4." << std::endl;
			continue;
		}

		int fromSquare = parseSquare(input[0], input[1]);
		int toSquare = parseSquare(input[2], input[3]);

		if (fromSquare == -1 || toSquare == -1)
		{
			std::cout << "Bad squares - files a-h, ranks 1-8." << std::endl;
			continue;
		}

		// Gate 1: is there a piece at all?
		Piece mover = pieceAt(fromSquare);
		if (mover == EMPTY)
		{
			std::cout << "No piece on that square." << std::endl;
			continue;
		}

		// Gate 2: is it yours?
		bool moverIsWhite = (mover >= WHITE_PAWN && mover <= WHITE_KING);
		if (moverIsWhite != isWhiteTurn)
		{
			std::cout << "That piece isn't yours." << std::endl;
			continue;
		}

		// Gate 3: can it actually go there?
		if (!(targetsFor(mover, fromSquare) & (1ULL << toSquare)))
		{
			std::cout << "That piece can't move there." << std::endl;
			continue;
		}

		makeMove(fromSquare, toSquare);
		isWhiteTurn = !isWhiteTurn;
	}

	return 0;
}