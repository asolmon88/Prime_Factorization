// Copyright [2021] Ariel Solis, ariel.solismonge@ucr.ac.cr
#ifndef READER_H
#define READER_H

#include <stddef.h>
#include <stdio.h>

#include "array_int64.h"

/**
 * \struct Dynamic array of int64_t
 * 
 */

typedef struct {
  FILE * file;
  array_int64_t* values;
  array_int64_t* invalid_numbers;
} reader_t;

void reader_init(reader_t* reader, FILE* file, array_int64_t* values,
  array_int64_t* invalid_numbers);

int read_file(reader_t* reader);


#endif  // READER_H
