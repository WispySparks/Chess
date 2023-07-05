#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include "piece.hpp"

class Board {
    Piece board[8][8];
    public:
        void newGame();
        void printBoard();
}; 

#endif