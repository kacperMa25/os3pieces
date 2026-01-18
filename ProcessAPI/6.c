#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int rc = fork();

    if (rc == 0) {
        printf("Child PID %d\n", getpid());
    } else {
        int status;
        int rc_wait = waitpid(-1, &status, 0);
        printf("Parent PID %d, Wait return value %d, Status %d\n", getpid(), rc_wait, status);
    }

    return EXIT_SUCCESS;
}
