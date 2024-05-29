#ifndef TEAM_HPP
#define TEAM_HPP

#include <cstdint>
#include <string>

enum class Team : uint8_t { White = 0, Black = 1 };
inline Team oppositeTeam(Team team) {
    return (team == Team::White) ? Team::Black : Team::White;
};
inline std::string teamToString(Team team) {
    return (team == Team::White) ? "White" : "Black";
}

#endif