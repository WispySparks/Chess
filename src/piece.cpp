#include "piece.hpp"

#include <vector>

#include "board.hpp"

std::vector<Pos> getRookMoves(Pos pos) {
    std::vector<Pos> moves;
    for (int col = pos.getCol() + 1; col < Board::size; col++) {  // Right
        Pos newPos = {pos.getRow(), col};
        moves.push_back(newPos);
        if (Board::isPiecePresent(newPos)) break;
    }
    for (int col = pos.getCol() - 1; col >= 0; col--) {  // Left
        Pos newPos = {pos.getRow(), col};
        moves.push_back(newPos);
        if (Board::isPiecePresent(newPos)) break;
    }
    for (int row = pos.getRow() + 1; row < Board::size; row++) {  // Down
        Pos newPos = {row, pos.getCol()};
        moves.push_back(newPos);
        if (Board::isPiecePresent(newPos)) break;
    }
    for (int row = pos.getRow() - 1; row >= 0; row--) {  // Up
        Pos newPos = {row, pos.getCol()};
        moves.push_back(newPos);
        if (Board::isPiecePresent(newPos)) break;
    }
    return moves;
}

std::vector<Pos> getKnightMoves(Pos pos) {
    //* Squish this into loops
    std::vector<Pos> moves;
    moves.push_back(Pos{pos.getRow() - 1, pos.getCol() - 2});  // ULL
    moves.push_back(Pos{pos.getRow() - 2, pos.getCol() - 1});  // ULL
    moves.push_back(Pos{pos.getRow() - 2, pos.getCol() + 1});  // UUR
    moves.push_back(Pos{pos.getRow() - 1, pos.getCol() + 2});  // URR
    moves.push_back(Pos{pos.getRow() + 1, pos.getCol() + 2});  // DRR
    moves.push_back(Pos{pos.getRow() + 2, pos.getCol() + 1});  // DDR
    moves.push_back(Pos{pos.getRow() + 2, pos.getCol() - 1});  // DDL
    moves.push_back(Pos{pos.getRow() + 1, pos.getCol() - 2});  // DLL
    return moves;
}

std::vector<Pos> getBishopMoves(Pos pos) {
    std::vector<Pos> moves;
    for (int col = pos.getCol() + 1; col < Board::size; col++) {  // Right Down
        Pos newPos = {pos.getRow() + (col - pos.getCol()), col};
        moves.push_back(newPos);
        if (Board::isPiecePresent(newPos)) break;
    }
    for (int col = pos.getCol() + 1; col < Board::size; col++) {  // Right Up
        Pos newPos = {pos.getRow() - (col - pos.getCol()), col};
        moves.push_back(newPos);
        if (Board::isPiecePresent(newPos)) break;
    }
    for (int col = pos.getCol() - 1; col >= 0; col--) {  // Left Up
        Pos newPos = {pos.getRow() + (col - pos.getCol()), col};
        moves.push_back(newPos);
        if (Board::isPiecePresent(newPos)) break;
    }
    for (int col = pos.getCol() - 1; col >= 0; col--) {  // Left Down
        Pos newPos = {pos.getRow() - (col - pos.getCol()), col};
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
            moves.push_back(Pos{pos.getRow() + i, pos.getCol() + j});
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
    Pos firstSquare = {pos.getRow() - 1, pos.getCol()};
    moves.push_back(firstSquare);
    if (!hasMoved && !Board::isPiecePresent(firstSquare)) {
        moves.push_back(Pos{pos.getRow() - 2, pos.getCol()});
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
            return getKingMoves(pos, hasMoved);
        case Type::Pawn:
            return getPawnMoves(pos, hasMoved);
        case Type::None:
        default:
            return std::vector<Pos>();
    }
}
