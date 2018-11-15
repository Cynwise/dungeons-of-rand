/**
 * @file attack_type.cpp
 * @brief Implementation of module specified attack types.
 */

#include <cstdlib>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include <actor.h>
#include <actor/player.h>
#include <attack_type.h>
#include <rng.h>
#include <item/weapon.h>
#include <vendor/json.h>

/// Replaces all instances of substr in src
static void replace_all(
    std::string& str,
    const std::string& from,
    const std::string& to)
{
    size_t len = from.length();
    size_t pos = str.find(from);
    while (pos != std::string::npos)
    {
        str.replace(pos, len, to);
        pos = str.find(from);
    }
}

int Attack_Type::calc_atk()
{
    int base_damage = roll(2, atk) / 2;
    return base_damage;
}

void Attack_Type::print_attack(
    const Actor& attacker,
    const Actor& defender,
    int damage)
{
    Player& player = Player::get_instance();

    std::string damage_str = std::to_string(damage);
    std::string hp_str = std::to_string(defender.hp);
    std::string max_hp_str = std::to_string(defender.max_hp);

    // Pick a combat string to use.
    int entry = rng(0, attack_msg.size() - 1);
    std::string msg(attack_msg[entry]);

    // Add the defender's status to the combat string.
    std::string status = "\n[Their] current health is ";
    status += hp_str + "/" + max_hp_str + ".\n\n";
    msg += status;

    // Parse the combat string.
    if (&attacker == &player)
    {
        replace_all(msg, "[You]", "You");
        replace_all(msg, "[you]", "you");
        replace_all(msg, "[Your]", "Your");
        replace_all(msg, "[your]", "your");
        replace_all(msg, "[Yours]", "Yours");
        replace_all(msg, "[yours]", "yours");
        replace_all(msg, "[You're]", "You're");
        replace_all(msg, "[you're]", "you're");
        replace_all(msg, "[y]", "");
        replace_all(msg, "[ey]", "");
    }
    else
    {
        std::string upper_name = "The " + attacker.get_name();
        std::string lower_name = "the " + attacker.get_name();
        replace_all(msg, "[You]", upper_name);
        //replace_all(msg, "[you]", lower_name);
        replace_all(msg, "[you]", "they");
        replace_all(msg, "[Your]", upper_name + "'s");
        //replace_all(msg, "[your]", lower_name + "'s");
        replace_all(msg, "[your]", "their");
        replace_all(msg, "[Yours]", "Theirs");
        replace_all(msg, "[yours]", "theirs");
        replace_all(msg, "[You're]", upper_name + " is");
        //replace_all(msg, "[you're]", lower_name + " is");
        replace_all(msg, "[you're]", "they're");
        replace_all(msg, "[y]", "s");
        replace_all(msg, "[ey]", "es");
    }
    if (&defender == &player)
    {
        replace_all(msg, "[They]", "You");
        replace_all(msg, "[they]", "you");
        replace_all(msg, "[Their]", "Your");
        replace_all(msg, "[their]", "your");
        replace_all(msg, "[Theirs]", "Yours");
        replace_all(msg, "[theirs]", "yours");
        replace_all(msg, "[They're]", "You're");
        replace_all(msg, "[they're]", "you're");
        replace_all(msg, "[them]", "you");
        replace_all(msg, "[t]", "");
        replace_all(msg, "[et]", "");
    }
    else
    {
        std::string upper_name = "The " + defender.get_name();
        std::string lower_name = "the " + defender.get_name();
        replace_all(msg, "[They]", upper_name);
        //replace_all(msg, "[they]", lower_name);
        replace_all(msg, "[they]", "they");
        replace_all(msg, "[Their]", upper_name + "'s");
        //replace_all(msg, "[their]", lower_name + "'s");
        replace_all(msg, "[their]", "their");
        replace_all(msg, "[Theirs]", "Theirs");
        replace_all(msg, "[theirs]", "theirs");
        replace_all(msg, "[They're]", upper_name + " is");
        //replace_all(msg, "[they're]", lower_name + " is");
        replace_all(msg, "[they're]", "they're");
        replace_all(msg, "[them]", lower_name);
        replace_all(msg, "[t]", "s");
        replace_all(msg, "[et]", "es");
    }
    replace_all(msg, "[damage]", damage_str);
    replace_all(msg, "[weapon]", attacker.weapon->get_name());
    replace_all(msg, "\\n", "\n"); // Escape newline.

    // Output formatted message.
    std::cout << msg;
}

void from_json(const Json& json, Attack_Type& mod)
{
    auto it = json.find("type");
    if (it != json.end())
    {
        json.at("type").get_to(mod.type);
    }

    it = json.find("atk");
    if (it != json.end())
    {
        json.at("atk").get_to(mod.atk);
    }

    it = json.find("verbs");
    if (it != json.end())
    {
        json.at("verbs").get_to(mod.verbs);
    }

    it = json.find("attack_msg");
    if (it != json.end())
    {
        json.at("attack_msg").get_to(mod.attack_msg);
    }
}
