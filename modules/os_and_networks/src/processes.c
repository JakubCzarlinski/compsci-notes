// Copyright 2022 Jakub Czarlinski
// Processes demonstrates how to create processes in c.
// Tested on WSL2.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "include/processes.h"

/** @brief  Creates a child process and waits for it to finish. The child
 *          process executes the `ls -l` command.
 *  @return -1 if failed, 0 if success
 */
int createProcess() {
  printf("------------------\n");
  printf("Child Process Demo\n");
  printf("------------------\n");

  pid_t childPid = 0;
  childPid = fork();

  if (childPid < 0) {
    // For failed forks, PID is negative.
    fprintf(stderr, "Error: Failed to fork.");
    return -1;

  } else if (childPid == 0) {
    // The child sees it's PID as 0, because at the moment the process is
    // forked, pid = 0. So the memory that is copied, includes the pid = 0.
    execlp("/bin/ls", "ls", "-l", NULL);

  } else {
    // Wait untill any of child processes have finished.
    wait(NULL);
    printf("Child completed successfully.\n");
  }

  return 0;
}

/**
 *  @brief  Creates a child process that will be sent a message to print.
 *  @return On success, returns 0. On failure, returns -1. errno is set
 *          appropriately.
 */
int createProcessWithPipes() {
  printf("------------------\n");
  printf("     Pipe Demo    \n");
  printf("------------------\n");

  pid_t childPid = 0;

  // The pipe has a read and write end. File descriptors are used to access the
  // ends of the pipe. The read end is `parentToChild[0]` and the write
  // end is `parentToChild[1]`.
  int parentToChild[2];
  int childToParent[2];
  char *buffer = calloc(BUFSIZ, sizeof(char));

  if (pipe(parentToChild) < 0) {
    printf("Error: Failed to create parent to child pipe.\n");
    return -1;
  }
  if (pipe(childToParent) < 0) {
    printf("Error: Failed to create child to parent pipe.\n");
    return -1;
  }

  childPid = fork();
  if (childPid < 0) {
    printf("Error: Fork Failed");
    return -1;

  } else if (childPid == 0) {
    // Child process reads the message from parent first, then sends a message
    // back.
    close(parentToChild[1]);
    close(childToParent[0]);

    read(parentToChild[0], buffer, BUFSIZ);
    close(parentToChild[0]);

    write(childToParent[1], "Hello from child process", BUFSIZ);
    close(childToParent[1]);
    printf("Child: %s\n", buffer);
    free(buffer);
    exit(EXIT_SUCCESS);

  } else {
    // Parent process: first sends a message to child, then receives a message
    // back.
    int result = -1;

    close(parentToChild[0]);
    close(childToParent[1]);

    // Parent writes to the pipe.
    write(parentToChild[1], "Hello from parent process", BUFSIZ);
    close(parentToChild[1]);

    read(childToParent[0], buffer, BUFSIZ);
    close(childToParent[0]);

    printf("Parent: %s\n", buffer);
    free(buffer);

    wait(&result);

    printf("Parent: status = %i\n", result);
  }

  return 0;
}
