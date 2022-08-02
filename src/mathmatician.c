// Copyright 2021 Ariel Solis, ariel.solismonge@ucr.ac.cr

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include "array_int64.h"
#include "mathmatician.h"

#define NA_NUMBER -1
#define NEGATIVE_NUMBER -2



// Adapted from
// <https://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/>

// procedure calculate_prime_factors(value, matrix, index):
/**
 * @brief Calculates all the prime factors of a number
 * 
 * @details The number has to be more than 1 to have prime factors.
 *  first we see if the number is divisible by 2, if it is we save
 *  2 in the array and set the exponent to 1, then divide the number by 2.
 *  If the number is divisible by 2 again we add 1 to the exponent.
 *  When the number is no longer divisible by 2 we add the exponent next
 *  to the first 2.
 *  After that we know for a fact, the number is odd, so we 
 *  divide it by only odd numbers and sabe de divisible ones in the array
 *  After that process we have sucessfully calculated all factors.
 * 
 * @param value 
 * @param matrix 
 * @param matrix_index 
 */

// procedure calculate_prime_factors(value, matrix, index):
void calculate_prime_factors(int64_t value, array_int64_t* matrix,
  size_t matrix_index) {
  // if value is_different from 1 or 0:
  if (value > 1) {
    // add_factors(value, 2, matrix, index)
    if (value%2 == 0) {
      add_factors(&value, 2, matrix, matrix_index);
    }

    // for odd_numbers = 3 stop_when odd_numbers <= sqrt(value)
    for (int odd_numbers = 3; odd_numbers <= sqrt((double)value);
      odd_numbers = odd_numbers+2) {
      // add_factors(value, odd_numbers, matrix, index)
      if (value%odd_numbers == 0) {
        add_factors(&value, odd_numbers, matrix, matrix_index);
      }
    }  // end for

    // if value > 2:
    if (value > 2) {
      // add value to matrix in index
      array_int64_append(&matrix[matrix_index], value);
      array_int64_append(&matrix[matrix_index], 1);
    }  // end if
  } else if (value == 1 || value == 0) {
    array_int64_append(&(matrix[matrix_index]), NA_NUMBER);
  } else if (value < 0) {
//     add -1 to matrix in index
    array_int64_append(&(matrix[matrix_index]), NEGATIVE_NUMBER);
  }  // end else
}  // end procedure

/**
 * @brief Method to add the factors that current values is divisible by.
 * @details The method divides the number by the current factor we give it.
 *  it divides it until it is no longer divisible. If it's divisible
 *  at least one time, the method adds the current factor to the matrix
 *  in the matrix index. After that if the number is still divisible we
 *  calculate how many times it is divisible (exponent) ans at the end we
 *  add it to the matrix.
 * 
 * @param current_value 
 * @param current_factor 
 * @param matrix 
 * @param matrix_index 
 */

// procedure add_factors(current_value, current_factor, matrix, index) do
void add_factors(int64_t* current_value, int64_t current_factor,
  array_int64_t* matrix, size_t matrix_index) {
  // declare exponent := 0
  int exponent = 0;
  // while current_value divisible by current_factor:
  while (*current_value % current_factor == 0) {
    // if exponent equals 0:
    if (!exponent) {
      // add current_factor to matrix in index
      array_int64_append(&matrix[matrix_index], current_factor);
      // set exponent to 1
      exponent = 1;
    // else
    } else {
      // increment exponent by 1
      ++exponent;
    }  // end if
    // current_value = current_value/current_factor
    *current_value = *current_value/current_factor;
  }  // end while
  // add exponent to matrix in index
  array_int64_append(&matrix[matrix_index], exponent);
}  // end procedure
