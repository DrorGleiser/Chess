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

Bitboard white_ocuupency = white_pawns | white_rooks | white_knights | white_bishops | white_queen | white_king;
Bitboard black_ocuupency = black_pawns | black_rooks | black_knights | black_bishops | black_queen | black_king;
Bitboard all_occupency = white_ocuupency | black_ocuupency;

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

bool checkIfRookPathClear(Bitboard board, int fromSquare, int toSquare)
{
	int fromRank = fromSquare / 8;
	int fromFile = fromSquare % 8;
	int toRank = toSquare / 8;
	int toFile = toSquare % 8;

	if (fromRank == toRank)
	{
		int startFile = std::min(fromFile, toFile) + 1;
		int endFile = std::max(fromFile, toFile);
		for (int file = startFile; file < endFile; ++file)
		{
			int square = fromRank * 8 + file;
			if (checkIfSquareOccupied(board, square))
				return false;
		}
	}

	else if (fromFile == toFile)
	{
		int startRank = std::min(fromRank, toRank) + 1;
		int endRank = std::max(fromRank, toRank);
		for (int rank = startRank; rank < endRank; ++rank)
		{
			int square = rank * 8 + fromFile;
			if (checkIfSquareOccupied(board, square))
				return false;
		}
	}
	else
	{
		return false; // Not a valid rook move
	}
	return true; // Path is clear
}

bool checkIfBishopPathClear(Bitboard board, int fromSquare, int toSquare)
{
	int fromRank = fromSquare / 8;
	int fromFile = fromSquare % 8;
	int toRank = toSquare / 8;
	int toFile = toSquare % 8;

	if (abs(toRank - fromRank) != abs(toFile - fromFile))
		return false; // Not a valid bishop move

	int rankStep = (toRank > fromRank) ? 1 : -1;
	int fileStep = (toFile > fromFile) ? 1 : -1;
	int currentRank = fromRank + rankStep;
	int currentFile = fromFile + fileStep;

	while (currentRank != toRank && currentFile != toFile)
	{
		int square = currentRank * 8 + currentFile;
		if (checkIfSquareOccupied(board, square))
			return false; // Path is blocked
		currentRank += rankStep;
		currentFile += fileStep;
	}
	return true; // Path is clear
}

bool checkIfQueenPathClear(Bitboard board, int fromSquare, int toSquare)
{
	return checkIfRookPathClear(board, fromSquare, toSquare) || checkIfBishopPathClear(board, fromSquare, toSquare);
}

bool checkIfPawnPathClear(Bitboard board, int fromSquare, int toSquare)
{
	int fromRank = fromSquare / 8;
	int fromFile = fromSquare % 8;
	int toRank = toSquare / 8;
	int toFile = toSquare % 8;

	if (fromFile == toFile)
	{
		if (toRank == fromRank + 1 || (fromRank == 1 && toRank == fromRank + 2))
		{
			return !checkIfSquareOccupied(board, toSquare);
		}
	}

	else if (abs(toFile - fromFile) == 1 && toRank == fromRank + 1)
	{
		return checkIfSquareOccupied(board, toSquare);
	}
	return false; // Invalid pawn move
}

bool checkIfKingPathClear(Bitboard board, int fromSquare, int toSquare)
{
	int fromRank = fromSquare / 8;
	int fromFile = fromSquare % 8;
	int toRank = toSquare / 8;
	int toFile = toSquare % 8;
	if (abs(toRank - fromRank) <= 1 && abs(toFile - fromFile) <= 1)
	{
		return !checkIfSquareOccupied(board, toSquare);
	}
	return false; // Invalid king move
}

bool checkIfSquareOccupied(Bitboard board, int square)
{
	return (board >> square) & 1ULL;
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

void makeMove(Bitboard& board, int fromSquare, int toSquare)
{
    board &= ~(1ULL << fromSquare);
    board |= (1ULL << toSquare);
}

void checkRookMovement(Bitboard& board, int fromSquare, int toSquare)
{
    int fromRank = fromSquare / 8;
    int fromFile = fromSquare % 8;
    int toRank = toSquare / 8;
    int toFile = toSquare % 8;
    if (fromRank == toRank || fromFile == toFile)
    {
        makeMove(board, fromSquare, toSquare);
    }
    else
    {
        std::cout << "Invalid move for a rook!" << std::endl;
    }
}

void checkKnightMovement(Bitboard& board, int fromSquare, int toSquare)
{
	int fromRank = fromSquare / 8;
	int fromFile = fromSquare % 8;
	int toRank = toSquare / 8;
	int toFile = toSquare % 8;
	int rankDiff = abs(toRank - fromRank);
	int fileDiff = abs(toFile - fromFile);
	if ((rankDiff == 2 && fileDiff == 1) || (rankDiff == 1 && fileDiff == 2))
	{
		makeMove(board, fromSquare, toSquare);
	}
	else
	{
		std::cout << "Invalid move for a knight!" << std::endl;
	}
}

void checkBishopMovement(Bitboard& board, int fromSquare, int toSquare)
{
	int fromRank = fromSquare / 8;
	int fromFile = fromSquare % 8;
	int toRank = toSquare / 8;
	int toFile = toSquare % 8;
	if (abs(toRank - fromRank) == abs(toFile - fromFile))
	{
		makeMove(board, fromSquare, toSquare);
	}
	else
	{
		std::cout << "Invalid move for a bishop!" << std::endl;
	}
}

void checkQueenMovement(Bitboard& board, int fromSquare, int toSquare)
{
	int fromRank = fromSquare / 8;
	int fromFile = fromSquare % 8;
	int toRank = toSquare / 8;
	int toFile = toSquare % 8;
	if (fromRank == toRank || fromFile == toFile || abs(toRank - fromRank) == abs(toFile - fromFile))
	{
		makeMove(board, fromSquare, toSquare);
	}
	else
	{
		std::cout << "Invalid move for a queen!" << std::endl;
	}
}

void checkKingMovement(Bitboard& board, int fromSquare, int toSquare)
{
	int fromRank = fromSquare / 8;
	int fromFile = fromSquare % 8;
	int toRank = toSquare / 8;
	int toFile = toSquare % 8;
	if (abs(toRank - fromRank) <= 1 && abs(toFile - fromFile) <= 1)
	{
		makeMove(board, fromSquare, toSquare);
	}
	else
	{
		std::cout << "Invalid move for a king!" << std::endl;
	}
}

void checkPawnMovement(Bitboard& board, int fromSquare, int toSquare)
{
	int fromRank = fromSquare / 8;
	int fromFile = fromSquare % 8;
	int toRank = toSquare / 8;
	int toFile = toSquare % 8;
	if (fromFile == toFile && (abs(toRank - fromRank) == 1 || (fromRank == 1 && abs (toRank - fromRank) == 2)))
	{
		makeMove(board, fromSquare, toSquare);
	}
	else
	{
		std::cout << "Invalid move for a pawn!" << std::endl;
	}
}

int main()
{
	updateVisualBoard();
	printVisualBoard();
    std::cout << std::endl;
	checkKnightMovement(white_knights, b1, c3);
	updateVisualBoard();
	printVisualBoard();

	return 0;
}