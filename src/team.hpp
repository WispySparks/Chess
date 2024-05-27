#ifndef TEAM_HPP
#define TEAM_HPP

enum class Team : int { White = 0, Black = 1 };
inline Team oppositeTeam(Team team) {
    return (team == Team::White) ? Team::Black : Team::White;
};

#endif