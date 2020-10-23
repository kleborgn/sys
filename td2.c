#include <stdio.h>
#include <string.h>

int extract_ppid(int un_pid, char *name) {
    char path[1024] = "/proc/";
    char s_pid[64];
    int ppid;
    int pid;
    char buff;
    sprintf(s_pid, "%d", un_pid);
    strcat(path, s_pid);
    strcat(path, "/stat");
    FILE *f = fopen(path, "r");
    

    fscanf(f, "%d (%[^)]) %c %d", &pid, name, &buff, &ppid);
    fclose(f);
    return ppid;
}

int main() {
    char nom[30];
    printf("PPID (%s) : %d\n", nom, extract_ppid(2285, nom));
    return 0;
    }