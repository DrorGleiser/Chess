#include <stdio.h>
#include <iostream>

using Bitboard = uint64_t;

enum Square
{
    a1, b1, c1, d1, e1, f1, g1, h1,  // rank 1 — bits 0-7
    a2, b2, c2, d2, e2, f2, g2, h2,  // rank 2 — bits 8-15
    a3, b3, c3, d3, e3, f3, g3, h3,  // rank 3 — bits 16-23
    a4, b4, c4, d4, e4, f4, g4, h4,  // rank 4 — bits 24-31
    a5, b5, c5, d5, e5, f5, g5, h5,  // rank 5 — bits 32-39
    a6, b6, c6, d6, e6, f6, g6, h6,  // rank 6 — bits 40-47
    a7, b7, c7, d7, e7, f7, g7, h7,  // rank 7 — bits 48-55
    a8, b8, c8, d8, e8, f8, g8, h8,  // rank 8 — bits 56-63
};

enum Piece
{
	EMPTY,         // 0
    WHITE_PAWN,    // 1
    WHITE_KNIGHT,  // 2
    WHITE_BISHOP,  // 3
    WHITE_ROOK,    // 4
    WHITE_QUEEN,   // 5
    WHITE_KING,    // 6
    BLACK_PAWN,    // 7
    BLACK_KNIGHT,  // 8
    BLACK_BISHOP,  // 9
    BLACK_ROOK,    // 10
    BLACK_QUEEN,   // 11
    BLACK_KING,    // 12           
};

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

void makeMove(Bitboard& board, int fromSquare, int toSquare)
{
    board &= ~(1ULL << fromSquare);
    board |= (1ULL << toSquare);
}

int main()
{
    printBitboard(white_knights);
    std::cout << std::endl;
	makeMove(white_knights, b1, c3); // Move white pawn from e2 to e4
	printBitboard(white_knights);

	return 0;
}