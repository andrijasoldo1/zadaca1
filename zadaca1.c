#include <math.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int should_exit = 0;
int current_status;

void sigint_handler(int sig) {
    printf("\nIzaberite opciju:\n1) Izlaz iz programa bez zavrsetka trenutne radnje\n2) Izadite iz programa i pohranite trenutni status\n3) Ispisite trenutni status\n4) Nastavite\n");
    int input;
    scanf("%d", &input);
    switch(input){
    case 1:
        printf("\nNapustanje programa\n");
        exit(0);
        break;
    case 2:
        printf("\nSIGTERM primljen, napustanje programa...\n");
        FILE* status_file = fopen("status.txt", "w");
        fprintf(status_file, "%d", current_status);
        fclose(status_file);
        exit(0);
        break;
    case 3:
        printf("\nTrenutni status: %d\n", current_status);
        break;
    default:
        break;
    }
}

void sigterm_handler(int sig) {
    printf("\nSIGTERM primljen, napustanje programa... ...\n");
    should_exit = 1;
}

void process_data(FILE *status_file, FILE *obrada_file) {
    if(current_status == 0) {
        int obrada_num;
        while(!feof(obrada_file)) {
            fscanf(obrada_file, "%d", &obrada_num);
        }
        current_status = round(sqrt(obrada_num));
    }

    fseek(status_file, 0, SEEK_SET);
    fprintf(status_file, "%d", 0);
    fflush(status_file);
    fflush(obrada_file);
    sleep(3);
    fseek(status_file, 0, SEEK_SET);
    fseek(obrada_file, 0, SEEK_END);
    current_status++;
    fprintf(status_file, "%d", current_status);
    fprintf(obrada_file, "%d\n", current_status*current_status);
    fflush(status_file);
    fflush(obrada_file);
    sleep(2);
}

int main() {
    FILE* status_file = fopen("status.txt", "r");
    FILE* obrada_file = fopen("obrada.txt", "r+");

    fscanf(status_file, "%d", &current_status);
    signal(SIGTERM, sigterm_handler);
    signal(SIGINT, sigint_handler);

    while(should_exit == 0) {
        status_file = freopen("status.txt", "w+", status_file);
        process_data(status_file, obrada_file);
        }
        }
