#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int p = open("./text.txt", O_CREAT | O_RDWR | O_TRUNC);
    fork();
    char* string = (char*)malloc(100 * sizeof(char));

    sprintf(string, "Hello from PID %d\n", getpid());

    write(p, string, strlen(string));
    free(string);
}
