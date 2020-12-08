#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int pipefd[2];
    pid_t cpid;
    char buf;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) // Child
    {                     
        close(pipefd[1]); // Close unused

        while (read(pipefd[0], &buf, 1) > 0) // Child reads pipe
            printf("%s", &buf);

        printf("\n");
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);
    }
    else // Parent
    {                     
        close(pipefd[0]); // Close unused read end
        write(pipefd[1], argv[1], strlen(argv[1])); // Parent writes argv[1] to pipe
        close(pipefd[1]); // Reader will see EOF
        wait(NULL);       // Wait for child
        exit(EXIT_SUCCESS);
    }
}