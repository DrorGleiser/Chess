#pragma once

#include "types.h"

// The 12 piece bitboards. DECLARED here (extern, no value), DEFINED once in board.cpp.
// Anyone who includes board.h can read/write these; there is still only one of each.
extern Bitboard white_pawns;
extern Bitboard white_rooks;
extern Bitboard white_knights;
extern Bitboard white_bishops;
extern Bitboard white_queen;
extern Bitboard white_king;

extern Bitboard black_pawns;
extern Bitboard black_rooks;
extern Bitboard black_knights;
extern Bitboard black_bishops;
extern Bitboard black_queen;
extern Bitboard black_king;

// Derived occupancy (also defined in board.cpp).
extern Bitboard white_ocuupency;
extern Bitboard black_ocuupency;
extern Bitboard all_occupency;

// Board primitives.
void makeMove(Bitboard& board, int fromSquare, int toSquare);
bool checkIfSquareOccupied(Bitboard board, int square);
