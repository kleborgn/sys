#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>

int fini;

void do_job_pere()
{
    double pi, res;
    long loop;
    pi = 0;
    fini = false;
    loop = 1;
    while (!fini)
    {
        pi = pi + 1.0 / (double)pow(loop, 2);
        loop++;
    }
    res = sqrt(pi * 6);
    printf("PI = %.18f (précision : %e) en %ld itérations\n",
           res, (res - 3.141592653589793238462643383279502884197),
           loop);
}

void do_job_fils()
{
    double pi, res;
    long loop;
    pi = 0;
    loop = 1;
    while (!fini)
    {
        pi = pi + 1.0 / (double)pow(loop, 4);
        loop++;
    }
    res = pow(pi * 90, 0.25);
    printf("PI = %.18f (précision : %e) en %ld itérations\n",
           res, (res - 3.141592653589793238462643383279502884197),
           loop);
}

void handler(int sig) {
    fini = true;
}

int main()
{

    int timerA = 0;
    int timerB = 1;

    pid_t p;

    p = fork();

    if (p < 0)
    {
        fprintf(stderr, "Fork Failed");
        return 1;
    }

    // Parent process
    if (p > 0)
    {
        while (1)
        {
            signal(SIGUSR1, handler);
            printf("p : %d\n", timerA);
            timerA += 2;
            sleep(1);

            do_job_pere();
        }
    }

    // child process
    else
    {
        while (1)
        {
            printf("c : %d\n", timerB);
            timerB += 2;
            sleep(1);

            do_job_fils();
        }
        
    }
}