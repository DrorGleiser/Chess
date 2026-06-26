#include "board.h"
#include "display.h"
#include "movegen.h"
#include <iostream>

int main()
{
    
    // ---- ROOK ----
    printBitboard(rookTargets(27, 0x0000000000000000ULL, 0x0000000000000000ULL)); // d4 empty           -> 0x08080808F7080808
    std::cout << std::endl;
    printBitboard(rookTargets(0, 0x0000000000000000ULL, 0x0000000000000000ULL)); // a1 empty           -> 0x01010101010101FE
    std::cout << std::endl;
    printBitboard(rookTargets(31, 0x0000000000000000ULL, 0x0000000000000000ULL)); // h4 empty (wrap)    -> 0x808080807F808080
    std::cout << std::endl;
    printBitboard(rookTargets(27, 0x0000080020000000ULL, 0x0000080000000000ULL)); // d4 fr d6 / en f4   -> 0x0000000837080808
    std::cout << std::endl;
    printBitboard(rookTargets(27, 0x0000000814080000ULL, 0x0000000814080000ULL)); // d4 boxed in        -> 0x0000000000000000
    std::cout << std::endl;

    // ---- BISHOP ----
    printBitboard(bishopTargets(27, 0x0000000000000000ULL, 0x0000000000000000ULL)); // d4 empty (full X) -> 0x8041221400142241
    std::cout << std::endl;
    printBitboard(bishopTargets(0, 0x0000000000000000ULL, 0x0000000000000000ULL)); // a1 empty (one ray)-> 0x8040201008040200
    std::cout << std::endl;
    printBitboard(bishopTargets(7, 0x0000000000000000ULL, 0x0000000000000000ULL)); // h1 empty (wrap)   -> 0x0102040810204000
    std::cout << std::endl;
    printBitboard(bishopTargets(27, 0x0000200000000200ULL, 0x0000000000000200ULL)); // d4 en f6 / fr b2  -> 0x0001221400142040
    std::cout << std::endl;
    printBitboard(bishopTargets(27, 0x0000000814080000ULL, 0x0000000814080000ULL)); // d4 boxed in       -> 0x0000000000000000
    std::cout << std::endl;

    // ---- QUEEN (rook | bishop) ----
    printBitboard(queenTargets(27, 0x0000000000000000ULL, 0x0000000000000000ULL)); // d4 empty (star)    -> 0x88492A1CF71C2A49
    std::cout << std::endl;
    printBitboard(queenTargets(0, 0x0000000000000000ULL, 0x0000000000000000ULL)); // a1 empty           -> 0x81412111090503FE
    std::cout << std::endl;
    printBitboard(queenTargets(7, 0x0000000000000000ULL, 0x0000000000000000ULL)); // h1 empty (wrap)    -> 0x8182848890A0C07F
    std::cout << std::endl;
    printBitboard(queenTargets(27, 0x0000200000000200ULL, 0x0000000000000200ULL)); // d4 en f6 / fr b2   -> 0x08092A1CF71C2848
    std::cout << std::endl;
    printBitboard(queenTargets(27, 0x0008080022000000ULL, 0x0000080002000000ULL)); // d4 mixed blockers  -> 0x8041221C341C2A49
    std::cout << std::endl;

    // ---- KING (leaper: own-occupancy only matters) ----
    printBitboard(kingTargets(27, 0x0000000000000000ULL, 0x0000000000000000ULL)); // d4 (8 moves)        -> 0x0000001C141C0000
    std::cout << std::endl;
    printBitboard(kingTargets(0, 0x0000000000000000ULL, 0x0000000000000000ULL)); // a1 corner (3)       -> 0x0000000000000302
    std::cout << std::endl;
    printBitboard(kingTargets(31, 0x0000000000000000ULL, 0x0000000000000000ULL)); // h4 edge (5, no wrap)-> 0x000000C040C00000
    std::cout << std::endl;
    printBitboard(kingTargets(27, 0x0000000000000000ULL, 0x0000001000000000ULL)); // friendly on e5      -> 0x0000000C141C0000
    std::cout << std::endl;
    return 0;
}
