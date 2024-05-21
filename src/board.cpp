#include "board.hpp"
#include <iostream>

void Board::newGame(Team playerTeam) {
    for (int row = 2; row < 6; row++) {
        for (int col = 0; col < 8; col++) {
            board[row][col] = empty;
        }
    }
    for (int i = 0; i < 8; i += 7) {
        Team team = (i == 0) ? oppositeTeam(playerTeam) : playerTeam;
        board[i][0] = new Rook(team);
        board[i][1] = new Knight(team);
        board[i][2] = new Bishop(team);
        board[i][3] = new Queen(team);
        board[i][4] = new King(team);
        board[i][5] = new Bishop(team);
        board[i][6] = new Knight(team);
        board[i][7] = new Rook(team);
    }
    for (int i = 0; i < 8; i++) {
        board[1][i] = new Pawn(oppositeTeam(playerTeam));
        board[6][i] = new Pawn(playerTeam);
    }
}

void Board::movePiece(std::string start, std::string end, Team team) {
    int startCol = fileToColumnIndex(start.at(0));
    int startRow = rankToRowIndex(start.at(1));
    int endCol = fileToColumnIndex(end.at(0));
    int endRow = rankToRowIndex(end.at(1));
    Piece* piece = board[startRow][startCol];
    // Stored as column, row, column, row, etc
    std::vector<int> moves = piece->getMoves(startCol, startRow);
    // std::cout << "Getting moves for " << piece->getName() << ".\n";
    if (checkMoveLegality(piece, moves, endCol, endRow, team)) {
        piece->registerMove();
        board[endRow][endCol] = piece;
        board[startRow][startCol] = empty;
        printBoardWithNotation();
    } 
}

bool Board::checkMoveLegality(Piece* startPiece, std::vector<int> pieceMoves, int endCol, int endRow, Team team) {
    Piece* endPiece = board[endRow][endCol];
    if (startPiece->getTeam() != team) {
        std::cout << "Wrong team!\n";
        return false;
    }
    if (startPiece->getTeam() == endPiece->getTeam()) {
        std::cout << "Can't attack same team!\n";
        return false;
    }
    bool legalMove = false;
    for (int i = 0; i < pieceMoves.size(); i += 2) {
        int column = pieceMoves.at(i);
        int row = pieceMoves.at(i+1);
        // std::cout << column << ", " << row << "\n";
        if (endCol == column && endRow == row) {
            legalMove = true;
        }
    }
    if (!legalMove) std::cout << "Illegal move!\n";
    return legalMove;
}

int Board::fileToColumnIndex(char c) {
    return c - 'a';
}

int Board::rankToRowIndex(char c) {
    // flip index as player is the bottom pieces
    return 7 - (c - '1');
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
            std::string str; 
            str += board[i][j]->getName();
            if (board[i][j]->getTeam() == Team::Black) applyColor(&str, 34);
            std::cout << str << " ";
            if (j == 7) {
                std::cout << (8-i) << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "  a" << " " << "b" << " " << "c" << " " << "d" << " " << "e" << " " << "f" << " " << "g" << " " << "h" << "\n";
}

void Board::applyColor(std::string* str, int color) {
    std::string s = "\033[" + std::to_string(color) + "m";
    str->insert(0, s);
    str->append("\033[0m");
}