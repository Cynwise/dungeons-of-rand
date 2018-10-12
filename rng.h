/**
 * @file rng.h
 */

#ifndef RNG_H
#define RNG_H

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
 * @param modifier Number to add to the outcome of the dice roll.
 * 
 * @return Result from dice roll, plus modifier.
 * 
 * @note 2d5+2 -> roll(2, 5, 2)
 */
int roll(int times, int sides, int modifier);

#endif // RNG_H
