#ifndef POSITION_HPP
#define POSITION_HPP

// Row, Column
class Pos {
    private:
        int row;
        int col;
    public:
        Pos(int row, int col) : row{}, col{} {}
        int getRow() const { return row; }
        int getCol() const { return col; }
        bool operator==(const Pos&) const = default;
};

#endif