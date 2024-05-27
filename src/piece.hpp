#ifndef PIECE_HPP
#define PIECE_HPP

#include <vector>

#include "position.hpp"
#include "team.hpp"
#include "type.hpp"

class Piece {
    private:
        Team team;
        Type type;
        bool moved = false;
    public:
        Piece(Team team, Type type) {
            this->team = team;
            this->type = type;
        }
        Team getTeam() { return team; }
        Type getType() { return type; }
        char getName() { return std::to_underlying(type); }
        void registerMove() { moved = true; }
        std::vector<Pos> getMoves(Pos pos);
};

#endif