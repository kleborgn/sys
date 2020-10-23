#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stddef.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[])
{
    DIR *p_dir = NULL;
    struct dirent *p_dirent = NULL;
    struct stat buff;
    char path[1024];
    strcpy(path, argv[1]);
    
    if (argc != 2) {
        printf("Nombre de parametres incorrect\n");
    } else {
        p_dir = opendir(argv[1]);

        //p_dirent = readdir(p_dir); // .
        //p_dirent = readdir(p_dir); // ..
        p_dirent = readdir(p_dir);

        while (p_dirent != NULL) {
            char path[1024];
            strcpy(path, argv[1]);
            strcat(path, "/");
            strcat(path, p_dirent->d_name);
            stat(path, &buff);
            // Inode number
            printf("%ld\t", buff.st_ino);
            // File type
            if(S_ISDIR(buff.st_mode)) {
                printf("d\t");
            } else {
                printf("-\t");
            }
            // Rights
            //printf("%lo\t", (unsigned long) p_buff->st_mode);
            // man 7 inode to see consts
            // Links number
            printf("%ld\t", buff.st_nlink);

            printf("%s\n", p_dirent->d_name);

            p_dirent = readdir(p_dir);
            
        }
        closedir(p_dir);
    }
    
    return 0;
}

