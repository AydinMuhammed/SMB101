#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void printFileInfo(const char *filePath, const struct stat *fileStat) {
    struct passwd *pw = getpwuid(fileStat->st_uid);
    struct group *gr = getgrgid(fileStat->st_gid);
    struct tm *timeinfo;
    char date_modified[20];

    timeinfo = localtime(&(fileStat->st_mtime));
    strftime(date_modified, sizeof(date_modified), "%Y-%m-%d %H:%M:%S", timeinfo);

    printf("Nom : %s\n", filePath);
    printf("Permissions : %o\n", fileStat->st_mode & 0777);
    printf("Propriétaire : %s\n", pw->pw_name);
    printf("Groupe : %s\n", gr->gr_name);
    printf("Taille : %lld octets\n", (long long)fileStat->st_size);
    printf("Date de dernière modification : %s\n", date_modified);
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <dossier>\n", argv[0]);
        return 1;
    }

    DIR *directory;
    struct dirent *entry;
    struct stat fileStat;
    char filePath[256];

    // Ouvre le répertoire spécifié en argument
    directory = opendir(argv[1]);

    if (directory) {
        // Lit chaque entrée du répertoire
        while ((entry = readdir(directory)) != NULL) {
            snprintf(filePath, sizeof(filePath), "%s/%s", argv[1], entry->d_name);

            // Obtient les métadonnées du fichier
            if (stat(filePath, &fileStat) == 0) {
                // Vérifie si l'entrée est un fichier régulier
                if (S_ISREG(fileStat.st_mode)) {
                    printFileInfo(entry->d_name, &fileStat);
                }
            }
        }

        // Ferme le répertoire
        closedir(directory);
    }

    return 0;
}