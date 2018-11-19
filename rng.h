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

/**
 * @brief Roll virtual dice n times, keeping the highest value.
 *
 * @note Average rolls for n dice, from Tyler Akins at rumkin.com:
 * 1d10  = 5.5
 * 2d10  = 7.15
 * 3d10  = 7.975
 * 4d10  = 8.4667
 * 5d10  = 8.79175
 * 6d10  = 9.021595
 * 7d10  = 9.1919575
 * 8d10  = 9.32268667
 * 9d10  = 9.425695015
 * 10d10 = 9.5085658075
 */
int roll_high(int times, int sides, int n);

/// Return an element, respecting weights.
template <class T>
const T& weighted_element(const std::vector<T>& data)
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

        if (weighted_chance >= entry && it.chance != 0)
        {
            return it;
        }
    }

    std::cerr << "Error:\nCould not find valid element.\n";
    std::exit(1);
}

/// Return a random element.
template <class T>
const T& random_element(const std::vector<T>& data)
{
    size_t entry = rng(0, data.size() - 1);
    return data[entry];
}

#endif // RNG_H
