#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
int main() {
    pid_t pid;
    pid = fork();
    int status = 0;
    if (pid == 0) { // Fils
        printf("Je suis le fils, mon PID est %d et mon pere a le PID %d\n", getpid(), getppid());
    } else { // Pere
        printf("Je suis le pere, mon PID est %d et je viens de creer un fils de PID %d\n", getpid(), pid);
        for (size_t i = 0; i < 300; i++) {
            printf("Passage %d\n", i);
            sleep(1);
        }
        //wait(&status);
    }
    return EXIT_SUCCESS;
}
