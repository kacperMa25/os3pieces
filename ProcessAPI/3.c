#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int rc = fork();

    if (rc == 0) {
        printf("Hello\n");
    } else {
        wait(NULL);
        printf("Goodbye\n");
    }

    return EXIT_SUCCESS;
}
