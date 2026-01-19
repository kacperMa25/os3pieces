#define _GNU_SOURCE

#include <err.h>
#include <math.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
    unsigned int iterations = 1000000;
    int64_t estiamated = 0;
    int threshold = ceil(iterations * 0.0001);
    char buff = 'x';
    struct timespec start, end;

    int pipeFdA[2], pipeFdB[2];
    if (pipe(pipeFdA) < 0 || pipe(pipeFdB) < 0)
        err(EXIT_FAILURE, "pipe");

    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(2, &set);
    sched_setaffinity(0, sizeof(set), &set);

    switch (fork()) {
    case -1:
        err(EXIT_FAILURE, "fork");
    case 0:
        close(pipeFdA[1]);
        close(pipeFdB[0]);
        for (unsigned int i = 0; i < iterations; ++i) {
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            write(pipeFdB[1], &buff, 1);
            read(pipeFdA[0], &buff, 1);
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            if (i > threshold) {
                int64_t delta = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
                estiamated += delta;
            }
        }
        close(pipeFdA[0]);
        close(pipeFdB[1]);
        printf("Done reading\n");
        estiamated /= (iterations - threshold) * 2;
        printf("%ld\n", estiamated);
        break;
    default:
        close(pipeFdA[0]);
        close(pipeFdB[1]);
        for (unsigned int i = 0; i < iterations; ++i) {
            write(pipeFdA[1], &buff, 1);
            read(pipeFdB[0], &buff, 1);
        }
        close(pipeFdA[1]);
        close(pipeFdB[0]);
        printf("Done writing\n");
        wait(NULL);
        break;
    }

    return EXIT_SUCCESS;
}
