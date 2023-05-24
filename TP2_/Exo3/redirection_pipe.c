#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

int main() {
	int pipefd[2];
	if (pipe(pipefd) == -1) {
    	perror("Erreur lors de la création du pipe");
    	return 1;
	}

	pid_t ps_pid = fork();
	if (ps_pid == -1) {
    	perror("Erreur lors de la création du processus fils pour 'ps'");
    	return 1;
	} else if (ps_pid == 0) {
    	// Processus fils pour 'ps'

    	// Rediriger la sortie standard vers l'extrémité d'écriture du pipe
    	if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
        	perror("Erreur lors de la redirection de la sortie standard pour 'ps'");
        	return 1;
    	}

    	// Fermer les descripteurs de fichiers inutilisés
    	close(pipefd[0]);
    	close(pipefd[1]);

    	// Exécuter la commande "ps eaux"
    	execlp("ps", "ps", "eaux", NULL);

    	// En cas d'erreur d'exécution de la commande, afficher un message d'erreur
    	perror("Erreur lors de l'exécution de 'ps eaux'");
    	return 1;
	}

	// Processus parent

	pid_t grep_pid = fork();
	if (grep_pid == -1) {
    	perror("Erreur lors de la création du processus fils pour 'grep'");
    	return 1;
	} else if (grep_pid == 0) {
    	// Processus fils pour 'grep'

    	// Rediriger l'entrée standard vers l'extrémité de lecture du pipe
    	if (dup2(pipefd[0], STDIN_FILENO) == -1) {
        	perror("Erreur lors de la redirection de l'entrée standard pour 'grep'");
        	return 1;
    	}

    	// Fermer les descripteurs de fichiers inutilisés
    	close(pipefd[0]);
    	close(pipefd[1]);

    	// Ouvrir le fichier /dev/null en écriture
    	int devNull = open("/dev/null", O_WRONLY);

    	// Rediriger la sortie standard vers /dev/null
    	if (dup2(devNull, STDOUT_FILENO) == -1) {
        	perror("Erreur lors de la redirection de la sortie standard vers '/dev/null'");
        	return 1;
    	}

    	// Exécuter la commande "grep '^root '"
    	execlp("grep", "grep", "^root", NULL);

    	// En cas d'erreur d'exécution de la commande, afficher un message d'erreur
    	perror("Erreur lors de l'exécution de 'grep \"^root\"'");
    	return 1;
	}

	// Processus parent

	// Fermer les descripteurs de fichiers inutilisés
	close(pipefd[0]);
	close(pipefd[1]);

	// Attendre la fin de l'exécution des processus fils
	waitpid(ps_pid, NULL, 0);
	waitpid(grep_pid, NULL, 0);

	// Afficher le message final avec la primitive write
	char message[] = "root est connecté\n";
	write(STDOUT_FILENO, message, strlen(message));

	return 0;
}



