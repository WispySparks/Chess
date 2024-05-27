#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>

#include "position.hpp"
#include "team.hpp"

class Board {
    public:
        static constexpr int size = 8;
        void newGame();
        bool movePiece(std::string start, std::string end, Team team);
        bool isPiecePresent(Pos pos);
        void printBoardWithNotation(Team team);
};

constexpr Pos queenSideRook{7, 0};
constexpr Pos queenSideKnight{7, 1};
constexpr Pos queenSideBishop{7, 2};
constexpr Pos queen{7, 3};
constexpr Pos king{7, 4};
constexpr Pos kingSideBishop{7, 5};
constexpr Pos kingSideKnight{7, 6};
constexpr Pos kingSideRook{7, 7};

#endif