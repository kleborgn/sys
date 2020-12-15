#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <math.h>

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
        signal(SIGUSR1, handler);
        while (1)
        {
            
            fini = false;
            printf("p : %d\n", timerA);
            timerA += 2;
            sleep(1);
            kill(p, SIGUSR1);
            do_job_pere();
        }
    }

    // child process
    else
    {
        signal(SIGUSR1, handler);
        pause();
        while (1)
        {
            
            fini = false;
            printf("c : %d\n", timerB);
            timerB += 2;
            sleep(1);
            kill(getppid(), SIGUSR1);
            do_job_fils();
        }
        
    }
}