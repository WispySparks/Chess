#ifndef PIECE_HPP
#define PIECE_HPP

#include <utility>
#include <vector>

#include "board.hpp"
#include "position.hpp"
#include "team.hpp"
#include "type.hpp"

struct Piece {
        const Team team;
        const Type type;
        bool moved = false;
        char getName() const { return std::to_underlying(type); }
        std::vector<Pos> getMoves(Board board, Pos pos);
};

#endif