// Copyright 2021 Ariel Solis, ariel.solismonge@ucr.ac.cr

#include <assert.h>
#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include "reader.h"
#include "array_int64.h"
#include "mathmatician.h"
#include "printer.h"
#include "shared_data.h"
#include "private_data.h"
#include "thread_manager.h"

#define THREAD_COUNT_ERROR 10

// procedure main:
/**
 * @brief Main procedure, creates dynamic arrays, reads the file, creates
 *  the threads to calculate the prime factors
 *  and shows the result on screen, lastly fress all
 *  the memory.
 * 
 * 
 * @return int 
 */
int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  // create thread_count as result of converting argv[1] to integer
  // thread_count := integer(argv[1])
  uint64_t thread_count = sysconf(_SC_NPROCESSORS_ONLN);
  if (argc == 2) {
    if (sscanf(argv[1], "%" SCNu64, &thread_count) == 1) {
    } else {
      fprintf(stderr, "Error: invalid thread count\n");
      return THREAD_COUNT_ERROR;
    }
  }
//   initialize_data_structure values
  array_int64_t values;
  array_int64_init(&values);
  array_int64_t invalid_number_array;  // array to know if we have a valid
  // number or not.
  array_int64_init(&invalid_number_array);
//   read_file(file, values)
  reader_t reader;
  reader_init(&reader, stdin, &values, &invalid_number_array);
  if (read_file(&reader) == EXIT_SUCCESS) {
//   create_matrix(row_size: values_count, column: data_satructure)
    array_int64_t* factors = (array_int64_t*)
      malloc(values.count * sizeof(array_int64_t));
    for (size_t factors_rows = 0; factors_rows < values.count; ++factors_rows) {
      array_int64_init(&factors[factors_rows]);
    }

    shared_data_t shared_data;
    shared_data_init(&shared_data, &values, factors);

    if (thread_count > values.count) {
      thread_count = values.count;
    }

    // create_threads(thread_count, matrix, values) from thread_manager
    create_threads(&shared_data, thread_count);

//   print_results(matrix);
    print_results(&values, factors, &invalid_number_array);

    for (size_t factors_rows = 0; factors_rows < values.count; ++factors_rows) {
      array_int64_destroy(&(factors[factors_rows]));
    }
    free(factors);
    array_int64_destroy(&values);
    array_int64_destroy(&invalid_number_array);
  } else {
    fprintf(stderr, "Error: could not read file");
  }
  return error;
}  // end procedure
