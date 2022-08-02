// Copyright 2021 Ariel Solis, ariel.solismonge@ucr.ac.cr

#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_int64.h"
#include "mathmatician.h"
#include "shared_data.h"
#include "private_data.h"
#include "thread_manager.h"

#define ERROR_THREADS 12

void* distribute_work(void* data);

/**
 * @brief Creates the threads and the private data for threads
 *  also separates the workload between threads.
 * @details Firstly, if the number of threads is more than the number of
 * numbers, we take the number of threads as the amount of numbers, and
 * just create the ones we need. If not then we calculate how many numbers
 * correspond to each thread by divinding the amount of numbers by the
 * amount of threads. After that we calculate the remainder of the division
 * the calculate the amount of extra threads to be distributed. After the
 * distribution is done we create the threads and calculate the factors.
 * 
 * @param shared_data 
 * @param thread_count 
 * @return int 
 */

// procedure create_threads(thread_count, matrix, values) do
int create_threads(shared_data_t* shared_data, uint64_t thread_count) {
  assert(shared_data);
  // initialize array of threads with thread_count
  pthread_t* threads = (pthread_t*)malloc(thread_count*sizeof(pthread_t));
  // create array of private variables with thread_count
  private_data_t* private_data = (private_data_t*)
    calloc(thread_count, sizeof(private_data_t));

  if (threads && private_data) {
    for (uint64_t index = 0; index < thread_count; ++index) {
      private_data[index].shared_data = shared_data;
    }

    struct timespec start_time, finish_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    // for index := 0 to thread_count do
    for (uint64_t index = 0; index < thread_count; ++index) {
      // create_thread(threads in index, distribute_work, private_data)
      pthread_create(&threads[index], NULL, distribute_work,
        &private_data[index]);
    }  // end

    for (uint64_t current_thread = 0; current_thread < thread_count;
      ++current_thread) {
      pthread_join(threads[current_thread], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &finish_time);
    double elapsed_time = finish_time.tv_sec - start_time.tv_sec +
      (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;
    FILE* duration = fopen("duration.txt", "w");
    fprintf(duration, "Execution time: %.9lfs\n", elapsed_time);
    fclose(duration);

    pthread_mutex_destroy(&shared_data->can_access_next_unit);
    free(private_data);
    free(threads);
  } else {  // end procedure
    fprintf(stderr, "Error, could not allocate that many threads\n");
    return ERROR_THREADS;
  }
  return EXIT_SUCCESS;
}

/**
 * @brief Method to distribute work in a dynamic mapping way
 * 
 * @details The method distributes work of threads by
 * locking the variable that has the index of the next number to
 * be factorized in values. The mutex locks when a thread needs
 * to access this variable and unlocks it after the variable has been assigned
 * and incremented to be ready for the next thread.
 * 
 * @param data 
 * @return void* 
 */

// procedure distribute_work(private_data) do
void* distribute_work(void* data) {
  assert(data);
  private_data_t* private_data = (private_data_t*) data;
  shared_data_t* shared_data = private_data->shared_data;
  // while (true) do
  while (true) {
    // lock(can_access_next_unit)
    pthread_mutex_lock(&shared_data->can_access_next_unit);
      // private my_unit = next_work_unit
      // next_work_unit = next_work_unit + 1
      private_data->my_unit = shared_data->next_work_unit++;
    // unlock(can_access_next_unit)
    pthread_mutex_unlock(&shared_data->can_access_next_unit);
    // if (my_unit < values_count) do
    if (private_data->my_unit < shared_data->values->count) {
      // calculate_prime_factors(value in index, matrix, index)
      calculate_prime_factors(
        shared_data->values->elements[private_data->my_unit],
        shared_data->factors, private_data->my_unit);
    // end
    // else do
    } else {
      // break
      break;
    }  // end
  }  // end
  return NULL;
}  // end
