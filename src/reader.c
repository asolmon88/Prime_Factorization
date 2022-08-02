// Copyright [2021] Ariel Solis, ariel.solismonge@ucr.ac.cr
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "array_int64.h"
#include "reader.h"

#define VALID_NUMBER 1
#define INVALID_NUMBER 0

/**
 * @brief Method to initialize a reader by setting each of it's attributes
 *  to the parameters.
 * 
 * @param reader 
 * @param file 
 * @param values 
 * @param invalid_numbers 
 */

void reader_init(reader_t* reader, FILE* file, array_int64_t* values,
  array_int64_t* invalid_numbers) {
  assert(reader);
  reader->file = file;
  reader->invalid_numbers = invalid_numbers;
  reader->values = values;
}

// procedure read_file(file, values):
/**
 * @brief Reads a file and stores the numbers in a dynamic array
 * 
 * @details First, checks if the array and file we gave it are not null
 *  Then it starts a while to read the numbers from the files.
 *  We know that when fscanf returns 1 and the errno is 0 it means
 *  we have a number, which results in adding that number to the
 *  array.
 *  If errno is 34, that's when fscanf reads a number too big for the one
 *  we want. On that case we add a 1 to the array and a 0 to the invalid number
 *  if none of that happens, we have a line of characters, we then iterate
 *  through them until we are at EOF or \n. If we didn't get to the EOF
 *  that means another number is coming, so we add a 1 and a 0 to each array.
 *  In the case that the values array wasn't modified we return that we
 *  couldn't read the file.
 * 
 * @param file 
 * @param values 
 * @param invalid_number 
 * @return int 
 */
int read_file(reader_t* reader) {
//   current_number = 0
  assert(reader);
  int error_code = 0;
  int64_t current_number = 0;
//   while current_number:
//     save_number_in_current_file_line in current_number
//     if number_saved_sucessfull:
  int number_found = 1;
  while (number_found == 1) {
//    add current_number to values
    error_code = fscanf(reader->file, "%" SCNd64, &current_number);
    if (error_code == 1 && errno == 0) {
      array_int64_append(reader->values, current_number);
      array_int64_append(reader->invalid_numbers, VALID_NUMBER);
    } else if (errno == 34) {
      array_int64_append(reader->invalid_numbers, INVALID_NUMBER);
      array_int64_append(reader->values, 1);
      errno = 0;
    } else {
      char ignore_character = 'a';
      while (ignore_character != '\n' && ignore_character != EOF) {
        ignore_character = fgetc(reader->file);
      }
      if (ignore_character == EOF) {
        number_found = 0;
      } else {
        array_int64_append(reader->invalid_numbers, INVALID_NUMBER);
        array_int64_append(reader->values, 1);
      }
    }
    if (error_code == EOF) {
      number_found = 0;
    }
  }  //   end while
  if (reader->values->count > 0) {
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}  // end procedure
