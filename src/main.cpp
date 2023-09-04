#include <iostream>
#include <regex>
#include <string>
#include "board.hpp"

int main(int argc, char* argv[]) {
    Board board = Board();
    board.newGame(Team::White);
    board.printBoardWithNotation();
    std::regex inputRegex = std::regex("^[a-h][1-8][a-h][1-8]$");
    std::string input;
    while (true) {
        std::cout << "\nInput: ";
        std::cin >> input; 
        if (input == "exit") break;
        if (!std::regex_match(input, inputRegex)) {
            std::cout << "Invalid notation.\n";
            continue;
        }
        std::string startPos = input.substr(0, 2);
        std::string endPos = input.substr(2, 2);
        if (startPos == endPos) {
            std::cout << "Can't move to same square.\n";
            continue;
        }
        board.movePiece(startPos, endPos);
    }
    std::cout << "--- END PROGRAM ---";
    return 0;
}

// https://stackoverflow.com/a/15188950
// https://stackoverflow.com/a/655086
// https://stackoverflow.com/a/7532521