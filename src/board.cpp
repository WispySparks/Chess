#include "board.hpp"

#include <algorithm>
#include <iostream>
#include <limits>

Piece* board[Board::size][Board::size];            // Row, Column
Piece* empty = new Piece(Team::None, Type::None);  // Single Empty Instance

int fileToColumnIndex(char c) {
    return c - 'a';
}

int rankToRowIndex(char c) {
    // flip index as player is the bottom pieces
    return 7 - (c - '1');
}

void applyColor(std::string* str, int color) {
    std::string s = "\033[" + std::to_string(color) + "m";
    str->insert(0, s);
    str->append("\033[0m");
}

bool isLegalMove(Piece* piece, std::vector<Pos> moves, Pos pos, Team team) {
    if (piece == empty) {
        std::cout << "No piece selected!\n";
        return false;
    }
    if (piece->getTeam() != team) {
        std::cout << "Wrong team!\n";
        return false;
    }
    if (piece->getTeam() == board[pos.getRow()][pos.getCol()]->getTeam()) {
        std::cout << "Can't attack same team!\n";
        return false;
    }
    bool legalMove = std::find(moves.begin(), moves.end(), pos) != moves.end();
    if (!legalMove) std::cout << "Illegal move!\n";
    return legalMove;
}

void Board::newGame(Team playerteam) {
    // Having a team here doesn't really make sense, the board can flip in the print function
    Team opponentTeam = oppositeTeam(playerteam);
    for (int row = 2; row < 6; row++) {
        for (int col = 0; col < Board::size; col++) {
            board[row][col] = empty;
        }
    }
    for (int i = 0; i < Board::size; i += 7) {
        Team team = (i == 0) ? opponentTeam : playerteam;
        board[i][0] = new Piece(team, Type::Rook);
        board[i][1] = new Piece(team, Type::Knight);
        board[i][2] = new Piece(team, Type::Bishop);
        board[i][3] = new Piece(team, Type::Queen);
        board[i][4] = new Piece(team, Type::King);
        board[i][5] = new Piece(team, Type::Bishop);
        board[i][6] = new Piece(team, Type::Knight);
        board[i][7] = new Piece(team, Type::Rook);
    }
    for (int i = 0; i < Board::size; i++) {
        board[1][i] = new Piece(opponentTeam, Type::Pawn);
        board[6][i] = new Piece(playerteam, Type::Pawn);
    }
}

bool Board::isPiecePresent(Pos pos) {
    return board[pos.getRow()][pos.getCol()]->getType() != Type::None;
}

void Board::movePiece(std::string start, std::string end, Team team) {
    int startCol = fileToColumnIndex(start.at(0));
    int startRow = rankToRowIndex(start.at(1));
    int endCol = fileToColumnIndex(end.at(0));
    int endRow = rankToRowIndex(end.at(1));
    Piece* piece = board[startRow][startCol];
    std::vector<Pos> moves = piece->getMoves(Pos{startRow, startCol});
    if (isLegalMove(piece, moves, Pos{endRow, endCol}, team)) {
        piece->registerMove();
        if (piece->getType() == Type::Pawn && endRow == 0) {
            std::cout << "Pawn Promotion! Input a valid piece to be promoted to. (R, N, B, Q)\n";
            Type type = Type::None;
            while (true) {
                char c;
                std::cin >> c;
                if (!std::cin.fail()) {
                    if (c == 'R') type = Type::Rook;
                    if (c == 'N') type = Type::Knight;
                    if (c == 'B') type = Type::Bishop;
                    if (c == 'Q') type = Type::Queen;
                    if (type != Type::None) break;
                }
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid Piece.\n";
            }
            piece = new Piece(team, type);
        }
        board[endRow][endCol] = piece;
        board[startRow][startCol] = empty;
        printBoardWithNotation();
    }
}

void Board::printBoard() {
    for (int i = 0; i < Board::size; i++) {
        for (int j = 0; j < Board::size; j++) {
            std::cout << board[i][j]->getName() << " ";
        }
        std::cout << "\n";
    }
}

void Board::printBoardWithNotation() {
    std::cout << "  a b c d e f g h\n";
    for (int i = 0; i < Board::size; i++) {
        for (int j = 0; j < Board::size; j++) {
            if (j == 0) {
                std::cout << (Board::size - i) << " ";
            }
            std::string str;
            str += board[i][j]->getName();
            if (board[i][j]->getTeam() == Team::Black) applyColor(&str, 34);
            std::cout << str << " ";
            if (j == 7) {
                std::cout << (Board::size - i) << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "  a b c d e f g h\n";
}