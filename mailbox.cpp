#include "mailbox.h"
#include "board.h"

void toMailbox(Piece out[64])
{
    for (int sq = 0; sq < 64; ++sq)
        out[sq] = EMPTY;

    for (int sq = 0; sq < 64; ++sq)
    {
        Bitboard mask = 1ULL << sq;

        if (white_pawns & mask) out[sq] = WHITE_PAWN;
        else if (white_knights & mask) out[sq] = WHITE_KNIGHT;
        else if (white_bishops & mask) out[sq] = WHITE_BISHOP;
        else if (white_rooks & mask) out[sq] = WHITE_ROOK;
        else if (white_queen & mask) out[sq] = WHITE_QUEEN;
        else if (white_king & mask) out[sq] = WHITE_KING;
        else if (black_pawns & mask) out[sq] = BLACK_PAWN;
        else if (black_knights & mask) out[sq] = BLACK_KNIGHT;
        else if (black_bishops & mask) out[sq] = BLACK_BISHOP;
        else if (black_rooks & mask) out[sq] = BLACK_ROOK;
        else if (black_queen & mask) out[sq] = BLACK_QUEEN;
        else if (black_king & mask) out[sq] = BLACK_KING;
    }
}