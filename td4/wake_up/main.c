#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int pid;

    if (argc != 2) {
        printf("Nombre de parametres incorrect\n");
        return 1;
    }

    pid = atoi(argv[1]);

    if(kill(pid, SIGCONT) == 0) {
        printf("%d resume\n", pid);
    } else {
        printf("Erreur\n");
        return 1;
    }

    return 0;
}