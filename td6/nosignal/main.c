#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main()
{

    int fd1[2];
    int fd2[2];

    int timerA = 0;
    int timerB = 1;

    int isReady = 0;

    pid_t p;

    if (pipe(fd1) == -1)
    {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }
    if (pipe(fd2) == -1)
    {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    p = fork();

    if (p < 0)
    {
        fprintf(stderr, "Fork Failed");
        return 1;
    }

    while (1)
    {
        // Parent process
        if (p > 0)
        {

            printf("p : %d\n", timerA);
            timerA += 2;
            sleep(1);

            isReady = 1;
            write(fd1[1], &isReady, sizeof(int));
            isReady = 0;
            read(fd2[0], &isReady, sizeof(int));
            isReady = 0;
        }

        // child process
        else
        {
            read(fd1[0], &isReady, sizeof(int));
            isReady = 0;
            
            printf("c : %d\n", timerB);
            timerB += 2;
            sleep(1);

            isReady = 1;
            write(fd2[1], &isReady, sizeof(int));
            isReady = 0;
            
        }
    }
}