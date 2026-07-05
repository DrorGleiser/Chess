//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include "renderer.h"
//#include "mailbox.h"
//
//int main()
//{
//    Piece board[64];
//    toMailbox(board);
//
//    const char* symbols = ".PNBRQKpnbrqk"; // index 0 = EMPTY, then your enum order
//
//    for (int rank = 7; rank >= 0; --rank)
//    {
//        for (int file = 0; file < 8; ++file)
//            std::cout << symbols[board[rank * 8 + file]] << ' ';
//        std::cout << '\n';
//    }
//    
//    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "Chess");
//
//    Renderer renderer;   // constructor loads textures — once, not per frame
//
//    while (window.isOpen())
//    {
//        while (auto event = window.pollEvent())
//            if (event->is<sf::Event::Closed>())
//                window.close();
//
//        window.clear();
//        toMailbox(board);
//        renderer.draw(window, board);
//        window.display();
//    }
//    return 0;
//}