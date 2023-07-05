#ifndef PIECE_HPP
#define PIECE_HPP

#include <vector>
class Piece {
    protected:
        char name;
        bool hasMoved = false;
    public: 
        char getName() {return name;}
        void registerMove() {hasMoved = true;}
        virtual std::vector<int> getLegalMoves(int startCol, int startRow);
};

class Rook : public Piece {
    public: 
        Rook() {
            name = 'R';
        }
        std::vector<int> getLegalMoves(int startCol, int startRow) override;

};
class Knight : public Piece {
    public: 
        Knight() {
            name = 'N';
        }
        std::vector<int> getLegalMoves(int startCol, int startRow) override;

};
class Bishop : public Piece {
    public: 
        Bishop() {
            name = 'B';
        }
        std::vector<int> getLegalMoves(int startCol, int startRow) override;

};
class Queen : public Piece {
    public: 
        Queen() {
            name = 'Q';
        }
        std::vector<int> getLegalMoves(int startCol, int startRow) override;

};
class King : public Piece {
    public: 
        King() {
            name = 'K';
        }
        std::vector<int> getLegalMoves(int startCol, int startRow) override;

};
class Pawn : public Piece {
    public:
        Pawn() {
            name = 'P';
        }
        std::vector<int> getLegalMoves(int startCol, int startRow) override;
};
class Empty : public Piece {
    public: 
        Empty() {
            name = '-';
        }
        std::vector<int> getLegalMoves(int startCol, int startRow) override;
};

#endif