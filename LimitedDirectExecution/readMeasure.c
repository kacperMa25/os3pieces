#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    const int iterations = 1000;
    int fd = open("./siemka.txt", O_CREAT | O_TRUNC | O_RDWR);

    time_t sum = 0;
    struct timespec start, end;

    for (int i = 0; i < iterations; ++i) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        read(fd, NULL, 0);
        clock_gettime(CLOCK_MONOTONIC, &end);
        sum += end.tv_nsec - start.tv_nsec;
    }
    sum /= iterations;

    printf("Avg time over %d iterations: %ld", iterations, sum);
    return 0;
}
