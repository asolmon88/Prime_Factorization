// Copyright [2021] Ariel Solis, ariel.solismonge@ucr.ac.cr
#ifndef MATHMATICIAN_H
#define MATHMATICIAN_H

#include <stdint.h>
#include "array_int64.h"

void calculate_prime_factors(int64_t value, array_int64_t* matrix,
  size_t matrix_index);
void add_factors(int64_t* current_value, int64_t current_factor,
  array_int64_t* matrix, size_t matrix_index);

#endif  // MATHMATICIAN_H
