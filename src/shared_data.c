// Copyright 2021 Ariel Solis, ariel.solismonge@ucr.ac.cr

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include "array_int64.h"
#include "shared_data.h"

/**
 * @brief Method to initialize the values and factors with the ones given.
 * 
 * @param shared_data 
 * @param values 
 * @param factors 
 */

void shared_data_init(shared_data_t* shared_data,
  array_int64_t* values, array_int64_t* factors) {
  assert(values);
  assert(factors);
  shared_data->values = values;
  shared_data->factors = factors;
  pthread_mutex_init(&shared_data->can_access_next_unit, NULL);
  shared_data->next_work_unit = 0;
}
