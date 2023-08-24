#include "board.hpp"

void Board::newGame() {
    // Have to use 'new' so that the objects are created on the heap and I can have pointers to them.
    for (int row = 2; row < 6; row++) {
        for (int col = 0; col < 8; col++) {
            board[row][col] = new Empty();
        }
    }
    for (int i = 0; i < 8; i += 7) {
        board[i][0] = new Rook();
        board[i][1] = new Knight();
        board[i][2] = new Bishop();
        board[i][3] = new Queen();
        board[i][4] = new King();
        board[i][5] = new Bishop();
        board[i][6] = new Knight();
        board[i][7] = new Rook();
    }
    for (int i = 0; i < 8; i++) {
        board[1][i] = new Pawn();
        board[6][i] = new Pawn();
    }
}

void Board::movePiece(std::string start, std::string end) {
    int startCol = convertFile(start.at(0));
    int startRow = convertRank(start.at(1));
    int endCol = convertFile(end.at(0));
    int endRow = convertRank(end.at(1));
    Piece* piece = board[startRow][startCol];
    std::cout << "Getting legal moves for " << piece->getName() << "\n";
    std::vector<int> legalMoves = piece->getLegalMoves(startCol, startRow);
    for (auto i: legalMoves) {
        std::cout << i << ' ';
    }
    std::cout << "\n";
    bool legalMove = false;
    for (int i = 0; i < legalMoves.size(); i += 2) {
        int legalCol = legalMoves.at(i);
        int legalRow = legalMoves.at(i+1);
        if (endCol == legalCol && endRow == legalRow) {
            legalMove = true;
        }
    }
    if (legalMove) {
        piece->registerMove();
        board[endRow][endCol] = piece;
        board[startRow][startCol] = new Empty();
    } else {
        std::cout << "Illegal Move!\n";
    }
}

int Board::convertFile(char c) {
    return c - 'a';
}

int Board::convertRank(char c) {
    return c - '1';
}

void Board::printBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << board[i][j]->getName() << " ";
        }
        std::cout << "\n";
    }
}

void Board::printBoardWithNotation() {
    std::cout << "  a" << " " << "b" << " " << "c" << " " << "d" << " " << "e" << " " << "f" << " " << "g" << " " << "h" << "\n";
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (j == 0) {
                std::cout << (8-i) << " ";
            }
            std::cout << board[i][j]->getName() << " ";
            if (j == 7) {
                std::cout << (8-i) << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "  a" << " " << "b" << " " << "c" << " " << "d" << " " << "e" << " " << "f" << " " << "g" << " " << "h" << "\n";
}