#include <iostream>
#include <vector>
#include "piece.hpp"

std::vector<int> Piece::getLegalMoves(int startCol, int startRow) {
    return std::vector<int>();
}

std::vector<int> Rook::getLegalMoves(int startCol, int startRow) {
    return std::vector<int>();
}

std::vector<int> Knight::getLegalMoves(int startCol, int startRow) {
    return std::vector<int>();
}

std::vector<int> Bishop::getLegalMoves(int startCol, int startRow) {
    return std::vector<int>();
}

std::vector<int> Queen::getLegalMoves(int startCol, int startRow) {
    return std::vector<int>();
}

std::vector<int> King::getLegalMoves(int startCol, int startRow) {
    return std::vector<int>();
}

std::vector<int> Pawn::getLegalMoves(int startCol, int startRow) {
    std::cout << "getting legal moves for pawn!\n";
    std::vector<int> moves = std::vector<int>();
    moves.push_back(startCol+1);
    moves.push_back(startRow);
    if (!hasMoved) {
        moves.push_back(startCol+2);
        moves.push_back(startRow);
    }
    return moves;
}

std::vector<int> Empty::getLegalMoves(int startCol, int startRow) {
    return std::vector<int>();
}