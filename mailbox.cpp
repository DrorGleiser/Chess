#include "mailbox.h"
#include "board.h"

void toMailbox(Piece out[64])
{
    for (int sq = 0; sq < 64; ++sq)
        out[sq] = pieceAt(sq);
}