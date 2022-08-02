// Copyright 2021 Ariel Solis, ariel.solismonge@ucr.ac.cr

#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <pthread.h>
#include "array_int64.h"

/**
 * \struct Shared Data
 * @details The data shared by the threads are the array of the values
 * to be factorized and the matrix that contains the factorization of
 * each number. Also contains the mutex, which all threads can access
 * and the index of the next number to be factorized.
 * 
 */

typedef struct {
  array_int64_t* values;
  array_int64_t* factors;
  size_t next_work_unit;
  pthread_mutex_t can_access_next_unit;
} shared_data_t;

void shared_data_init(shared_data_t* shared_data,
  array_int64_t* values, array_int64_t* factors);

#endif  // SHARED_DATA_H
