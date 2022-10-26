// Processes demonstrates how to create processes in c. 
// Tested on WSL2.

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t childPid = 0;
    int status;

    childPid = fork();

    if (childPid < 0) {
        // For failed forks, PID is negative.
        printf("Error: Fork Failed");
        return 1;

    } else if (childPid == 0) {
        // The child sees it's PID as 0, because at the moment the process is
        // forked, pid = 0. So the memory that is copied, includes the pid = 0.
        // execlp("/bin/ls", "ls", NULL);
        execlp("/bin/ls", "ls", "-l", NULL);

    } else {
        // Wait untill any of child processes have finished.
        wait(NULL);
        printf("Child completed successfully.\n");
    }

    return 0;
}