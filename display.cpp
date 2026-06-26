#include "display.h"
#include "board.h"   // needs the piece bitboards to read the position
#include <iostream>

// Private to this file now — nothing else touches it, so it stays out of the header.
char VisualBoard[64];

void updateVisualBoard()
{
    for (int square = 0; square < 64; ++square)
    {
        if ((white_pawns >> square) & 1ULL) VisualBoard[square] = WHITE_PAWN_SQUARE;
        else if ((white_rooks >> square) & 1ULL) VisualBoard[square] = WHITE_ROOK_SQUARE;
        else if ((white_knights >> square) & 1ULL) VisualBoard[square] = WHITE_KNIGHT_SQUARE;
        else if ((white_bishops >> square) & 1ULL) VisualBoard[square] = WHITE_BISHOP_SQUARE;
        else if ((white_queen >> square) & 1ULL) VisualBoard[square] = WHITE_QUEEN_SQUARE;
        else if ((white_king >> square) & 1ULL) VisualBoard[square] = WHITE_KING_SQUARE;
        else if ((black_pawns >> square) & 1ULL) VisualBoard[square] = BLACK_PAWN_SQUARE;
        else if ((black_rooks >> square) & 1ULL) VisualBoard[square] = BLACK_ROOK_SQUARE;
        else if ((black_knights >> square) & 1ULL) VisualBoard[square] = BLACK_KNIGHT_SQUARE;
        else if ((black_bishops >> square) & 1ULL) VisualBoard[square] = BLACK_BISHOP_SQUARE;
        else if ((black_queen >> square) & 1ULL) VisualBoard[square] = BLACK_QUEEN_SQUARE;
        else if ((black_king >> square) & 1ULL) VisualBoard[square] = BLACK_KING_SQUARE;
        else VisualBoard[square] = EMPTY_SQUARE;
    }
}

void printVisualBoard()
{
    for (int rank = 7; rank >= 0; --rank)
    {
        for (int file = 0; file < 8; ++file)
        {
            int square = rank * 8 + file;
            std::cout << VisualBoard[square] << " ";
        }
        std::cout << std::endl;
    }
}

void printBitboard(Bitboard bb)
{
    for (int rank = 7; rank >= 0; --rank)
    {
        for (int file = 0; file < 8; ++file)
        {
            int square = rank * 8 + file;
            std::cout << ((bb >> square) & 1ULL);
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}
