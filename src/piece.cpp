#include "piece.hpp"

#include <vector>

#include "board.hpp"

std::vector<Pos> getRookMoves(Board board, Pos pos) {
    std::vector<Pos> moves;
    for (int col = pos.col + 1; col < Board::size; col++) {  // Right
        Pos newPos = {pos.row, col};
        moves.push_back(newPos);
        if (board.isPiecePresent(newPos)) break;
    }
    for (int col = pos.col - 1; col >= 0; col--) {  // Left
        Pos newPos = {pos.row, col};
        moves.push_back(newPos);
        if (board.isPiecePresent(newPos)) break;
    }
    for (int row = pos.row + 1; row < Board::size; row++) {  // Down
        Pos newPos = {row, pos.col};
        moves.push_back(newPos);
        if (board.isPiecePresent(newPos)) break;
    }
    for (int row = pos.row - 1; row >= 0; row--) {  // Up
        Pos newPos = {row, pos.col};
        moves.push_back(newPos);
        if (board.isPiecePresent(newPos)) break;
    }
    return moves;
}

std::vector<Pos> getKnightMoves(Board board, Pos pos) {
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

std::vector<Pos> getBishopMoves(Board board, Pos pos) {
    std::vector<Pos> moves;
    for (int col = pos.col + 1; col < Board::size; col++) {  // Right Down
        Pos newPos = {pos.row + (col - pos.col), col};
        moves.push_back(newPos);
        if (board.isPiecePresent(newPos)) break;
    }
    for (int col = pos.col + 1; col < Board::size; col++) {  // Right Up
        Pos newPos = {pos.row - (col - pos.col), col};
        moves.push_back(newPos);
        if (board.isPiecePresent(newPos)) break;
    }
    for (int col = pos.col - 1; col >= 0; col--) {  // Left Up
        Pos newPos = {pos.row + (col - pos.col), col};
        moves.push_back(newPos);
        if (board.isPiecePresent(newPos)) break;
    }
    for (int col = pos.col - 1; col >= 0; col--) {  // Left Down
        Pos newPos = {pos.row - (col - pos.col), col};
        moves.push_back(newPos);
        if (board.isPiecePresent(newPos)) break;
    }
    return moves;
}

std::vector<Pos> getQueenMoves(Board board, Pos pos) {
    std::vector<Pos> rookMoves = getRookMoves(board, pos);
    std::vector<Pos> bishopMoves = getBishopMoves(board, pos);
    rookMoves.insert(rookMoves.end(), bishopMoves.begin(), bishopMoves.end());
    return rookMoves;
}

std::vector<Pos> getKingMoves(Board board, Pos pos, bool moved) {
    std::vector<Pos> moves;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            moves.push_back(Pos{pos.row + i, pos.col + j});
        }
    }
    if (!moved) {
        if (!board.isPiecePresent(kingSideBishop) && !board.isPiecePresent(kingSideKnight)) {
        }
    }
    return moves;
}

std::vector<Pos> getPawnMoves(Board board, Piece piece, Pos pos) {
    std::vector<Pos> moves;
    int increment = (piece.team == Team::White) ? -1 : 1;
    Pos firstSquare = {pos.row + increment, pos.col};
    moves.push_back(firstSquare);
    if (!piece.moved && !board.isPiecePresent(firstSquare)) {
        moves.push_back(Pos{pos.row + increment * 2, pos.col});
    }
    return moves;
}

std::vector<Pos> getMoves(Board board, Piece piece, Pos pos) {
    switch (piece.type) {
        case Type::Rook:
            return getRookMoves(board, pos);
        case Type::Knight:
            return getKnightMoves(board, pos);
        case Type::Bishop:
            return getBishopMoves(board, pos);
        case Type::Queen:
            return getQueenMoves(board, pos);
        case Type::King:
            return getKingMoves(board, pos, piece.moved);
        case Type::Pawn:
            return getPawnMoves(board, piece, pos);
        case Type::None:
        default:
            return std::vector<Pos>();
    }
}
