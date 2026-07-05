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
Bitboard white_occupancy = white_pawns | white_rooks | white_knights | white_bishops | white_queen | white_king;
Bitboard black_occupancy = black_pawns | black_rooks | black_knights | black_bishops | black_queen | black_king;
Bitboard all_occupancy = white_occupancy | black_occupancy;

std::vector<Piece> capturedByWhite;
std::vector<Piece> capturedByBlack;

void makeMove(int fromSquare, int toSquare)
{
    // 1. Look everything up BEFORE touching anything
    Piece mover = pieceAt(fromSquare);
    Piece victim = pieceAt(toSquare);

    // 2. Handle the capture first
    if (victim != EMPTY)
    {
        boardFor(victim) &= ~(1ULL << toSquare);

        if (victim >= BLACK_PAWN)           // black victim -> white captured it
            capturedByWhite.push_back(victim);
        else
            capturedByBlack.push_back(victim);
    }

    // 3. Move the attacker — your original two lines, unchanged
    Bitboard& moverBoard = boardFor(mover);
    moverBoard &= ~(1ULL << fromSquare);
    moverBoard |= (1ULL << toSquare);

    // 4. Keep the world honest
    refreshOccupancy();
}

bool checkIfSquareOccupied(Bitboard board, int square)
{
    return (board >> square) & 1ULL;
}

void refreshOccupancy()
{
    white_occupancy = white_pawns | white_rooks | white_knights | white_bishops | white_queen | white_king;
    black_occupancy = black_pawns | black_rooks | black_knights | black_bishops | black_queen | black_king;
    all_occupancy = white_occupancy | black_occupancy;
}

Piece pieceAt(int square)
{
    Bitboard squareBit = 1ULL << square;

    if (white_pawns   & squareBit) return WHITE_PAWN;
    if (white_knights & squareBit) return WHITE_KNIGHT;
    if (white_bishops & squareBit) return WHITE_BISHOP;
    if (white_rooks   & squareBit) return WHITE_ROOK;
    if (white_queen   & squareBit) return WHITE_QUEEN;
    if (white_king    & squareBit) return WHITE_KING;

    if (black_pawns   & squareBit) return BLACK_PAWN;
    if (black_knights & squareBit) return BLACK_KNIGHT;
    if (black_bishops & squareBit) return BLACK_BISHOP;
    if (black_rooks   & squareBit) return BLACK_ROOK;
    if (black_queen   & squareBit) return BLACK_QUEEN;
    if (black_king    & squareBit) return BLACK_KING;

    return EMPTY;
}

Bitboard& boardFor(Piece piece)
{
    switch (piece)
    {
    case WHITE_PAWN:   return white_pawns;
    case WHITE_KNIGHT: return white_knights;
    case WHITE_BISHOP: return white_bishops;
    case WHITE_ROOK:   return white_rooks;
    case WHITE_QUEEN:  return white_queen;
    case WHITE_KING:   return white_king;

    case BLACK_PAWN:   return black_pawns;
    case BLACK_KNIGHT: return black_knights;
    case BLACK_BISHOP: return black_bishops;
    case BLACK_ROOK:   return black_rooks;
    case BLACK_QUEEN:  return black_queen;
    case BLACK_KING:   return black_king;

    default:           return white_pawns; // EMPTY should never be asked — see note
    }
}