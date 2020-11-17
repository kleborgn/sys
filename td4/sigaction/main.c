#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void handler(int sig, siginfo_t *siginfo, void *contexte) {
    printf("Recu signal %d depuis %d par %d\n", sig, siginfo->si_pid, siginfo->si_uid);
}

int main() {
    int loop;
    struct sigaction act;
    memset (&act, '\0', sizeof(act));
    act.sa_sigaction = handler;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGTSTP, &act, NULL);

    printf("%d\n", getpid());

    for (loop = 0; loop < 600; loop++) {
        printf("PID %d - Passage %d\n", getpid(), loop);
        sleep(5);
    }
    
    return 0;
}
