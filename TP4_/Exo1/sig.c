#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int counter = 0;



void sigint_handler(int signum)
{
    counter++;
    printf("Nombre total de signaux SIGINT reçus : %d\n", counter);
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

/* pour demarrer le programme : ./sig

pour trouver le PID du programme executer dans un autre terminal: ps aux | grep sig )
le pid correspond au nombre dans la deuxième colonne (exemple : 7124) dans la ligne qui contient le nom du programme (ici : ./sig)

(remplacer PID par le résulat obtenu dans la commande précédente)
pour envoyer un signal SIGINT : - faire CTRL + C dans le terminal (vous pourrez observer en temps réel la sortie du programme (^C affiché))
                                - ou faire kill -SIGINT <PID> (vous pourrez observer en temps réel la sortie du programme dans le premier terminal mais  il faut l'executer dans un autre terminal)

pour envoyer un signal SIGTERM : kill -SIGTERM <PID> (il faut l'executer dans un autre terminal, cela mettre fin au programme et vous verrez dans le terminal où le programme est executé le nombre de signaux SIGINT reçus) */

