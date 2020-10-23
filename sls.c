#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stddef.h>

int main(int argc, char *argv[])
{
    DIR *p_dir;
    struct dirent *p_dirent;
    if (argc != 2) {
        printf("Nombre de parametres incorrect\n");
    } else {
        p_dir = opendir(argv[1]);

        //p_dirent = readdir(p_dir); // .
        //p_dirent = readdir(p_dir); // ..
        p_dirent = readdir(p_dir);

        while (p_dirent != NULL) {
            
            printf("%d, %s\n", p_dirent->d_ino, p_dirent->d_name);
            p_dirent = readdir(p_dir);
        }
    }
    
    return 0;
}
