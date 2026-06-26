#pragma once

#include "types.h"

Bitboard rookTargets(int square, Bitboard allOccupancy, Bitboard ownOccupancy);
Bitboard knightTargets(int square, Bitboard allOccupancy, Bitboard ownOccupancy);
Bitboard bishopTargets(int square, Bitboard allOccupancy, Bitboard ownOccupancy);
Bitboard queenTargets(int square, Bitboard allOccupancy, Bitboard ownOccupancy);
Bitboard kingTargets(int square, Bitboard allOccupancy, Bitboard ownOccupancy);
Bitboard pawnTargets(int square, Bitboard allOccupancy, Bitboard ownOccupancy);