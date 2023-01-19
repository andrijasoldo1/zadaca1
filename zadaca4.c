#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5 
int riders = 0; 
sem_t mutex, riders_sem, ride_sem;

void* rider(void* arg) {
    int id = *((int*) arg);
    printf("Posjetitelj %d je stigao na vrtuljak.\n", id);

    while(1) {
        
        sem_wait(&mutex);
        if (riders < N) {
            riders++;
            printf("Posjetitelj %d sjeda na vrtuljak.\n", id);
            sem_post(&mutex);
            sem_post(&riders_sem);
            break;
        }
        sem_post(&mutex);
    }

    sem_wait(&ride_sem);
    printf("Posjetitelj %d silazi s vrtuljak.\n", id);

    sem_wait(&mutex);
    riders--;
    sem_post(&mutex);
    pthread_exit(0);
}

void* ride(void* arg) {
    while(1) {
        sem_wait(&riders_sem);
        if (riders == N) {
            printf("Voznja pocinje!\n");
            for (int i = 0; i < N; i++) {
                sem_post(&ride_sem);
            }
        }
    }
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&riders_sem, 0, 0);
    sem_init(&ride_sem, 0, 0);

    pthread_t riders_t[10], ride_t;
    int id[10];
    for (int i = 0; i < 10; i++) {
        id[i] = i + 1;
        pthread_create(&riders_t[i], NULL, rider, &id[i]);
    }
    pthread_create(&ride_t, NULL, ride, NULL);

    for (int i = 0; i < 10; i++) {
        pthread_join(riders_t[i], NULL);
    }
    pthread_cancel(ride_t);

    sem_destroy(&mutex);
    sem_destroy(&riders_sem);
    sem_destroy(&ride_sem);

    return 0;
}
