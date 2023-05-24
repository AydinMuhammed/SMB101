#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#define SIZE (int)1e8
#define NUM_THREADS 2// essayer aevc 2, 4, 8

// Question :
// Que constatez-voud ?
// Je constate que avec 2 Thread ( c'est plus rapide ) :
        //Le tableau a été initialisé en 1.034055 secondes.
        //La recherche du min et du max avec 2 threads a pris 0.278547 secondes.
// Avec 4 Thread :
        //Le tableau a été initialisé en 1.072261 secondes.
        //La recherche du min et du max avec 4 threads a pris 0.295331 secondes.
// Avec 8 Thread :
        //Le tableau a été initialisé en 3.774795 secondes.
        //La recherche du min et du max avec 8 threads a pris 0.474818 secondes.


int tab[SIZE];
int min_result, max_result;
pthread_mutex_t mutex;

void initialize_array() {
	for (int i = 0; i < SIZE; i++) {
    	tab[i] = rand();
	}
}

void* find_min_max(void* arg) {
	int thread_id = *(int*)arg;
	int start_index = (SIZE / NUM_THREADS) * thread_id;
	int end_index = (SIZE / NUM_THREADS) * (thread_id + 1);

	int local_min = tab[start_index];
	int local_max = tab[start_index];

	for (int i = start_index + 1; i < end_index; i++) {
    	if (tab[i] < local_min) {
        	local_min = tab[i];
    	}

    	if (tab[i] > local_max) {
        	local_max = tab[i];
    	}
	}

	// Verrouillage du mutex pour protéger l'accès aux variables globales
	pthread_mutex_lock(&mutex);

	if (local_min < min_result) {
    	min_result = local_min;
	}

	if (local_max > max_result) {
    	max_result = local_max;
	}

	// Déverrouillage du mutex
	pthread_mutex_unlock(&mutex);

	pthread_exit(NULL);
}

void print_array() {
	printf("Contenu du tableau :\n");

	for (int i = 0; i < SIZE; i++) {
    	printf("%d ", tab[i]);
	}

	printf("\n");
}

int main() {
	struct timeval start_time, end_time;
	double elapsed_time;
	pthread_t threads[NUM_THREADS];
	int thread_ids[NUM_THREADS];

	// Initialisation du tableau
	gettimeofday(&start_time, NULL);
	initialize_array();
	gettimeofday(&end_time, NULL);
	elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1e6;

	printf("Le tableau a été initialisé en %.6f secondes.\n", elapsed_time);

	// Affichage du contenu du tableau
	//print_array();

	// Initialisation du mutex
	pthread_mutex_init(&mutex, NULL);

	// Recherche du minimum et du maximum avec threads
	gettimeofday(&start_time, NULL);

	min_result = tab[0];
	max_result = tab[0];

	for (int i = 0; i < NUM_THREADS; i++) {
    	thread_ids[i] = i;
    	pthread_create(&threads[i], NULL, find_min_max, &thread_ids[i]);
	}

	for (int i = 0; i < NUM_THREADS; i++) {
    	pthread_join(threads[i], NULL);
	}

	gettimeofday(&end_time, NULL);
	elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1e6;

	printf("Le minimum du tableau est : %d\n", min_result);
	printf("Le maximum du tableau est : %d\n", max_result);
	printf("La recherche du min et du max avec %d threads a pris %.6f secondes.\n", NUM_THREADS, elapsed_time);

	// Destruction du mutex
	pthread_mutex_destroy(&mutex);

	return 0;
}


