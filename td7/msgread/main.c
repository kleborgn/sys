#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

#define BUFF_SIZE 1024

int main() {

    key_t cle;
    int msg;

    cle = ftok("..", 1);

    if (cle == -1) {
        perror("ftok");
        return 1;
    }

    printf("Clé : %x\n", cle);

    msg = msgget(cle, 00600);

    if (msg == -1) {
        perror("msgget");
        return 1;
    }
    
    printf("Msg : %d\n", msg);

    char str[BUFF_SIZE];
    if (msgrcv(msg, str, BUFF_SIZE, 0, IPC_NOWAIT) == -1) {
        perror("msgrcv");
        return 1;
    }

    printf("Message : %s\n", str);
    
    return 0;
}

