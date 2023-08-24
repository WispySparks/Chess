#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include "piece.hpp"

class Board {
    Piece* board[8][8];
    public:
        void newGame();
        void movePiece(std::string start, std::string end);
        void printBoard();
        void printBoardWithNotation();
    private:
        int convertFile(char c);
        int convertRank(char c);
}; 

#endif