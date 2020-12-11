#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define TIMEB2FLOOR 2

int main()
{
    int c2l_fd;
    int l2c_fd;
    char status;
    int floor, init_floor, t_wait;

    while (1)
    {
        
        c2l_fd = open("../call2lift", O_NONBLOCK | O_RDONLY);

        if (c2l_fd == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }

        
        l2c_fd = open("../lift2call", O_NONBLOCK | O_WRONLY);

        if (l2c_fd == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }

        status = '#';
        init_floor = 0;

        read(c2l_fd, &floor, sizeof(char));

        t_wait = (floor-48) * TIMEB2FLOOR;

        printf("lift : ascenseur appelé au %d ème etage, temps estimé : %d s\n", floor-48, t_wait);
        sleep(t_wait);
        printf("lift : ascenseur retourne au RDC, temps estimé : %d s\n", t_wait);
        sleep(t_wait);

        printf("lift : ascenseur libre, temps total : %d s\n", t_wait*2);
        write(l2c_fd, &status, sizeof(char));

        close(c2l_fd);
        close(l2c_fd);
    }
}