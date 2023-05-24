#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define SIZE (int)1e8

int tab[SIZE];

void initialize_array() {
	for (int i = 0; i < SIZE; i++) {
    	tab[i] = rand();
	}
}

void find_min_max(int* min, int* max) {
	*min = tab[0];
	*max = tab[0];

	for (int i = 1; i < SIZE; i++) {
    	if (tab[i] < *min) {
        	*min = tab[i];
    	}

    	if (tab[i] > *max) {
        	*max = tab[i];
    	}
	}
}

//je ne n'affiche pas le tableau car trop long 
//void print_array() {
//	printf("Contenu du tableau :\n");
//
//	for (int i = 0; i < SIZE; i++) {
//  	printf("%d ", tab[i]);
//	}
//
//	printf("\n");
//}

int main() {
	struct timeval start_time, end_time;
	double elapsed_time;

	// Initialisation du tableau
	gettimeofday(&start_time, NULL);
	initialize_array();
	gettimeofday(&end_time, NULL);
	elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1e6;

	printf("Le tableau a été initialisé en %.6f secondes.\n", elapsed_time);

	// Recherche du minimum et du maximum
	gettimeofday(&start_time, NULL);
	int min, max;
	find_min_max(&min, &max);
	gettimeofday(&end_time, NULL);
	elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1e6;

	printf("Le minimum du tableau est : %d\n", min);
	printf("Le maximum du tableau est : %d\n", max);
	printf("La recherche du min et du max a pris %.6f secondes.\n", elapsed_time);

	return 0;
}


