#include <iostream>
#include <limits>
#include <regex>
#include <string>

#include "board.hpp"
#include "team.hpp"

Team chooseTeam();

int main(int argc, char* argv[]) {
    std::cout << "Welcome to Chess! Enter 0 to play as white and 1 to play as black.\n";
    Team playerTeam = chooseTeam();
    Board::newGame(playerTeam);
    Board::printBoardWithNotation();
    std::regex inputRegex = std::regex("^[a-h][1-8][a-h][1-8]$");
    std::string input;
    while (true) {
        std::cout << "\nInput: ";
        std::cin >> input;
        if (input == "exit" || input == "quit") break;
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
        Board::movePiece(startPos, endPos, playerTeam);
    }
    std::cout << "--- END PROGRAM ---";
    return EXIT_SUCCESS;
}

Team chooseTeam() {
    while (true) {
        int num;
        std::cin >> num;
        if (!std::cin.fail()) {
            if (num == std::to_underlying(Team::White) || num == std::to_underlying(Team::Black)) {
                return static_cast<Team>(num);
            }
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid Team.\n";
    }
}

// TODO: LOS Checks (King Castling), Castling
// TODO: Play against self, Checking and Checkmate, En Passant, Computer opponent, LAN Opponent

// https://stackoverflow.com/a/15188950
// https://stackoverflow.com/a/655086
// https://stackoverflow.com/a/7532521