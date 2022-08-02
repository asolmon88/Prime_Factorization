// Copyright [2021] Ariel Solis, ariel.solismonge@ucr.ac.cr
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "array_int64.h"


/**
 * @brief initialices a dynamic array of ints.
 * 
 * @details the capacity is the total amount of ints that can be inserted.
 *  the count is the amount of ints already in the array
 *  the elements are the elements in the array
 * 
 * @param array 
 */

void array_int64_init(array_int64_t* array) {
  assert(array);
  array->capacity = 0;
  array->count = 0;
  array->elements = NULL;
}

/**
 * @brief Method that destroys the array by setting capacity to 0,
 *  count to 0 and freeing the memory for the elements
 * 
 * @param array 
 */

void array_int64_destroy(array_int64_t* array) {
  assert(array);
  array->capacity = 0;
  array->count = 0;
  free(array->elements);
}

/**
 * @brief A method to add an int to the array
 * 
 * @details first checks that the array that we gave it exists
 *  Then we checks if the count is equal to the capacity, if it is we need to
 *  increase the capacity
 *  then we add the element to the array and increment the count by one
 *  the return values indicate ig the insertion was sucessfully done
 * 
 * @param array 
 * @param element 
 * @return int 
 */

int array_int64_append(array_int64_t* array, int64_t element) {
  assert(array);
  if (array->count == array->capacity) {
    if (array_int64_increase_capacity(array) != EXIT_SUCCESS) {
      return EXIT_FAILURE;
    }
  }
  array->elements[array->count++] = element;
  return EXIT_SUCCESS;
}

/**
 * @brief Method to increase the capacity of an array of ints
 * 
 * @details First we set a new capacity by multiplying the one we already have
 *  by 2.
 *  then we create a new pointer to store the new memory space for the
 *  new array.
 *  Then, if the new elements were sucessfully created, we asign the new
 *  values to our dynamic array.
 *  The return values indicate if the capacity was sucessfully increased.
 * 
 * @param array 
 * @return int 
 */

int array_int64_increase_capacity(array_int64_t* array) {
  assert(array);
  size_t new_capacity = 10 * (array->capacity ? array->capacity : 1);
  int64_t* new_elements = (int64_t*)
    realloc(array->elements, new_capacity*sizeof(int64_t));
  if (new_elements) {
    array->capacity = new_capacity;
    array->elements = new_elements;
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}

/**
 * @brief Method to print the elements of the array in the terminal
 * 
 * @details The method shows the array with the next format:
 *  [number, number, number].
 * 
 * @param array 
 */

void array_int64_print(array_int64_t* array) {
  assert(array);
  printf("[");
  for (size_t i = 0; i < array->count; ++i) {
    if (i < (array->count)-1) {
      printf("%" PRId64 ",", array->elements[i]);
    } else {
      printf("%" PRId64, array->elements[i]);
    }
  }
  printf("]\n");
}
