#ifndef BOARD_HPP
#define BOARD_HPP

#include <algorithm>
#include <string>

enum class Team : int;
class Pos;
namespace Board {
const int size = 8;
void newGame(Team team);
void movePiece(std::string start, std::string end, Team team);
bool isPiecePresent(Pos pos);
void printBoard();
void printBoardWithNotation();
}

// Row, Column
class Pos {
    private:
        int row;
        int col;
    public:
        Pos(int row, int col)
            : row{std::clamp(row, 0, Board::size - 1)}, col{std::clamp(col, 0, Board::size - 1)} {}
        int getRow() const { return row; }
        int getCol() const { return col; }
        bool operator==(const Pos&) const = default;
};

#endif