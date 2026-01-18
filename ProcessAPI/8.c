#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MSG_SIZE 7

const char msg1[] = "Siemka1";
const char msg2[] = "Siemka2";
const char msg3[] = "Siemka3";

int main(int argc, char* argv[])
{

    int fd[2];
    if (pipe(fd) < 0)
        exit(1);

    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "Couldn't fork\n");
        exit(1);
    } else if (rc == 0) {
        printf("Hello from writer PID: %d\n", getpid());
        close(fd[0]);
        write(fd[1], msg1, MSG_SIZE);
        write(fd[1], msg2, MSG_SIZE);
        write(fd[1], msg3, MSG_SIZE);
        close(fd[1]);

    } else {
        int rc2 = fork();

        if (rc2 < 0) {
            fprintf(stderr, "Couldn't fork\n");
            exit(1);
        } else if (rc2 == 0) {
            printf("Hello from reader PID: %d\n", getpid());

            int nbytes;
            char msgR[MSG_SIZE];

            close(fd[1]);
            while ((nbytes = read(fd[0], msgR, MSG_SIZE)) > 0) {
                printf("Read: %s\n", msgR);
            }
            if (nbytes != 0)
                exit(2);
            printf("Finished reading PID %d\n", getpid());
            close(fd[0]);

        } else {
            close(fd[0]);
            close(fd[1]);
            printf("Hello from parent PID: %d\n", getpid());
            waitpid(rc, NULL, 0);
            waitpid(rc2, NULL, 0);
        }
    }

    return EXIT_SUCCESS;
}
