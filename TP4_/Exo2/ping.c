#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>

int score_pere = 0, score_enfant = 0;

void handle_sigusr1(int sig) {
    int random_number = rand() % 2;
    if (random_number == 1) {
        printf("Le papa renvoie la balle\n");
        kill(getppid(), SIGUSR1);
        score_pere++;
    } else {
        printf("Le papa manque la balle\n");
        kill(getppid(), SIGUSR2);
        score_enfant++;
    }
    printf("Signal reçu (score : papa = %d, enfant = %d)\n", score_pere, score_enfant);
    sleep(1);
}

void handle_sigusr2(int sig) {
    int random_number = rand() % 2;
    if (random_number == 1) {
        printf("Le enfant renvoie la balle\n");
        kill(getppid(), SIGUSR2);
        score_enfant++;
    } else {
        printf("Le enfant manque la balle\n");
        kill(getppid(), SIGUSR1);
        score_pere++;
    }
    printf("Signal reçu (score : papa = %d, enfant = %d)\n", score_pere, score_enfant);
    sleep(1);
}

void handle_sigterm(int sig) {
    if (score_pere == 13) {
        printf("J'ai gagné !\n");
    } else if (score_enfant == 13) {
        printf("Mon enfant a gagné !\n");
    }
    exit(EXIT_SUCCESS);
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
        while (score_enfant < 13 && score_pere < 13) {
            sleep(1);
        }
    } else {
        // processus père
        kill(pid, SIGUSR1);
        while (score_enfant < 13 && score_pere < 13) {
            sleep(1);
        }
    }

    // Nettoyage et terminaison
    if (pid == 0) {
        // processus enfant
        if (score_enfant == 13) {
            printf("Mon enfant a gagné !\n");
        }
    } else {
        // processus père
        if (score_pere == 13) {
            printf("J'ai gagné !\n");
        }
    }

    printf("Appuyez sur une touche pour quitter...\n");
    getchar();
    
    return 0;
}

// pour tester le programme : ./ping