#include "piece.hpp"

#include <vector>

#include "board.hpp"

std::vector<Pos> getRookMoves(Pos pos) {
    std::vector<Pos> moves;
    for (int col = pos.col + 1; col < Board::size; col++) {  // Right
        Pos newPos = {pos.row, col};
        moves.push_back(newPos);
        if (Board::isPiecePresent(newPos)) break;
    }
    for (int col = pos.col - 1; col >= 0; col--) {  // Left
        Pos newPos = {pos.row, col};
        moves.push_back(newPos);
        if (Board::isPiecePresent(newPos)) break;
    }
    for (int row = pos.row + 1; row < Board::size; row++) {  // Down
        Pos newPos = {row, pos.col};
        moves.push_back(newPos);
        if (Board::isPiecePresent(newPos)) break;
    }
    for (int row = pos.row - 1; row >= 0; row--) {  // Up
        Pos newPos = {row, pos.col};
        moves.push_back(newPos);
        if (Board::isPiecePresent(newPos)) break;
    }
    return moves;
}

std::vector<Pos> getKnightMoves(Pos pos) {
    //* Squish this into loops
    std::vector<Pos> moves;
    moves.push_back(Pos{pos.row - 1, pos.col - 2});  // ULL
    moves.push_back(Pos{pos.row - 2, pos.col - 1});  // ULL
    moves.push_back(Pos{pos.row - 2, pos.col + 1});  // UUR
    moves.push_back(Pos{pos.row - 1, pos.col + 2});  // URR
    moves.push_back(Pos{pos.row + 1, pos.col + 2});  // DRR
    moves.push_back(Pos{pos.row + 2, pos.col + 1});  // DDR
    moves.push_back(Pos{pos.row + 2, pos.col - 1});  // DDL
    moves.push_back(Pos{pos.row + 1, pos.col - 2});  // DLL
    return moves;
}

std::vector<Pos> getBishopMoves(Pos pos) {
    std::vector<Pos> moves;
    for (int col = pos.col + 1; col < Board::size; col++) {  // Right Down
        Pos newPos = {pos.row + (col - pos.col), col};
        moves.push_back(newPos);
        if (Board::isPiecePresent(newPos)) break;
    }
    for (int col = pos.col + 1; col < Board::size; col++) {  // Right Up
        Pos newPos = {pos.row - (col - pos.col), col};
        moves.push_back(newPos);
        if (Board::isPiecePresent(newPos)) break;
    }
    for (int col = pos.col - 1; col >= 0; col--) {  // Left Up
        Pos newPos = {pos.row + (col - pos.col), col};
        moves.push_back(newPos);
        if (Board::isPiecePresent(newPos)) break;
    }
    for (int col = pos.col - 1; col >= 0; col--) {  // Left Down
        Pos newPos = {pos.row - (col - pos.col), col};
        moves.push_back(newPos);
        if (Board::isPiecePresent(newPos)) break;
    }
    return moves;
}

std::vector<Pos> getQueenMoves(Pos pos) {
    std::vector<Pos> rookMoves = getRookMoves(pos);
    std::vector<Pos> bishopMoves = getBishopMoves(pos);
    rookMoves.insert(rookMoves.end(), bishopMoves.begin(), bishopMoves.end());
    return rookMoves;
}

std::vector<Pos> getKingMoves(Pos pos, bool hasMoved) {
    std::vector<Pos> moves;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            moves.push_back(Pos{pos.row + i, pos.col + j});
        }
    }
    if (!hasMoved) {
        if (!Board::isPiecePresent(Board::kingSideBishop) &&
            !Board::isPiecePresent(Board::kingSideKnight)) {
        }
    }
    return moves;
}

std::vector<Pos> getPawnMoves(Pos pos, bool hasMoved) {
    std::vector<Pos> moves;
    Pos firstSquare = {pos.row - 1, pos.col};
    moves.push_back(firstSquare);
    if (!hasMoved && !Board::isPiecePresent(firstSquare)) {
        moves.push_back(Pos{pos.row - 2, pos.col});
    }
    return moves;
}

std::vector<Pos> Piece::getMoves(Pos pos) {
    switch (getType()) {
        case Type::Rook:
            return getRookMoves(pos);
        case Type::Knight:
            return getKnightMoves(pos);
        case Type::Bishop:
            return getBishopMoves(pos);
        case Type::Queen:
            return getQueenMoves(pos);
        case Type::King:
            return getKingMoves(pos, moved);
        case Type::Pawn:
            return getPawnMoves(pos, moved);
        case Type::None:
        default:
            return std::vector<Pos>();
    }
}
