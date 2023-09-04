#ifndef PIECE_HPP
#define PIECE_HPP

#include <vector>

enum Team {White, Black, None};
Team oppositeTeam(Team team);
class Piece {
    protected:
        Team team;
        char name;
        bool hasMoved = false;
    public: 
        Piece(Team team) {
            this->team = team;
        }
        Team getTeam() {return team;}
        char getName() {return name;}
        void registerMove() {hasMoved = true;}
        virtual std::vector<int> getMoves(int startCol, int startRow) = 0;
};

class Rook : public Piece {
    public: 
        Rook(Team team) : Piece(team) {
            name = 'R';
        }
        std::vector<int> getMoves(int startCol, int startRow) override;

};
class Knight : public Piece {
    public: 
        Knight(Team team) : Piece(team) {
            name = 'N';
        }
        std::vector<int> getMoves(int startCol, int startRow) override;

};
class Bishop : public Piece {
    public: 
        Bishop(Team team) : Piece(team) {
            name = 'B';
        }
        std::vector<int> getMoves(int startCol, int startRow) override;

};
class Queen : public Piece {
    public: 
        Queen(Team team) : Piece(team) {
            name = 'Q';
        }
        std::vector<int> getMoves(int startCol, int startRow) override;

};
class King : public Piece {
    public: 
        King(Team team) : Piece(team) {
            name = 'K';
        }
        std::vector<int> getMoves(int startCol, int startRow) override;

};
class Pawn : public Piece {
    public:
        Pawn(Team team) : Piece(team) {
            name = 'P';
        }
        std::vector<int> getMoves(int startCol, int startRow) override;
};
class Empty : public Piece {
    public: 
        Empty() : Piece(Team::None) {
            name = '-';
        }
        std::vector<int> getMoves(int startCol, int startRow) override;
};

#endif