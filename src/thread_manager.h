// Copyright 2021 Ariel Solis, ariel.solismonge@ucr.ac.cr

#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <stdint.h>
#include "shared_data.h"

int create_threads(shared_data_t* shared_data, uint64_t thread_count);

#endif  // THREAD_MANAGER_H
