#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include "piece.hpp"
    
// Pointers because object slicing
class Board {
    // Row, Column
    Piece* board[8][8];
    public:
        void newGame();
        void movePiece(std::string start, std::string end);
        void printBoard();
        void printBoardWithNotation();
    private:
        bool checkMoveLegality(Piece* startPiece, std::vector<int> pieceMoves, int endCol, int endRow);
        int fileToColumnIndex(char c);
        int rankToRowIndex(char c);
}; 

#endif