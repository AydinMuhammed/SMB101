#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
    // Vérifie si le nom de fichier est fourni en argument
    if (argc < 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }
    
// Vérifie si l'extension du fichier est .txt
    char* filename = argv[1];
    size_t filename_len = strlen(filename);
    if (filename_len < 5 || strcmp(&filename[filename_len - 4], ".txt") != 0) {
        printf("Error: invalid file extension. File must be a .txt file.\n");
        return 1;
    }

    // Ouvre le fichier en lecture seule
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        printf("Error: failed to open file %s\n", filename);
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

//     Pour tester le programme avec le fichier exemple.txt (le fichier .txt doit etre dans le dossier exo2), vous pouvez exécuter la commande suivante dans un terminal :

//     ./programme exemple.txt

//     Note: bien se placer dans le dossier exo2 avant d'exécuter la commande ci-dessus.