#include <iostream>
#include <vector>
#include "piece.hpp"

Team oppositeTeam(Team team) {
    return (team == Team::White) ? Team::Black : Team::White;
}

std::vector<int> Rook::getMoves(int startCol, int startRow) {
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

std::vector<int> Knight::getMoves(int startCol, int startRow) {
    //* Squish this into loops
    std::vector<int> moves = std::vector<int>();
    moves.push_back(startCol-2); // ULL
    moves.push_back(startRow-1);

    moves.push_back(startCol-1); // UUL  
    moves.push_back(startRow-2);

    moves.push_back(startCol+1); // UUR 
    moves.push_back(startRow-2);

    moves.push_back(startCol+2); // URR 
    moves.push_back(startRow-1);

    moves.push_back(startCol+2); // DRR  
    moves.push_back(startRow+1);

    moves.push_back(startCol+1); // DDR  
    moves.push_back(startRow+2);

    moves.push_back(startCol-1); // DDL 
    moves.push_back(startRow+2);

    moves.push_back(startCol-2); // DLL 
    moves.push_back(startRow+1);
    return moves;
}

std::vector<int> Bishop::getMoves(int startCol, int startRow) {
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

std::vector<int> Queen::getMoves(int startCol, int startRow) {
    //* Maybe change this later so I'm not creating rooks and bishops
    Rook r = Rook(Team::None);
    Bishop b = Bishop(Team::None);
    std::vector<int> rVector = r.getMoves(startCol, startRow);
    std::vector<int> bVector = b.getMoves(startCol, startRow);
    rVector.insert(rVector.end(), bVector.begin(), bVector.end());
    return rVector;
}

std::vector<int> King::getMoves(int startCol, int startRow) {
    std::vector<int> moves = std::vector<int>();
    for (int i = -1; i < 2; i++) {  
        for (int j = -1; j < 2; j++) {
            moves.push_back(startCol+j);
            moves.push_back(startRow+i);
        }
    }
    return moves;
}

std::vector<int> Pawn::getMoves(int startCol, int startRow) {
    std::vector<int> moves = std::vector<int>();
    moves.push_back(startCol);
    moves.push_back(startRow-1);
    if (!hasMoved) {
        moves.push_back(startCol);
        moves.push_back(startRow-2);
    }
    return moves;
}

std::vector<int> Empty::getMoves(int startCol, int startRow) {
    return std::vector<int>();
}