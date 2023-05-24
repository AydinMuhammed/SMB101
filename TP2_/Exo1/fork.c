#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//pour compiler 
// gcc -o fork fork.

//pour exécuter l'exécutable
// ./fork

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Processus fils
        printf("Processus fils - PID: %d, PID du père: %d\n", getpid(), getppid());
        int exitCode = getpid() % 10;
        exit(exitCode);
    } else {
        // Processus père
        printf("Processus père - PID du fils: %d\n", pid);
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            int exitCode = WEXITSTATUS(status);
            printf("Code de retour du fils: %d\n", exitCode);
        }
    }

    return 0;
}
