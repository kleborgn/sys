#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define WR_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Nombre de parametres incorrect\n");
        return 1;
    }

    int fd;
    fd = open("../mon_tube", O_WRONLY);

    for (int i = 1; i < argc; i++) {
        write(fd, argv[i], WR_SIZE);
    }

    close(fd);
    return 0;
}