#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>

#include "position.hpp"
#include "team.hpp"

namespace Board {
const int size = 8;
const Pos queenSideRook = {7, 0};
const Pos queenSideKnight = {7, 1};
const Pos queenSideBishop = {7, 2};
const Pos queen = {7, 3};
const Pos king = {7, 4};
const Pos kingSideBishop = {7, 5};
const Pos kingSideKnight = {7, 6};
const Pos kingSideRook = {7, 7};
void newGame(Team team);
void movePiece(std::string start, std::string end, Team team);
bool isPiecePresent(Pos pos);
void printBoard();
void printBoardWithNotation();
}

#endif