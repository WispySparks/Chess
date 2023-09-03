#include "board.hpp"

void Board::newGame() {
    // Have to use 'new' so that the objects are created on the heap and I can have pointers to them.
    for (int row = 2; row < 6; row++) {
        for (int col = 0; col < 8; col++) {
            board[row][col] = new Empty();
        }
    }
    for (int i = 0; i < 8; i += 7) {
        Team team = (i == 0) ? Team::Black : Team::White;
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
        board[1][i] = new Pawn(Team::Black);
        board[6][i] = new Pawn(Team::White);
    }
}

void Board::movePiece(std::string start, std::string end) {
    int startCol = fileToColumnIndex(start.at(0));
    int startRow = rankToRowIndex(start.at(1));
    int endCol = fileToColumnIndex(end.at(0));
    int endRow = rankToRowIndex(end.at(1));
    Piece* piece = board[startRow][startCol];
    // Stored as column, row, column, row, etc
    std::vector<int> moves = piece->getMoves(startCol, startRow);
    // std::cout << "Getting moves for " << piece->getName() << ".\n";
    if (checkMoveLegality(piece, moves, endCol, endRow)) {
        piece->registerMove();
        board[endRow][endCol] = piece;
        board[startRow][startCol] = new Empty();
    } else {
        std::cout << "Illegal Move!\n";
    }
}

bool Board::checkMoveLegality(Piece* startPiece, std::vector<int> pieceMoves, int endCol, int endRow) {
    Piece* endPiece = board[endRow][endCol];
    if (startPiece->getTeam() != Team::White) return false; //! Change later
    if (startPiece->getTeam() == endPiece->getTeam()) return false;
    bool legalMove = false;
    for (int i = 0; i < pieceMoves.size(); i += 2) {
        int column = pieceMoves.at(i);
        int row = pieceMoves.at(i+1);
        if (endCol == column && endRow == row) {
            legalMove = true;
        }
    }
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
    // std::cout << "\033[35m HI \033[0m\n";
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