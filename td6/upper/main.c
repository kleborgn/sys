#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define RD_SIZE 1024

int main() {
    int fd;
    char buf[RD_SIZE];
    fd = open("../mon_tube", O_RDONLY);
    read(fd, buf, RD_SIZE);

    for (int i = 0; i < RD_SIZE; i++) {
        if ((buf[i] >= 'a') && (buf[i] <= 'z')) {
            buf[i] = buf[i] - 'a' + 'A';
        }
    }

    printf("%s\n", buf);
    close(fd);
    
    return 0;
}