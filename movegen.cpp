#include "movegen.h"
#include "board.h"     // makeMove, checkIfSquareOccupied, the bitboards
#include <iostream>
#include <cstdlib>     // abs
#include <algorithm>   // std::min, std::max

bool checkIfRookPathClear(Bitboard board, int fromSquare, int toSquare)
{
    int fromRank = fromSquare / 8;
    int fromFile = fromSquare % 8;
    int toRank = toSquare / 8;
    int toFile = toSquare % 8;

    if (fromRank == toRank)
    {
        int startFile = std::min(fromFile, toFile) + 1;
        int endFile = std::max(fromFile, toFile);
        for (int file = startFile; file < endFile; ++file)
        {
            int square = fromRank * 8 + file;
            if (checkIfSquareOccupied(board, square))
                return false;
        }
    }

    else if (fromFile == toFile)
    {
        int startRank = std::min(fromRank, toRank) + 1;
        int endRank = std::max(fromRank, toRank);
        for (int rank = startRank; rank < endRank; ++rank)
        {
            int square = rank * 8 + fromFile;
            if (checkIfSquareOccupied(board, square))
                return false;
        }
    }
    else
    {
        return false; // Not a valid rook move
    }
    return true; // Path is clear
}

bool checkIfBishopPathClear(Bitboard board, int fromSquare, int toSquare)
{
    int fromRank = fromSquare / 8;
    int fromFile = fromSquare % 8;
    int toRank = toSquare / 8;
    int toFile = toSquare % 8;

    if (abs(toRank - fromRank) != abs(toFile - fromFile))
        return false; // Not a valid bishop move

    int rankStep = (toRank > fromRank) ? 1 : -1;
    int fileStep = (toFile > fromFile) ? 1 : -1;
    int currentRank = fromRank + rankStep;
    int currentFile = fromFile + fileStep;

    while (currentRank != toRank && currentFile != toFile)
    {
        int square = currentRank * 8 + currentFile;
        if (checkIfSquareOccupied(board, square))
            return false; // Path is blocked
        currentRank += rankStep;
        currentFile += fileStep;
    }
    return true; // Path is clear
}

bool checkIfQueenPathClear(Bitboard board, int fromSquare, int toSquare)
{
    return checkIfRookPathClear(board, fromSquare, toSquare) || checkIfBishopPathClear(board, fromSquare, toSquare);
}

bool checkIfPawnPathClear(Bitboard board, int fromSquare, int toSquare)
{
    int fromRank = fromSquare / 8;
    int fromFile = fromSquare % 8;
    int toRank = toSquare / 8;
    int toFile = toSquare % 8;

    if (fromFile == toFile)
    {
        if (toRank == fromRank + 1 || (fromRank == 1 && toRank == fromRank + 2))
        {
            return !checkIfSquareOccupied(board, toSquare);
        }
    }

    else if (abs(toFile - fromFile) == 1 && toRank == fromRank + 1)
    {
        return checkIfSquareOccupied(board, toSquare);
    }
    return false; // Invalid pawn move
}

bool checkIfKingPathClear(Bitboard board, int fromSquare, int toSquare)
{
    int fromRank = fromSquare / 8;
    int fromFile = fromSquare % 8;
    int toRank = toSquare / 8;
    int toFile = toSquare % 8;
    if (abs(toRank - fromRank) <= 1 && abs(toFile - fromFile) <= 1)
    {
        return !checkIfSquareOccupied(board, toSquare);
    }
    return false; // Invalid king move
}

void checkRookMovement(Bitboard& board, int fromSquare, int toSquare)
{
    int fromRank = fromSquare / 8;
    int fromFile = fromSquare % 8;
    int toRank = toSquare / 8;
    int toFile = toSquare % 8;
    if (fromRank == toRank || fromFile == toFile)
    {
        makeMove(board, fromSquare, toSquare);
    }
    else
    {
        std::cout << "Invalid move for a rook!" << std::endl;
    }
}

void checkKnightMovement(Bitboard& board, int fromSquare, int toSquare)
{
    int fromRank = fromSquare / 8;
    int fromFile = fromSquare % 8;
    int toRank = toSquare / 8;
    int toFile = toSquare % 8;
    int rankDiff = abs(toRank - fromRank);
    int fileDiff = abs(toFile - fromFile);
    if ((rankDiff == 2 && fileDiff == 1) || (rankDiff == 1 && fileDiff == 2))
    {
        makeMove(board, fromSquare, toSquare);
    }
    else
    {
        std::cout << "Invalid move for a knight!" << std::endl;
    }
}

void checkBishopMovement(Bitboard& board, int fromSquare, int toSquare)
{
    int fromRank = fromSquare / 8;
    int fromFile = fromSquare % 8;
    int toRank = toSquare / 8;
    int toFile = toSquare % 8;
    if (abs(toRank - fromRank) == abs(toFile - fromFile))
    {
        makeMove(board, fromSquare, toSquare);
    }
    else
    {
        std::cout << "Invalid move for a bishop!" << std::endl;
    }
}

void checkQueenMovement(Bitboard& board, int fromSquare, int toSquare)
{
    int fromRank = fromSquare / 8;
    int fromFile = fromSquare % 8;
    int toRank = toSquare / 8;
    int toFile = toSquare % 8;
    if (fromRank == toRank || fromFile == toFile || abs(toRank - fromRank) == abs(toFile - fromFile))
    {
        makeMove(board, fromSquare, toSquare);
    }
    else
    {
        std::cout << "Invalid move for a queen!" << std::endl;
    }
}

void checkKingMovement(Bitboard& board, int fromSquare, int toSquare)
{
    int fromRank = fromSquare / 8;
    int fromFile = fromSquare % 8;
    int toRank = toSquare / 8;
    int toFile = toSquare % 8;
    if (abs(toRank - fromRank) <= 1 && abs(toFile - fromFile) <= 1)
    {
        makeMove(board, fromSquare, toSquare);
    }
    else
    {
        std::cout << "Invalid move for a king!" << std::endl;
    }
}

void checkPawnMovement(Bitboard& board, int fromSquare, int toSquare)
{
    int fromRank = fromSquare / 8;
    int fromFile = fromSquare % 8;
    int toRank = toSquare / 8;
    int toFile = toSquare % 8;
    if (fromFile == toFile && (abs(toRank - fromRank) == 1 || (fromRank == 1 && abs(toRank - fromRank) == 2)))
    {
        makeMove(board, fromSquare, toSquare);
    }
    else
    {
        std::cout << "Invalid move for a pawn!" << std::endl;
    }
}

Bitboard rookTargets(int square, Bitboard allOccupancy, Bitboard ownOccupancy)
{
    Bitboard targets = 0ULL;

    int fromRank = square / 8;
    int fromFile = square % 8;

    // The four rook directions, as (rank step, file step):
    // north, south, east, west.
    const int rankSteps[4] = { +1, -1,  0,  0 };
    const int fileSteps[4] = { 0,  0, +1, -1 };

    for (int dir = 0; dir < 4; ++dir)
    {
        int rank = fromRank + rankSteps[dir];
        int file = fromFile + fileSteps[dir];

        // Walk outward until a step leaves the board. Bounding BOTH rank and
        // file is what makes east/west wrap-safe: stepping off the h-file
        // gives file == 8, which fails the test instead of rolling onto the
        // next rank the way a raw +1 bit shift would.
        while (rank >= 0 && rank <= 7 && file >= 0 && file <= 7)
        {
            int target = rank * 8 + file;
            Bitboard targetBit = 1ULL << target;

            if (allOccupancy & targetBit)         // square is blocked
            {
                if (!(ownOccupancy & targetBit))  // blocker is an enemy
                    targets |= targetBit;          // include the capture
                break;                             // ray stops either way
            }

            targets |= targetBit;                  // empty: add and keep walking
            rank += rankSteps[dir];
            file += fileSteps[dir];
        }
    }

    return targets;
}

Bitboard knightTargets(int square, Bitboard allOccupancy, Bitboard ownOccupancy)
{
	Bitboard targets = 0ULL;
	int fromRank = square / 8;
	int fromFile = square % 8;
	// The eight knight moves, as (rank step, file step):
	const int rankSteps[8] = { +2, +2, +1, -1, -2, -2, -1, +1 };
	const int fileSteps[8] = { +1, -1, -2, -2, -1, +1, +2, +2 };

	for (int i = 0; i < 8; ++i)
	{
		int rank = fromRank + rankSteps[i];
		int file = fromFile + fileSteps[i];

		if (rank >= 0 && rank <= 7 && file >= 0 && file <= 7)
		{
			int target = rank * 8 + file;
			Bitboard targetBit = 1ULL << target;
			if (!(ownOccupancy & targetBit)) // not blocked by own piece
				targets |= targetBit;
		}
	}
	return targets;
}

Bitboard bishopTargets(int square, Bitboard allOccupancy, Bitboard ownOccupancy)
{
    Bitboard targets = 0ULL;

    int fromRank = square / 8;
    int fromFile = square % 8;

    const int rankSteps[4] = {+1, -1, +1, -1 };
    const int fileSteps[4] = { +1, -1, -1, +1 };

    for (int dir = 0; dir < 4; ++dir)
    {
        int rank = fromRank + rankSteps[dir];
        int file = fromFile + fileSteps[dir];

        while (rank >= 0 && rank <= 7 && file >= 0 && file <= 7)
        {
            int target = rank * 8 + file;
            Bitboard targetBit = 1ULL << target;

            if (allOccupancy & targetBit)         // square is blocked
            {
                if (!(ownOccupancy & targetBit))  // blocker is an enemy
                    targets |= targetBit;          // include the capture
                break;                             // ray stops either way
            }

            targets |= targetBit;                  // empty: add and keep walking
            rank += rankSteps[dir];
            file += fileSteps[dir];
        }
    }

    return targets;
}

Bitboard queenTargets(int square, Bitboard allOccupancy, Bitboard ownOccupancy)
{
    return rookTargets(square, allOccupancy, ownOccupancy) | bishopTargets(square, allOccupancy, ownOccupancy);
}

Bitboard kingTargets(int square, Bitboard allOccupancy, Bitboard ownOccupancy)
{
    Bitboard targets = 0ULL;

    int fromRank = square / 8;
    int fromFile = square % 8;

    const int rankSteps[8] = { +1, +1, +1, -1, -1, -1,  0,  0};
    const int fileSteps[8] = { +1, -1,  0, +1, -1,  0, +1, -1 };

    for (int dir = 0; dir < 8; ++dir)
    {
        int rank = fromRank + rankSteps[dir];
        int file = fromFile + fileSteps[dir];

        if (rank >= 0 && rank <= 7 && file >= 0 && file <= 7)
        {
            int target = rank * 8 + file;
            Bitboard targetBit = 1ULL << target;

            if (!(ownOccupancy & targetBit)) 
                targets |= targetBit;          
        }
    }

    return targets;
}

Bitboard pawnTargets(int square, Bitboard allOccupancy, Bitboard ownOccupancy)
{
    Bitboard targets = 0ULL;

    int fromRank = square / 8;
    int fromFile = square % 8;



    return targets;
}