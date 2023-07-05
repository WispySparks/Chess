#include "board.hpp"

void Board::newGame() {
    for (int row = 2; row < 6; row++) {
        for (int col = 0; col < 8; col++) {
            board[row][col] = Empty();
        }
    }
    for (int i = 0; i < 8; i += 7) {
        board[i][0] = Rook();
        board[i][1] = Knight();
        board[i][2] = Bishop();
        board[i][3] = Queen();
        board[i][4] = King();
        board[i][5] = Bishop();
        board[i][6] = Knight();
        board[i][7] = Rook();
    }
    for (int i = 0; i < 8; i++) {
        board[1][i] = Pawn();
        board[6][i] = Pawn();
    }
}

void Board::printBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << board[i][j].getName() << " ";
        }
        std::cout << "\n";
    }
}