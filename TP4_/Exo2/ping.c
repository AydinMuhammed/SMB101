#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>

volatile int p_points = 0; // Points du processus père
volatile int f_points = 0; // Points du processus fils
pid_t p_pid; // ID du processus père
pid_t f_pid; // ID du processus fils

// Gestionnaire de signaux
void sig_handler(int signal) {
    if (p_pid == getpid()) {
        printf("Père: Signal reçu\n");
        sleep(1); // Rajoute du délai
        if (rand() % 2) { // Une chance sur deux de renvoyer la balle
            printf("Père: Renvoie la balle\n");
            kill(f_pid, SIGUSR1);
        } else {
            printf("Père: Manque la balle\n");
            f_points++; // Incrémente les points du fils
            kill(f_pid, SIGUSR1);
        }
    } else {
        printf("Fils: Signal reçu\n");
        sleep(1); // Rajoute du délai
        if (rand() % 2) { // Une chance sur deux de renvoyer la balle
            printf("Fils: Renvoie la balle\n");
            kill(p_pid, SIGUSR1);
        } else {
            printf("Fils: Manque la balle\n");
            p_points++; // Incrémente les points du père
            kill(p_pid, SIGUSR1);
        }
    }
    if (p_points == 13) {
        printf("Père: J'ai gagné !\n");
        kill(f_pid, SIGTERM); // Envoie SIGTERM au fils pour terminer le jeu
        exit(EXIT_SUCCESS);
    } else if (f_points == 13) {
        printf("Fils: J'ai gagné !\n");
        kill(p_pid, SIGTERM); // Envoie SIGTERM au père pour terminer le jeu
        exit(EXIT_SUCCESS);
    }
}

int main() {
    srand(time(NULL));
    p_pid = getpid(); // Obtient l'ID du processus père
    f_pid = fork(); // Crée un processus fils
    if (f_pid < 0) {
        perror("Erreur lors de la création du processus fils");
        exit(EXIT_FAILURE);
    }
    if (f_pid == 0) {
        // Processus fils
        f_pid = getpid(); // Obtient l'ID du processus fils
        signal(SIGUSR1, sig_handler); // Associe le gestionnaire de signal au SIGUSR1
        while (1) {
            pause(); // Attente passive des signaux
        }
    } else {
        // Processus père
        signal(SIGUSR1, sig_handler); // Associe le gestionnaire de signal au SIGUSR1
        sleep(1);
        printf("Père: Envoie la balle\n");
        kill(f_pid, SIGUSR1); // Envoie SIGUSR1 au fils pour commencer le jeu

        while (1) {
            pause(); // Attente passive des signaux
        }
    }
    return 0;
}
