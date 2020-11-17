#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void mon_action(int sig) {
    printf("Recu signal %d\n", sig);
}

int main() {
    int loop;

    printf("%d\n", getpid());
    signal(SIGTERM, mon_action);

    for (loop = 0; loop < 600; loop++) {
        printf("PID %d - Passage %d\n", getpid(), loop);
        sleep(5);
    }
    
    return 0;
}
