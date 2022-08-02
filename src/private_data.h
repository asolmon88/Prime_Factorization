// Copyright 2021 Ariel Solis, ariel.solismonge@ucr.ac.cr

#ifndef PRIVATE_DATA_H
#define PRIVATE_DATA_H

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include "array_int64.h"
#include "shared_data.h"

/**
 * \struct stores the private data of a thread
 * @details All threads most have the index of the current number
 * that it will factorize.
 * Also it needs to have access to the shared data.
 * 
 */

typedef struct {
  size_t my_unit;
  shared_data_t* shared_data;
} private_data_t;

void private_data_init(private_data_t* private_data, shared_data_t* shared_data,
  uint64_t thread_count);

#endif  // PRIVATE_DATA_H
