// Copyright [2021] Ariel Solis, ariel.solismonge@ucr.ac.cr
#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>

#include "array_int64.h"
#include "printer.h"

#define VALID_NUMBER 1
#define INVALID_NUMBER 0
#define NA_NUMBER -1
#define NEGATIVE_NUMBER -2

// procedure print_results(values, matrix):
/**
 * @brief Method to print the number and it's factors on the terminal
 * 
 * @details First it iterates through the values. If a value in the array
 *  of values is 1 and in the invalid numbers is 0, that means it is an 
 *  invalid number so we print it, a negative number is also an invalid
 *  number.
 *  If the value is 1 or 0 we print the corresponding number and then NA
 *  next to it.
 *  If the number does not qualify to any od the other cases we have a
 *  factorizable number. On which case we have to show the number and
 *  it's factorization.
 * 
 * @param values 
 * @param matrix 
 * @param invalid_numbers 
 */

void print_results(array_int64_t* values, array_int64_t* matrix,
  array_int64_t* invalid_numbers) {
  for (size_t current_value_index = 0; current_value_index < values->count;
    ++current_value_index) {
    if (invalid_numbers->elements[current_value_index] == INVALID_NUMBER) {
      printf("invalid number");
    } else {
      printf("%"PRId64": ", values->elements[current_value_index]);
      for (size_t current_factors_index = 0;
          current_factors_index < matrix[current_value_index].count;
            ++current_factors_index) {
        if (matrix[current_value_index].elements[
          current_factors_index] == NA_NUMBER) {
          printf("NA");
        } else if (matrix[current_value_index].elements[
          current_factors_index] == NEGATIVE_NUMBER) {
          printf("invalid number");
        } else {
          printf("%"PRId64, matrix[current_value_index].elements[
          current_factors_index]);
          if (matrix[current_value_index].elements[
          current_factors_index+1] != 1) {
            printf("^%"PRId64, matrix[current_value_index].elements[
            current_factors_index+1]);
          }
        }
        if (current_factors_index+2 < matrix[current_value_index].count) {
          printf(" ");
        }
        current_factors_index += 1;
      }
    }
    printf("\n");
  }
}
