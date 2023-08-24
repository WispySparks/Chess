#include <iostream>
#include <vector>
#include "piece.hpp"

std::vector<int> Piece::getLegalMoves(int startCol, int startRow) {
    std::cout << "Piece Called\n";
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
    std::cout << "Pawn Called\n";
    std::vector<int> moves = std::vector<int>();
    moves.push_back(startCol);
    moves.push_back(startRow+1);
    if (!hasMoved) {
        moves.push_back(startCol);
        moves.push_back(startRow+2);
    }
    return moves;
}

std::vector<int> Empty::getLegalMoves(int startCol, int startRow) {
    return std::vector<int>();
}