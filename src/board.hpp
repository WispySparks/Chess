#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>

#include "piece.hpp"

namespace Board {
void newGame(Team team);
void movePiece(std::string start, std::string end, Team team);
bool isPieceAtPos(int row, int col);
void printBoard();
void printBoardWithNotation();
}

#endif