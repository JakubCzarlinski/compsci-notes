// Copyright 2022 Jakub Czarlinski
// Wrapper for processes demo.

#include <stdio.h>
#include <stdlib.h>

#include "include/processes.h"

int main(int argc, char **argv) {
  if (argc != 1) {
    fprintf(stderr,
            "Error: Invalid number of arguments. Expected 1, got %d",
            argc - 1);
    exit(EXIT_FAILURE);
  }

  // First create a child process that will execute the `ls -l` command.
  // If it is successful, create another child process that will print a
  // message sent from a parent process.
  int result = createProcess();
  if (result == 0) {
    result = createProcessWithPipes();
  }

  return result;
}
