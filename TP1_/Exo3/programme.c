#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    // Vérification du nombre d'arguments
    if (argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    DIR *dirp = opendir(argv[1]);
    if (dirp == NULL) {
        perror("opendir");
        return errno;
    }

    struct dirent *dir;
    while ((dir = readdir(dirp)) != NULL) {
        // Ignorer les fichiers "." et ".."
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
            continue;
        }

        char path[1024];
        sprintf(path, "%s/%s", argv[1], dir->d_name);

        struct stat fileStat;
        if (stat(path, &fileStat) < 0) {
            perror("stat");
            continue;
        }

        struct passwd *pw = getpwuid(fileStat.st_uid);
        if(pw == NULL){
            perror("getpwuid");
            continue;
        }
        struct group *gr = getgrgid(fileStat.st_gid);
        if(gr == NULL){
            perror("getgrgid");
            continue;
        }

        char permission[11];
        permission[0] = (S_ISDIR(fileStat.st_mode)) ? 'd' : '-';
        permission[1] = (fileStat.st_mode & S_IRUSR) ? 'r' : '-';
        permission[2] = (fileStat.st_mode & S_IWUSR) ? 'w' : '-';
        permission[3] = (fileStat.st_mode & S_IXUSR) ? 'x' : '-';
        permission[4] = (fileStat.st_mode & S_IRGRP) ? 'r' : '-';
        permission[5] = (fileStat.st_mode & S_IWGRP) ? 'w' : '-';
        permission[6] = (fileStat.st_mode & S_IXGRP) ? 'x' : '-';
        permission[7] = (fileStat.st_mode & S_IROTH) ? 'r' : '-';
        permission[8] = (fileStat.st_mode & S_IWOTH) ? 'w' : '-';
        permission[9] = (fileStat.st_mode & S_IXOTH) ? 'x' : '-';
        permission[10] = '\0';

        char date[30];
        strftime(date, 30, "%d%m%y @ %Hh%M", localtime(&fileStat.st_mtime));

        printf("%-20s - %-10s %-10s %8ld %s %s\n", dir->d_name, permission, pw->pw_name, gr->gr_name, fileStat.st_size, date);
    }

    closedir(dirp);
    return 0;
}

//      Pour tester on peut exécuter la commande suivate:
        //     ./programme /chemin