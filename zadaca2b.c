#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
int *current_ticket, *flag, ticket_id, flag_id;

void enter_critical_section(int i, int j){
	flag[i] = 1;
	while(!(flag[j] == 0)){
		if(*current_ticket  == j){
			flag[i] = 0;
			while(*current_ticket == j){
			}
		flag[i] = 1;
		}
	}
}

void exit_critical_section(int i, int j){

	flag[i] = 0;
	*current_ticket = j;
}

void kontrola(int i, int j){
	int k, m;
	for(k = 1; k<5; k++){
		enter_critical_section(i,j);
		for(m = 1; m<5; m++){
			printf("i: %d, k: %d, m: %d\n", i, k, m);
			sleep(1);
		}
		exit_critical_section(i,j);
	}
}

void cleanup(){
	shmdt(current_ticket);
	shmdt(flag);

	shmctl(ticket_id, IPC_RMID, NULL);
	shmctl(flag_id, IPC_RMID, NULL);

	exit(0);
}

int main(){
        ticket_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0660);
        flag_id = shmget(IPC_PRIVATE, sizeof(int) * 2, IPC_CREAT | 0660);
        current_ticket = (int*)shmat(ticket_id, NULL, 0);
        flag = (int*)shmat(flag_id, NULL, 0);


        if(fork() == 0){
                kontrola(1,0);
        }if(fork() == 0){

		kontrola(0,1);

	};
	signal(SIGINT, cleanup);
	wait(NULL);
        wait;
        }
