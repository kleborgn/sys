#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int c2l_fd;
    int l2c_fd;
    int cp_fd;
    int floor;
    char status;

    while (1)
    {
        
        c2l_fd = open("../call2lift", O_NONBLOCK | O_WRONLY);

        if (c2l_fd == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }

        l2c_fd = open("../lift2call", O_NONBLOCK | O_RDONLY);

        if (l2c_fd == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }

        cp_fd = open("../call_pipe", O_NONBLOCK | O_RDONLY);

        if (cp_fd == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }

        read(cp_fd, &floor, sizeof(char));
        printf("call : appel au %d ème etage.\n", floor-48);

        read(l2c_fd, &status, sizeof(char));

        while (status != '#')
        {
            read(l2c_fd, &status, sizeof(char));
        }

        printf("call : ascenseur signale qu'il est libre.\n");
        write(c2l_fd, &floor, sizeof(char));

        close(c2l_fd);
        close(l2c_fd);
        close(cp_fd);
    }
}