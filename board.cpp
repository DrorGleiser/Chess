#include "board.h"

// These are the single definitions (with values) that board.h promised exist.
Bitboard white_pawns = 0x000000000000FF00ULL; // rank 2 — bits 8-15
Bitboard white_rooks = 0x0000000000000081ULL; // a1 and h1 — bits 0 and 7
Bitboard white_knights = 0x0000000000000042ULL; // b1 and g1 — bits 1 and 6
Bitboard white_bishops = 0x0000000000000024ULL; // c1 and f1 — bits 2 and 5
Bitboard white_queen = 0x0000000000000008ULL; // d1 — bit 3
Bitboard white_king = 0x0000000000000010ULL; // e1 — bit 4

Bitboard black_pawns = 0x00FF000000000000ULL; // rank 7 — bits 48-55
Bitboard black_rooks = 0x8100000000000000ULL; // a8 and h8 — bits 56 and 63
Bitboard black_knights = 0x4200000000000000ULL; // b8 and g8 — bits 57 and 62
Bitboard black_bishops = 0x2400000000000000ULL; // c8 and f8 — bits 58 and 61
Bitboard black_queen = 0x0800000000000000ULL; // d8 — bit 59
Bitboard black_king = 0x1000000000000000ULL; // e8 — bit 60

// NOTE: computed once at startup, like before. These go stale after a move until
// you add a recompute step — that's the occupancy fix from the review, left for you.
Bitboard white_ocuupency = white_pawns | white_rooks | white_knights | white_bishops | white_queen | white_king;
Bitboard black_ocuupency = black_pawns | black_rooks | black_knights | black_bishops | black_queen | black_king;
Bitboard all_occupency = white_ocuupency | black_ocuupency;

void makeMove(Bitboard& board, int fromSquare, int toSquare)
{
    board &= ~(1ULL << fromSquare);
    board |= (1ULL << toSquare);
}

bool checkIfSquareOccupied(Bitboard board, int square)
{
    return (board >> square) & 1ULL;
}
