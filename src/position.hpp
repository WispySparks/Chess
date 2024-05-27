#ifndef POSITION_HPP
#define POSITION_HPP

// Row, Column
struct Pos {
        int row;
        int col;
        bool operator==(const Pos&) const = default;
};

#endif