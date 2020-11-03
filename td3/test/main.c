#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
int main(int argc, char *argv[]) {
int fd, loop, sum = 0;
struct stat stats;
char *map;
if (argc <= 1) {
printf("Manque un param !\n");
return 2;
}
fd = open(argv[1], O_RDONLY);
fstat(fd, &stats);
posix_fadvise(fd, 0, stats.st_size, POSIX_FADV_DONTNEED);
map = (char *)mmap(NULL, stats.st_size, PROT_READ, MAP_SHARED, fd, 0);
if (map == MAP_FAILED) {
perror("Erreur mmap()");
return 1;
}
for (loop = 0; loop < stats.st_size; loop++) {
sum += (int)map[loop];
}
munmap(map, stats.st_size);
return sum;
}

