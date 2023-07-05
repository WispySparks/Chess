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

void Board::movePiece(std::string start, std::string end) {
    int startCol = convertFile(start.at(0));
    int startRow = convertRank(start.at(1));
    int endCol = convertFile(end.at(0));
    int endRow = convertRank(end.at(1));
    Piece piece = board[startRow][startCol];
    std::cout << piece.getName() << "\n";
    std::vector<int> legalMoves = piece.getLegalMoves(startCol, startRow);
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
        piece.registerMove();
        board[endRow][endCol] = piece;
        board[startRow][startCol] = Empty();
    } else {
        std::cout << "Illegal Move!\n";
    }
}

int Board::convertFile(char c) {
    return c - 'a';
}

int Board::convertRank(char c) {
    return c - '0' - 1;
}

void Board::printBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << board[i][j].getName() << " ";
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
            std::cout << board[i][j].getName() << " ";
            if (j == 7) {
                std::cout << (8-i) << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "  a" << " " << "b" << " " << "c" << " " << "d" << " " << "e" << " " << "f" << " " << "g" << " " << "h" << "\n";
}