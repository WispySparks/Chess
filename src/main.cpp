#include <iostream>
#include <regex>
#include <string>

#include "board.hpp"
#include "team.hpp"

int main(int argc, char* argv[]) {
    std::cout << "Welcome to Chess!\n";
    Board board = Board();
    Team currentTeam = Team::White;
    board.newGame();
    board.printBoardWithNotation(currentTeam);
    std::regex inputRegex = std::regex("^[a-h][1-8][a-h][1-8]$");
    std::string input;
    while (true) {
        std::cout << "\n" << getTeamAsString(currentTeam) << "'s turn.";
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
        if (board.movePiece(startPos, endPos, currentTeam)) currentTeam = oppositeTeam(currentTeam);
        board.printBoardWithNotation(currentTeam);
    }
    std::cout << "--- END PROGRAM ---";
    return EXIT_SUCCESS;
}

// TODO: LOS Checks (King Castling), Castling
// TODO: Play against self, Checking and Checkmate, En Passant, Computer opponent, LAN Opponent