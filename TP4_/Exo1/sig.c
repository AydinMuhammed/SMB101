#include <stdio.h>
#include <signal.h>

int counter = 0;



void sigint_handler(int signum)
{
    counter++;
}

void sigterm_handler(int signum)
{
    printf("Signal SIGTERM reçu. Terminaison du programme.\n");
    printf("Nombre total de signaux SIGINT reçus : %d\n", counter);
    exit(0);
}

int main()
{
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigterm_handler);

    while (1)
    {
        // Boucle sans fin
    }

    return 0;
}

// pour demarrer le programme : ./sig

// pour trouver le PID du programme : ps aux | grep sig (remplacer PID par le résulat obtenu)

// pour envoyer un signal SIGINT : - faire CTRL + C dans le terminal (vous pourrez observer en temps réel la sortie du programme)
//                                 - ou faire kill -SIGINT <PID> (mais vous ne pourrez pas observer en temps réel la sortie du programme)

// pour envoyer un signal SIGTERM : kill -SIGTERM <PID>

