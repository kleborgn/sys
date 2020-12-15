#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

int main() {

    key_t cle;
    int msg;

    cle = ftok("..", 1);

    if (cle == -1) {
        perror("ftok");
        return 1;
    }

    printf("Clé : %x\n", cle);

    msg = msgget(cle, IPC_CREAT | 00600);

    if (msg == -1) {
        perror("msgget");
        return 1;
    }

    printf("Msg : %d\n", msg);
    
    return 0;
}

