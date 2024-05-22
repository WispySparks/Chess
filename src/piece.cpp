#include "piece.hpp"

#include <vector>

Team oppositeTeam(Team team) {
    return (team == Team::White) ? Team::Black : Team::White;
}

std::vector<int> getRookMoves(int startCol, int startRow) {
    std::vector<int> moves = std::vector<int>();
    for (int i = 0; i < 8; i++) {
        moves.push_back(i);
        moves.push_back(startRow);
    }
    for (int i = 0; i < 8; i++) {
        moves.push_back(startCol);
        moves.push_back(i);
    }
    return moves;
}

std::vector<int> getKnightMoves(int startCol, int startRow) {
    //* Squish this into loops
    std::vector<int> moves = std::vector<int>();
    moves.push_back(startCol - 2);  // ULL
    moves.push_back(startRow - 1);

    moves.push_back(startCol - 1);  // UUL
    moves.push_back(startRow - 2);

    moves.push_back(startCol + 1);  // UUR
    moves.push_back(startRow - 2);

    moves.push_back(startCol + 2);  // URR
    moves.push_back(startRow - 1);

    moves.push_back(startCol + 2);  // DRR
    moves.push_back(startRow + 1);

    moves.push_back(startCol + 1);  // DDR
    moves.push_back(startRow + 2);

    moves.push_back(startCol - 1);  // DDL
    moves.push_back(startRow + 2);

    moves.push_back(startCol - 2);  // DLL
    moves.push_back(startRow + 1);
    return moves;
}

std::vector<int> getBishopMoves(int startCol, int startRow) {
    std::vector<int> moves = std::vector<int>();
    for (int i = 0; i < 8; i++) {
        moves.push_back(i);
        int row = startRow - (startCol - i);
        moves.push_back(row);
        moves.push_back(i);
        row = startRow - (i - startCol);
        moves.push_back(row);
    }
    return moves;
}

std::vector<int> getQueenMoves(int startCol, int startRow) {
    std::vector<int> bishopMoves = getBishopMoves(startCol, startRow);
    std::vector<int> rookMoves = getRookMoves(startCol, startRow);
    bishopMoves.insert(bishopMoves.end(), rookMoves.begin(), rookMoves.end());
    return bishopMoves;
}

std::vector<int> getKingMoves(int startCol, int startRow) {
    std::vector<int> moves = std::vector<int>();
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            moves.push_back(startCol + j);
            moves.push_back(startRow + i);
        }
    }
    return moves;
}

std::vector<int> getPawnMoves(int startCol, int startRow, bool hasMoved) {
    std::vector<int> moves = std::vector<int>();
    moves.push_back(startCol);
    moves.push_back(startRow - 1);
    if (!hasMoved) {
        moves.push_back(startCol);
        moves.push_back(startRow - 2);
    }
    return moves;
}

std::vector<int> Piece::getMoves(int column, int row) {
    switch (getType()) {
        case Type::Rook:
            return getRookMoves(column, row);
        case Type::Knight:
            return getKnightMoves(column, row);
        case Type::Bishop:
            return getBishopMoves(column, row);
        case Type::Queen:
            return getQueenMoves(column, row);
        case Type::King:
            return getKingMoves(column, row);
        case Type::Pawn:
            return getPawnMoves(column, row, hasMoved);
        case Type::None:
        default:
            return std::vector<int>();
    }
}
