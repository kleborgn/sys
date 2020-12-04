#include <stdlib.h>
#include <stdio.h>

int main() {
    system("ls -l | tail -n +2 | wc -l");
    printf("Avant\n");
    system("sleep 5");
    printf("Apres\n");
    return EXIT_SUCCESS;
}
