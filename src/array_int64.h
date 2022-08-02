// Copyright [2021] Ariel Solis, ariel.solismonge@ucr.ac.cr
#ifndef ARRAY_INT64_H
#define ARRAY_INT64_H

#include <stddef.h>
#include <stdint.h>

/**
 * \struct Dynamic array of int64_t
 * 
 */

typedef struct {
  size_t capacity;
  size_t count;
  int64_t* elements;
} array_int64_t;

void array_int64_init(array_int64_t* array);
void array_int64_destroy(array_int64_t* array);
int array_int64_append(array_int64_t* array, int64_t element);
int array_int64_increase_capacity(array_int64_t* array);
void array_int64_print(array_int64_t* array);

#endif  // ARRAY_INT64_H
