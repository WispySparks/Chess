#include <iostream>
#include <limits>
#include <regex>
#include <string>
#include "board.hpp"

int chooseTeam();

int main(int argc, char* argv[]) {
    std::cout << "Welcome to Chess! Enter 0 to play as white and 1 to play as black.\n";
    Team playerTeam = (Team) chooseTeam();
    Board board = Board();
    board.newGame(playerTeam);
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
        board.movePiece(startPos, endPos, playerTeam);
    }
    std::cout << "--- END PROGRAM ---";
    return 0;
}

int chooseTeam() {
    int num;
    while (true) {
        std::cin >> num;
        if (!std::cin.fail()) {
            if (num == 0 || num == 1) break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid Number.\n";
    }
    return num;
}

// TODO: LOS Checks, Castling, 
// TODO: Play against self, Checking and Checkmate, En Passant, Computer opponent, LAN Opponent


// https://stackoverflow.com/a/15188950
// https://stackoverflow.com/a/655086
// https://stackoverflow.com/a/7532521