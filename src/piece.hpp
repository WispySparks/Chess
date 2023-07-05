#ifndef PIECE_HPP
#define PIECE_HPP

class Piece {
    protected:
        char name;
    public: 
        char getName() {return name;}
};

class Rook : public Piece {
    public: Rook() {
        name = 'R';
    }
};
class Knight : public Piece {
    public: Knight() {
        name = 'N';
    }
};
class Bishop : public Piece {
    public: Bishop() {
        name = 'B';
    }
};
class Queen : public Piece {
    public: Queen() {
        name = 'Q';
    }
};
class King : public Piece {
    public: King() {
        name = 'K';
    }
};
class Pawn : public Piece {
    public: Pawn() {
        name = 'P';
    }
};
class Empty : public Piece {
    public: Empty() {
        name = '-';
    }
};

#endif