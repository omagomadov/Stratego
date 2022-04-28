#ifndef ROLE_H
#define ROLE_H

#include <string>

/**
 * @brief The Role enum represents the role of the pawn.
 */
enum Role {
    MARSHAL = 10,
    GENERAL = 9,
    COLONEL = 8,
    MAJOR = 7,
    COMMANDER = 6,
    LIEUTENANT = 5,
    SERGEANT = 4,
    MINESWEEPER = 3,
    SCOUT = 2,
    SPY = 1,
    FLAG = 11,
    BOMB = 12
};

/**
 * @brief toString simple toString function for the role.
 * @param role the role
 * @return the string value of the role
 */
inline std::string to_string(Role role) {
    switch(role) {
    case MARSHAL:
        return "Marshal";
        break;
    case GENERAL:
        return "General";
        break;
    case COLONEL:
        return "Colonel";
        break;
    case MAJOR:
        return "Major";
        break;
    case COMMANDER:
        return "Commander";
        break;
    case LIEUTENANT:
        return "Lieutenant";
        break;
    case SERGEANT:
        return "Sergeant";
        break;
    case MINESWEEPER:
        return "Minesweeper";
        break;
    case SCOUT:
        return "Scout";
        break;
    case SPY:
        return "Spy";
        break;
    case BOMB:
        return "Bomb";
        break;
    default:
        return "Flag";
        break;
    }
}

#endif // ROLE_H
