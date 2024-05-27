#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>

#include "position.hpp"
#include "team.hpp"

class Piece;
class Board {
    public:
        static constexpr int size = 8;
        void newGame();
        bool movePiece(std::string start, std::string end, Team team);
        bool castle(bool queenSide, Team team);
        bool isPiecePresent(Pos pos) const;
        void printBoardWithNotation(Team team) const;
        inline static Pos queenSideRook(Team team) {
            int row = (team == Team::White) ? 7 : 0;
            return {row, 0};
        };
        inline static Pos queenSideKnight(Team team) {
            int row = (team == Team::White) ? 7 : 0;
            return {row, 1};
        };
        inline static Pos queenSideBishop(Team team) {
            int row = (team == Team::White) ? 7 : 0;
            return {row, 2};
        };
        inline static Pos queen(Team team) {
            int row = (team == Team::White) ? 7 : 0;
            return {row, 3};
        };
        inline static Pos king(Team team) {
            int row = (team == Team::White) ? 7 : 0;
            return {row, 4};
        };
        inline static Pos kingSideBishop(Team team) {
            int row = (team == Team::White) ? 7 : 0;
            return {row, 5};
        };
        inline static Pos kingSideKnight(Team team) {
            int row = (team == Team::White) ? 7 : 0;
            return {row, 6};
        };
        inline static Pos kingSideRook(Team team) {
            int row = (team == Team::White) ? 7 : 0;
            return {row, 7};
        };
};
#endif