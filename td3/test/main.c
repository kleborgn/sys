#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

void reverseArray(char arr[], int start, int end)
{
    int temp;
    while (start < end)
    {
        temp = arr[start];   
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }   
}     

int main(int argc, char *argv[])
{
    int fd = 0;
    struct stat stats;
    char *map;

    if (argc <= 1)
    {
        printf("Manque un param !\n");
        return 2;
    }

    fd = open(argv[1], O_RDWR);
    fstat(fd, &stats);

    map = mmap(NULL, stats.st_size, PROT_WRITE, MAP_SHARED, fd, 0);

    if (map == MAP_FAILED)
    {
        perror("Erreur mmap()");
        return 1;
    }
    
    reverseArray(map, 0, stats.st_size - 1);
    
    munmap(map, stats.st_size);
    return 0;
}
