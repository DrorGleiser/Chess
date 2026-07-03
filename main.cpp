//#include "board.h"
//#include "display.h"
//#include "movegen.h"
//#include <iostream>
//
//int main()
//{
//    
//    // ---- PAWN (white) ----
//    printBitboard(pawnTargets(11, 0x0000000000000000ULL, 0x0000000000000000ULL, true));  // d2 empty            -> 0x0000000008080000
//    std::cout << std::endl;
//    printBitboard(pawnTargets(11, 0x0000000000080000ULL, 0x0000000000000000ULL, true));  // d2 enemy on d3      -> 0x0000000000000000
//    std::cout << std::endl;
//    printBitboard(pawnTargets(27, 0x0000001400000000ULL, 0x0000000000000000ULL, true));  // d4 en c5 + e5       -> 0x0000001C00000000
//    std::cout << std::endl;
//    printBitboard(pawnTargets(27, 0x0000001000000000ULL, 0x0000001000000000ULL, true));  // d4 friendly on e5   -> 0x0000000800000000
//    std::cout << std::endl;
//    printBitboard(pawnTargets(31, 0x0000010000000000ULL, 0x0000000000000000ULL, true));  // h4 en a6 (wrap)     -> 0x0000008000000000
//    std::cout << std::endl;
//    printBitboard(pawnTargets(0, 0x0000000000000000ULL, 0x0000000000000000ULL, true));  // a1 corner (edge)    -> 0x0000000000000100
//    std::cout << std::endl;
//
//    // ---- PAWN (black) ----
//    printBitboard(pawnTargets(51, 0x0000000000000000ULL, 0x0000000000000000ULL, false)); // d7 empty            -> 0x0000080800000000
//    std::cout << std::endl;
//    printBitboard(pawnTargets(51, 0x0000080000000000ULL, 0x0000000000000000ULL, false)); // d7 enemy on d6      -> 0x0000000000000000
//    std::cout << std::endl;
//    printBitboard(pawnTargets(35, 0x0000000014000000ULL, 0x0000000000000000ULL, false)); // d5 en c4 + e4       -> 0x000000001C000000
//    std::cout << std::endl;
//    printBitboard(pawnTargets(32, 0x0000000080000000ULL, 0x0000000000000000ULL, false)); // a5 en h4 (wrap)     -> 0x0000000001000000
//    std::cout << std::endl;
//    printBitboard(pawnTargets(11, 0x0000000000000000ULL, 0x0000000000000000ULL, false)); // d2 push to d1 (edge)-> 0x0000000000000008
//    std::cout << std::endl;
//
//    
//    return 0;
//}
