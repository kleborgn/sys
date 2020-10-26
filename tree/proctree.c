#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

void prepend(char *s1, char *s2) {
    char *dup;
    sprintf(s1,"%s%s",s2,(dup=strdup(s1)));
    free(dup);
    //printf("%s\n",s1);
}

int extract_ppid(int un_pid, char *name) {
    char path[1024] = "/proc/";
    char s_pid[64];
    sprintf(s_pid, "%d", un_pid);
    strcat(path, s_pid);
    strcat(path, "/stat");
    FILE *f = fopen(path, "r");
    int ppid;
    int pid;
    char buff;

    fscanf(f, "%d (%[^)]) %c %d", &pid, name, &buff, &ppid);
    fclose(f);
    return ppid;
}

int recursive_tree(int pid, char *name, char *out) {
    char unproc[40];
    int ppid = extract_ppid(pid, name);
    sprintf(unproc, "%d (%s) > ", pid, name);
    prepend(out, unproc);

    if (pid == 1) {
        return 1;
    }

    recursive_tree(ppid, name, out);
    return 0;
}

int main(int argc, char *argv[])
{
    char nom[1024];
    char out[4096];

    if (argc != 2) {
        printf("Args error\n");
    } else {
        recursive_tree(atoi(argv[1]), nom, out);
        out[strlen(out)-2] = '\n';
        out[strlen(out)-1] = '\0';
        printf("%s", out);
    }
    return 0;
}
