#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Utilisation : ./mem_conso <nombre de méga-octets>\n");
        return 1;
    }

    int mb = atoi(argv[1]);
    if (mb <= 0) {
        printf("Le nombre de méga-octets doit être supérieur à zéro.\n");
        return 1;
    }

    int total_bytes = mb * 1024 * 1024;
    int chunk_size = 1024 * 1024;
    int num_chunks = total_bytes / chunk_size;

    void **ptr_array = malloc(num_chunks * sizeof(void *));
    if (ptr_array == NULL) {
        printf("Échec de l'allocation du tableau de pointeurs.\n");
        return 1;
    }

    for (int i = 0; i < num_chunks; i++) {
        void *ptr = malloc(chunk_size);
        if (ptr == NULL) {
            printf("Échec de l'allocation mémoire.\n");
            break;
        }
        ptr_array[i] = ptr;
        printf("Allocation de %d Mo - Adresse : %p\n", mb, ptr);
    }

    // Libération de la mémoire allouée
    for (int i = num_chunks - 1; i >= 0; i--) {
        free(ptr_array[i]);
    }
    free(ptr_array);

    return 0;
}