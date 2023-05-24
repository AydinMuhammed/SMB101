#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>


// pour complier le code 
// gcc -o deuxieme deuxieme.c

//pour exécuter l'éxecutable 
//./deuxieme "message"


int main(int argc, char *argv[]) {
    // Vérifie le nombre d'arguments
    if (argc < 2) {
        printf("Usage: %s <message>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Affiche le message passé en argument
    printf("Message: %s\n", argv[1]);

    // Crée un processus fils
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Processus fils
        printf("Processus fils - PID: %d\n", getpid());

        // Crée un fichier temporaire
        char template[] = "/tmp/proc-exercise-XXXXXX";
        int fd = mkstemp(template);
        printf("Numéro du descripteur de fichier ouvert: %d\n", fd);

        if (fd == -1) {
            perror("mkstemp");
            exit(EXIT_FAILURE);
        }

        // Redirige la sortie standard vers le descripteur de fichier
        dup2(fd, STDOUT_FILENO);

        // Ferme le descripteur de fichier non nécessaire
        close(fd);

        // Exécute le programme "deuxieme" avec les arguments restants
        execvp("./deuxieme", &argv[1]);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        // Processus père
        printf("Processus père - PID: %d\n", getpid());

        // Attend la fin du processus fils
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            printf("That’s All Folks !\n");
        }
    }

    return 0;
}
