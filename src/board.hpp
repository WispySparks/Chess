#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>

#include "piece.hpp"

// Row, Column
class Pos {
    private:
        int row;
        int col;
    public:
        Pos(int row, int col) : row{row}, col{col} {}
        int getRow() { return row; }
        int getCol() { return col; }
        bool operator==(const Pos&) const = default;
};

namespace Board {
const int size = 8;
void newGame(Team team);
void movePiece(std::string start, std::string end, Team team);
bool isPiecePresent(Pos pos);
void printBoard();
void printBoardWithNotation();
}

#endif