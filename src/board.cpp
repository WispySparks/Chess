#include "board.hpp"

#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <memory>

#include "piece.hpp"

const int colorBlack = 34;
std::array<std::array<std::shared_ptr<Piece>, Board::size>, Board::size> board;  // Row, Column
std::shared_ptr<Piece> empty =
    std::make_shared<Piece>(Team::White, Type::None);  // Single Empty Instance

int fileToColumnIndex(char c) {
    return c - 'a';
}

int rankToRowIndex(char c) {
    // flip index as player is the bottom pieces
    return 7 - (c - '1');
}

void applyColor(std::string& str, int color) {
    std::string s = "\033[" + std::to_string(color) + "m";
    str.insert(0, s);
    str.append("\033[0m");
}

std::shared_ptr<Piece> getPiece(Pos pos) {
    if (pos.row < 0 || pos.row >= Board::size || pos.col < 0 || pos.col >= Board::size) {
        std::cout << "Bad Pos! " << pos.row << ", " << pos.col << "\n";
    }
    return board[pos.row][pos.col];
}

void setPiece(Pos pos, std::shared_ptr<Piece> piece) {
    board[pos.row][pos.col] = piece;
}

bool isLegalMove(Piece piece, std::vector<Pos> moves, Pos pos, Team team) {
    if (piece.team != team) {
        std::cout << "Wrong team!\n";
        return false;
    }
    if (piece.team == getPiece(pos)->team && getPiece(pos)->type != Type::None) {
        std::cout << "Can't attack same team!\n";
        return false;
    }
    bool legalMove = std::find(moves.begin(), moves.end(), pos) != moves.end();
    if (!legalMove) std::cout << "Illegal move!\n";
    return legalMove;
}

void Board::newGame() {
    // Having a team here doesn't really make sense, the board can flip in the print function
    for (int row = 2; row < 6; row++) {
        for (int col = 0; col < Board::size; col++) {
            board[row][col] = empty;
        }
    }
    for (int i = 0; i < Board::size; i += 7) {
        Team team = (i == 0) ? Team::Black : Team::White;
        board[i][0] = std::make_shared<Piece>(team, Type::Rook);
        board[i][1] = std::make_shared<Piece>(team, Type::Knight);
        board[i][2] = std::make_shared<Piece>(team, Type::Bishop);
        board[i][3] = std::make_shared<Piece>(team, Type::Queen);
        board[i][4] = std::make_shared<Piece>(team, Type::King);
        board[i][5] = std::make_shared<Piece>(team, Type::Bishop);
        board[i][6] = std::make_shared<Piece>(team, Type::Knight);
        board[i][7] = std::make_shared<Piece>(team, Type::Rook);
    }
    for (int i = 0; i < Board::size; i++) {
        board[1][i] = std::make_shared<Piece>(Team::Black, Type::Pawn);
        board[6][i] = std::make_shared<Piece>(Team::White, Type::Pawn);
    }
}

bool Board::movePiece(std::string start, std::string end, Team team) {
    int startCol = fileToColumnIndex(start.at(0));
    int startRow = rankToRowIndex(start.at(1));
    int endCol = fileToColumnIndex(end.at(0));
    int endRow = rankToRowIndex(end.at(1));
    Pos startPos{startRow, startCol};
    Pos endPos{endRow, endCol};
    std::shared_ptr<Piece> piece = getPiece(startPos);
    std::vector<Pos> moves = piece->getMoves(*this, startPos);
    // std::cout << "Moves\n";
    // for (auto p : moves) {
    // std::cout << p.col << " " << p.row << "\n";
    // }
    if (isLegalMove(*piece, moves, endPos, team)) {
        piece->moved = true;
        int finalRow = (piece->team == Team::White) ? 0 : Board::size - 1;
        if (piece->type == Type::Pawn && endRow == finalRow) {
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
            piece = std::make_shared<Piece>(team, type);
        }
        setPiece(endPos, piece);
        setPiece(startPos, empty);
        return true;
    }
    return false;
}

bool Board::castle(bool queenSide, Team team) {
    //! bugged!
    std::shared_ptr<Piece> king = getPiece(Board::king(team));
    std::shared_ptr<Piece> kingRook = getPiece(kingSideRook(team));
    std::shared_ptr<Piece> queenRook = getPiece(queenSideRook(team));
    if (!queenSide && !king->moved && !isPiecePresent(kingSideBishop(team)) &&
        !isPiecePresent(kingSideKnight(team)) && !kingRook->moved) {
        setPiece(Board::king(team), empty);
        setPiece(kingSideRook(team), empty);
        setPiece(kingSideBishop(team), kingRook);
        setPiece(kingSideKnight(team), king);
        return true;
    }
    if (queenSide && !king->moved && !isPiecePresent(queen(team)) &&
        !isPiecePresent(queenSideBishop(team)) && !isPiecePresent(queenSideKnight(team)) &&
        !queenRook->moved) {
        setPiece(Board::king(team), empty);
        setPiece(queenSideRook(team), empty);
        setPiece(queen(team), queenRook);
        setPiece(queenSideBishop(team), king);
        return true;
    }
    std::cout << "Can't Castle!\n";
    return false;
}

bool Board::inCheck(Team team) const {
    std::vector<Pos> moves;
    for (int row = 0; row < Board::size; row++) {
        for (int col = 0; col < Board::size; col++) {
            Pos pos{row, col};
            auto piece = getPiece(pos);
            auto pieceMoves = piece->getMoves(*this, pos);
            moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
        }
    }
    return false;
}

bool Board::isPiecePresent(Pos pos) const {
    return getPiece(pos)->type != Type::None;
}

void printBoardWhite() {
    std::cout << "  a b c d e f g h\n";
    for (int row = 0; row < Board::size; row++) {
        for (int col = 0; col < Board::size; col++) {
            Pos pos{row, col};
            auto piece = getPiece(pos);
            if (col == 0) {
                std::cout << (Board::size - row) << " ";
            }
            std::string str;
            str += piece->getName();
            if (piece->team == Team::Black) applyColor(str, colorBlack);
            std::cout << str << " ";
            if (col == 7) {
                std::cout << (Board::size - row) << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "  a b c d e f g h\n";
}

void printBoardBlack() {
    std::cout << "  h g f e d c b a\n";
    for (int row = Board::size - 1; row >= 0; row--) {
        for (int col = Board::size - 1; col >= 0; col--) {
            Pos pos{row, col};
            auto piece = getPiece(pos);
            if (col == 7) {
                std::cout << (Board::size - row) << " ";
            }
            std::string str;
            str += piece->getName();
            if (piece->team == Team::Black) applyColor(str, 34);
            std::cout << str << " ";
            if (col == 0) {
                std::cout << (Board::size - row) << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "  h g f e d c b a\n";
}

void Board::printBoardWithNotation(Team team) const {
    if (team == Team::White) {
        printBoardWhite();
    } else {
        printBoardBlack();
    }
}