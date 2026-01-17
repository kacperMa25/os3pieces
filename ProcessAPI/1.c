#include <stdio.h>
#include <unistd.h>

int main()
{
    int x = 100;
    fork();

    x = 10;
    printf("PID: %d, x = %d\n", getpid(), x);
}
