/**
 * @file attack_type.h
 * @brief Generic base class for different attack types that can
 * be performed by Actors.
 */

#ifndef ATTACK_TYPE_H
#define ATTACK_TYPE_H

#include <string>
#include <vector>

#include <vendor/json.h>
typedef nlohmann::json Json;

class Actor;

/// Stores information for a single performable attack type.
class Attack_Type
{
public:

    /// Unique identifier for this attack type.
    std::string type;

    /// Calculate the base damage of a single attack.
    int calc_atk();

    /// Display a combat message.
    void print_attack(
        const Actor& attacker,
        const Actor& defender,
        int damage);

protected:

    friend void from_json(const Json& json, Attack_Type& mod);

    /// Base damage of this attack type.
    int atk;

    /// Commands that can be used to perform this attack type.
    std::vector<std::string> verbs;

    /// Combat messages to be displayed when this attack is performed.
    std::vector<std::string> attack_msg;
};

void from_json(const Json& json, Attack_Type& mod);

#endif // ATTACK_TYPE_H
