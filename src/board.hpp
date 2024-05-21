#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>
#include <vector>
#include "piece.hpp"
    
// Pointers because object slicing
class Board {
    Piece* board[8][8]; // Row, Column
    Empty* empty = new Empty(); // Single Empty Instance
    public:
        void newGame(Team team);
        void movePiece(std::string start, std::string end, Team team);
        void printBoard();
        void printBoardWithNotation();
    private:
        bool checkMoveLegality(Piece* startPiece, std::vector<int> pieceMoves, int endCol, int endRow, Team team);
        int fileToColumnIndex(char c);
        int rankToRowIndex(char c);
        void applyColor(std::string* str, int color);
}; 

#endif