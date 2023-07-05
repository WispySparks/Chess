#include <iostream>
#include <string>
#include "board.hpp"

int main(int argc, char* argv[]) {
    Board board = Board();
    board.newGame();
    board.printBoardWithNotation();
    std::string input;
    while (true) {
        std::cout << "\nInput: ";
        std::cin >> input; 
        if (input == "exit") break;
        if (input.length() != 4) {
            std::cout << "Invalid Move";
            continue;
        }
        std::string startPos = input.substr(0, 2);
        std::string endPos = input.substr(2, 2);
        board.movePiece(startPos, endPos);
        board.printBoardWithNotation();
    }
    std::cout << "--- END PROGRAM ---";
    return 0;
}