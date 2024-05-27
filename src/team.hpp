#ifndef TEAM_HPP
#define TEAM_HPP

#include <cstdint>

enum class Team : uint8_t { White = 0, Black = 1 };
inline Team oppositeTeam(Team team) {
    return (team == Team::White) ? Team::Black : Team::White;
};

#endif