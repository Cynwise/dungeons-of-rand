/**
 * @file player.h
 * @brief Actor that represents the player character. Also declares
 * the global Player instance.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <actor.h>

/**
 * @brief Actor that represents the player character. Implemented as
 * a singleton to prevent multiple player instances from being
 * spawned.
 */
class Player : public Actor
{
public:

    Player();

    Player* clone();

    /// Return singleton.
    static Player& get_instance();

    void attack(Actor& target);
    void attack(Actor& target, const std::string& type);

    int hurt(int damage);

    /// Report the player's status.
    void print_status();

private:

    bool dodge;
};

#endif // PLAYER_H
