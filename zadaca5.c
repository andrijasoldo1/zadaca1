#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_t thread_id[N];
pthread_mutex_t mutex;
pthread_cond_t red[N];

char filozof[N] = { 'O', 'O', 'O', 'O', 'O' };
int vilica[N] = { 1, 1, 1, 1, 1 };

void ispisi_stanje() {
    int i;
    for (i = 0; i < N; i++)
        printf("%c ", filozof[i]);
    printf("\n");
}

void ispisi(int n) {
    printf("Filozof %d: ", n + 1);
}

void jesti(int n) {
    pthread_mutex_lock(&mutex);
    filozof[n] = 'o';
    ispisi(n);
    printf("ceka\n");
    while (vilica[n] == 0 || vilica[(n + 1) % N] == 0)
pthread_cond_wait(&red[n], &mutex);
vilica[n] = vilica[(n + 1) % N] = 0;
filozof[n] = 'X';
ispisi_stanje();
ispisi(n);
printf("jede\n");
sleep(3);
vilica[n] = vilica[(n + 1) % N] = 1;
filozof[n] = 'O';
ispisi_stanje();
ispisi(n);
printf("misli\n");
pthread_cond_signal(&red[(n + 1) % N]);
pthread_cond_signal(&red[(n + N - 1) % N]);
pthread_mutex_unlock(&mutex);
}

void *filozof_dretva(void *filozof_id) {
int n = *((int *) filozof_id);
while (1) {
jesti(n);

ispisi_stanje();
}
}

void inicijaliziraj() {
int i;
pthread_mutex_init(&mutex, NULL);
for (i = 0; i < N; i++)
pthread_cond_init(&red[i], NULL);
}

int main() {
int i, filozof_id[N];
inicijaliziraj();
for (i = 0; i < N; i++) {
    filozof_id[i] = i;
    pthread_create(&thread_id[i], NULL, filozof_dretva, &filozof_id[i]);
}

for (i = 0; i < N; i++)
    pthread_join(thread_id[i], NULL);

return 0;
}


void udji_u_kriticni_odsjecak(int i) {
pthread_mutex_lock(&mutex);
while (vilica[i] == 0 || vilica[(i + 1) % N] == 0)
pthread_cond_wait(&red[i], &mutex);
vilica[i] = vilica[(i + 1) % N] = 0;
}

void izadji_iz_kriticnog_odsjecka(int i) {
vilica[i] = vilica[(i + 1) % N] = 1;
pthread_cond_signal(&red[(i + 1) % N]);
pthread_cond_signal(&red[(i + N - 1) % N]);
pthread_mutex_unlock(&mutex);
}




