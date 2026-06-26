#pragma once

#include "types.h"

enum visualPiece
{
    EMPTY_SQUARE = '.',
    WHITE_PAWN_SQUARE = 'P',
    WHITE_KNIGHT_SQUARE = 'N',
    WHITE_BISHOP_SQUARE = 'B',
    WHITE_ROOK_SQUARE = 'R',
    WHITE_QUEEN_SQUARE = 'Q',
    WHITE_KING_SQUARE = 'K',
    BLACK_PAWN_SQUARE = 'p',
    BLACK_KNIGHT_SQUARE = 'n',
    BLACK_BISHOP_SQUARE = 'b',
    BLACK_ROOK_SQUARE = 'r',
    BLACK_QUEEN_SQUARE = 'q',
    BLACK_KING_SQUARE = 'k'
};

void updateVisualBoard();
void printVisualBoard();
void printBitboard(Bitboard bb);
