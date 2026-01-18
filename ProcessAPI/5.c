#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int rc = fork();

    if (rc == 0) {
        int rc_wait = wait(NULL);
        printf("Parent PID %d, Wait return value %d\n", getpid(), rc_wait);
    } else {
        int rc_wait = wait(NULL);
        printf("Parent PID %d, Wait return value %d\n", getpid(), rc_wait);
    }

    return EXIT_SUCCESS;
}
