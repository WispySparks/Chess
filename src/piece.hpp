#ifndef PIECE_HPP
#define PIECE_HPP

#include <utility>
#include <vector>

enum class Team : int { White, Black, None };
enum class Type : char {
    Rook = 'R',
    Knight = 'N',
    Bishop = 'B',
    Queen = 'Q',
    King = 'K',
    Pawn = 'P',
    None = '-'
};
class Piece {
    private:
        Team team;
        Type type;
        bool hasMoved = false;
    public:
        Piece(Team team, Type type) {
            this->team = team;
            this->type = type;
        }
        Team getTeam() { return team; }
        Type getType() { return type; }
        char getName() { return std::to_underlying(type); }
        void registerMove() { hasMoved = true; }
        std::vector<int> getMoves(int column, int row);
};
Team oppositeTeam(Team team);

#endif