#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int rc = fork();

    if (rc == 0) {
        char* args[2] = { "ls", NULL };

        execvp(args[0], args);
    } else {
        wait(NULL);
    }

    return EXIT_SUCCESS;
}
