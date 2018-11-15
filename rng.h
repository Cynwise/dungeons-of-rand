/**
 * @file rng.h
 * @brief Pseudorandom number generation utilities.
 */

#ifndef RNG_H
#define RNG_H

#include <cstdlib>
#include <iostream>
#include <vector>

/**
 * @brief Generate pseudorandom floating point number within a range.
 *
 * @param min Minimum value of generated float.
 * @param max Maximum vlaue of generated float.
 *
 * @return Generated float.
 */
double frng(double min, double max);

/**
 * @brief Generate pseudorandom integer within a range.
 *
 * @param min Minimum value of generated integer.
 * @param max Maximum value of generated integer.
 *
 * @return Generated integer.
 */
int rng(int min, int max);

/**
 * @brief Flip virtual coin.
 *
 * @return 0 = tails, 1 = heads
 */
int flip();

/**
 * @brief Roll virtual dice.
 *
 * @param times Number of times to roll. Alternatively, number of dice.
 * @param sides Number of sides on the die.
 *
 * @return Result sum of dice rolls.
 */
int roll(int times, int sides);

/// Return an element, respecting weights.
template <class T>
const T& random_element(const std::vector<T>& data)
{
    size_t total_weights = 0;
    size_t weighted_chance = 0;

    // Calculate sum of weights.
    for (auto& it : data)
    {
        total_weights += it.chance;
    }

    // Pick random element.
    size_t entry = rng(0, total_weights);
    for (auto& it : data)
    {
        weighted_chance += it.chance;

        if (weighted_chance >= entry)
        {
            return it;
        }
    }

    std::cerr << "Error:\nCould not find valid element.\n";
    std::exit(1);
}

#endif // RNG_H
