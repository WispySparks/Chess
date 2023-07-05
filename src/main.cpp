#include <iostream>
#include "board.hpp"

int main(int argc, char* argv[]) {
    Board board = Board();
    board.newGame();
    board.printBoard();
    std::string input;
    while (true) {
        std::cout << "\nInput: ";
        std::cin >> input; 
        if (input == "exit") break;
        board.printBoard();
    }
    std::cout << "--- END PROGRAM ---";
    return 0;
}