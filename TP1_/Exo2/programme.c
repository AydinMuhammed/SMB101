#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    // Vérifie si le nom de fichier est fourni en argument
    if (argc < 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }
    
    // Ouvre le fichier en lecture seule
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf("Error: failed to open file %s\n", argv[1]);
        return 1;
    }
    
    // Obtient la taille du fichier
    off_t size = lseek(fd, 0, SEEK_END);
    // Boucle à travers le fichier en partant de la fin
    for (off_t i = size - 1; i >= 0; i--) {
        // Se déplace à la position i à partir du début du fichier
        lseek(fd, i, SEEK_SET);
        // Lit un caractère à la position actuelle
        char c;
        read(fd, &c, 1);
        // Affiche le caractère lu
        printf("%c", c);
    }
    
    // Ferme le fichier
    close(fd);
    return 0;
}

//     Pour tester le programme avec le fichier exemple.txt, vous pouvez exécuter la commande suivante dans un terminal :

//     ./programme exemple.txt