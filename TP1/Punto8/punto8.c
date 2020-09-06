#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

void handlerABC(int);
void terminar(int);

int control=1;
int turno = 0;

int main(int argc, char const *argv[])
{
	printf("pid: %d\n", getpid());
	signal(SIGUSR2, terminar);
	while(control) {
		signal(SIGUSR1, handlerABC);
		pause();
	}

	return 0;
}

void handlerABC(int s) {
	char letra;
	if( (turno % 2) == 0) {
		letra = 'a';
		while(letra <= 'z') {
			printf("letra %c\n", letra);
			letra++;
		}
	} else {
		letra = 'A';
		while(letra <= 'Z') {
			printf("letra %c\n", letra);
			letra++;
		}
	}
	turno++;
}

void terminar(int s) {
	printf("recibi senal %d\n", s);
	control = 0;
}