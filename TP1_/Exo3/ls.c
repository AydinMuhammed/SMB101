#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

// fonction qui retourne une chaîne de caractères représentant les symboles de permission correspondants
const char *getPermissionsString(mode_t mode) {
    static char permissions[10];
    permissions[0] = (S_ISDIR(mode)) ? 'd' : '-';
    permissions[1] = (mode & S_IRUSR) ? 'r' : '-';
    permissions[2] = (mode & S_IWUSR) ? 'w' : '-';
    permissions[3] = (mode & S_IXUSR) ? 'x' : '-';
    permissions[4] = (mode & S_IRGRP) ? 'r' : '-';
    permissions[5] = (mode & S_IWGRP) ? 'w' : '-';
    permissions[6] = (mode & S_IXGRP) ? 'x' : '-';
    permissions[7] = (mode & S_IROTH) ? 'r' : '-';
    permissions[8] = (mode & S_IWOTH) ? 'w' : '-';
    permissions[9] = (mode & S_IXOTH) ? 'x' : '-';
    permissions[10] = '\0';

    return permissions;
}

void printFileInfo(const char *filePath, const struct stat *fileStat) {
    struct passwd *pw = getpwuid(fileStat->st_uid);
    struct group *gr = getgrgid(fileStat->st_gid);
    struct tm *timeinfo;
    char date_modified[20];

    timeinfo = localtime(&(fileStat->st_mtime));
    strftime(date_modified, sizeof(date_modified), "%Y-%m-%d %H:%M:%S", timeinfo);

    printf("Nom : %s\n", filePath);
    const char *permissions = getPermissionsString(fileStat->st_mode);//appel de la fonction getPermissionsString
    printf("Permissions : %s\n", permissions);
    // Vérifie si l'entrée est un dossier et affiche le type
    if (S_ISDIR(fileStat->st_mode)) {
        printf("Type : Dossier\n");
    // Vérifie si l'entrée est un fichier et affiche le type
    } else if (S_ISREG(fileStat->st_mode)) {
        printf("Type : Fichier\n");
      }
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

    if (directory == NULL) {
        printf("Erreur lors de l'ouverture du répertoire, assurez vous que le dossier existe\n"); //Gerer erreur
        return 1;
    }

    // Lit chaque entrée du répertoire
    while ((entry = readdir(directory)) != NULL) {
        snprintf(filePath, sizeof(filePath), "%s/%s", argv[1], entry->d_name);

        // Obtient les métadonnées du fichier
        if (stat(filePath, &fileStat) != 0) {
            printf("Erreur lors de l'accès au fichier : %s\n", filePath); //Gerer erreur
            continue;
        }

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        printFileInfo(entry->d_name, &fileStat);
    }

    // Ferme le répertoire
    closedir(directory);
    

    return 0;
}
// on affiche les fichiers et sous-dossiers présents dans le dossier précisé en entrée (ce dossier en question doit se situer dans le dossier Exo3)

// pour tester, on peut executer les commandes suivantes : "./ls chemin2" ainsi que "./ls/chemin2"

// Note : bien se placer dans le dossier Exo3 avant de lancer les commandes ci-dessus