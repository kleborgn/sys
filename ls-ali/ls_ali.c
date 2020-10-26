#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stddef.h>
#include <dirent.h>
#include <string.h>

#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

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

        p_dirent = readdir(p_dir);

        while (p_dirent != NULL) {
            char path[1024];
            strcpy(path, argv[1]);
            strcat(path, "/");
            strcat(path, p_dirent->d_name);
            stat(path, &buff);

            // Inode number
            printf("%-16ld\t", buff.st_ino);

            // File type
            if((((buff.st_mode)) & 0170000u) == (0040000)) {
                printf("d\t");
            } else {
                printf("-\t");
            }

            // Rights
            printf( (buff.st_mode & 0400u) ? "r" : "-");
            printf( (buff.st_mode & 0200u) ? "w" : "-");
            printf( (buff.st_mode & 0100u) ? "x" : "-");
            printf( (buff.st_mode & (0400u >> 3u)) ? "r" : "-");
            printf( (buff.st_mode & (0200u >> 3u)) ? "w" : "-");
            printf( (buff.st_mode & (0100u >> 3u)) ? "x" : "-");
            printf( (buff.st_mode & ((0400u >> 3u) >> 3u)) ? "r" : "-");
            printf( (buff.st_mode & ((0200u >> 3u) >> 3u)) ? "w" : "-");
            printf( (buff.st_mode & ((0100u >> 3u) >> 3u)) ? "x" : "-");
            printf("\t");
            // man 7 inode to see consts

            // Links number
            printf("%ld\t", buff.st_nlink);

            // Name
            printf("%s\n", p_dirent->d_name);

            p_dirent = readdir(p_dir);
            
        }
        closedir(p_dir);
    }
    
    return 0;
}

