#include <iostream>
#include <fstream>
#include <unistd.h>
#include <signal.h>
int broj;
const char* output_file ="obrada.txt";
const char* status_file ="status.txt";
void sigint_handler(int signum){
std::ofstream f(output_file,std::ios::app);
};
if(f.is_open()){
f << x << std::endl; 
}
sleep(5);

void sigusr1_handler(int signum);
std::cout <<"Trenuta vrijendost"<<broj<<std::endl;

void sigterm_handler(int signum);

std::ofstream f(status_file);

if(f.is_open()){
f << broj;
}
int compute(int x)
return x*x;

int x = compute(broj);

int main(){

sigset_t signals;
sigemptyset(&signals);
sigaddset(&signals,SIGUSR1);
sigaddset(&signals,SIGTERM);
sigaddset(&signals,SIGINT);

sigprocmask(SIG_BLOCK,&signals,nullptr);

return 0;


std::ifstream status(status_file);
if (status.is_open()){	
	status >> broj;
	}

if (broj == 0){
std::ofstream f(output_file);
if (f.is_open()){
while(f >> broj) {}
}
}
std::ofstream f(status_file);
if (f.is_open()){
f << "0";
}
while (true){
broj++;
}
}
