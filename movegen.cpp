#include "movegen.h"
#include "board.h"     // makeMove, checkIfSquareOccupied, the bitboards
#include <iostream>
#include <cstdlib>     // abs
#include <algorithm>   // std::min, std::max

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

Bitboard pawnTargets(int square, Bitboard allOccupancy, Bitboard ownOccupancy, bool isWhite)
{
    Bitboard targets = 0ULL;

    int fromRank = square / 8;
    int fromFile = square % 8;

    int dir = isWhite ? +1 : -1;
    int startRank = isWhite ? 1 : 6;

	Bitboard enemyOccupancy = allOccupancy &~ ownOccupancy;

    const int fileSteps[2] = { -1, +1 };
    for (int i = 0; i < 2; ++i)
    {
        int rank = fromRank + dir;
        int file = fromFile + fileSteps[i];

        if (rank >= 0 && rank <= 7 && file >= 0 && file <= 7)
        {
            Bitboard targetBit = 1ULL << (rank * 8 + file);

            if (enemyOccupancy & targetBit)   // enemy REQUIRED — empty is not enough
                targets |= targetBit;
        }
    }

    int pushRank = fromRank + dir;
    if (pushRank >= 0 && pushRank <= 7)
    {
        Bitboard pushBit = 1ULL << (pushRank * 8 + fromFile);

        if (!(allOccupancy & pushBit))
        {
            targets |= pushBit;

            if (fromRank == startRank)
            {
                Bitboard doubleBit = 1ULL << ((fromRank + 2 * dir) * 8 + fromFile);

                if (!(allOccupancy & doubleBit))
                    targets |= doubleBit;
            }
        }
    }

    return targets;
}