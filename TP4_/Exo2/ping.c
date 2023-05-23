#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

int score_pere = 0, score_enfant = 0;

void handle_sigusr1(int sig) {
    printf("signal reçu\n");
    sleep(1);
    int random_number = rand() % 2;
    if (random_number == 1) {
        printf("Le papa renvoie la balle\n");
        kill(getppid(), SIGUSR1);
    } else {
        printf("Le papa manque la balle\n");
        kill(getppid(), SIGUSR2);
    }
}

void handle_sigusr2(int sig) {
    printf("signal reçu\n");
    sleep(1);
    int random_number = rand() % 2;
    if (random_number == 1) {
        printf("Le enfant renvoie la balle\n");
        kill(getppid(), SIGUSR2);
    } else {
        printf("Le enfant manque la balle\n");
        kill(getppid(), SIGUSR1);
    }
}

void handle_sigterm(int sig) {
    if (score_pere == 13) {
        printf("J'ai gagné !\n");
        kill(getpid(), SIGTERM);
    } else if (score_enfant == 13) {
        printf("Mon enfant a gagné !\n");
        kill(getpid(), SIGTERM);
    }
}

int main() {
    srand(time(NULL));
    signal(SIGUSR1, handle_sigusr1);
    signal(SIGUSR2, handle_sigusr2);
    signal(SIGTERM, handle_sigterm);
    
    pid_t pid = fork();

    if (pid == -1) {
        perror("Erreur dans la création du enfant\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // processus enfant
        while (1) {
            sleep(1);
        }
    } else {
        // processus père
        kill(pid, SIGUSR1);
        while (1) {
            sleep(1);
        }
    }
    return 0;
}

