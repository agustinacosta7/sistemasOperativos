#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>


int main(int argc, char **argv){
	int pipe1[2];
	int pipe2[2];
	pipe(pipe1);
	pipe(pipe2);

	if(fork()) { 
		//PADRE
		if(fork()) { 
			//PADRE
			close(pipe1[0]);
			close(pipe1[1]);
			close(pipe2[0]);
			close(pipe2[1]);
			printf("P pid: %d\n", getpid());
			while(wait(NULL) != -1);
			printf("P: fin!\n");
		} else {
			//HIJO 2
			if(fork()) {
				printf("\t\t\t\tH2 pid: %d\n", getpid());
				close(pipe1[0]);
				close(pipe2[0]);
				close(pipe2[1]);
				char linea[255];
				while(strncmp(linea,"chau",4) != 0) {
					printf("Ingrese mensaje\n");
					gets(linea);
					printf("\t\t\t\tH2 [%d] envio [%s]\n", getpid(), linea);
					write(pipe1[1],linea,strlen(linea));
					sleep(1);
				}
				close(pipe1[1]);
				printf("\t\t\t\tH2 fin!\n");
			} else {
				//NIETO 2
				printf("\t\t\t\tN2 pid: %d\n", getpid());
				close(pipe1[0]);
				close(pipe1[1]);
				close(pipe2[1]);
				char linea[255];
				int n;
				while(strncmp(linea,"chau",4) != 0) {
					n = read(pipe2[0],linea,255);
					linea[n]='\0';
					printf("\t\t\t\tN2 [%d] leyo [%s]\n", getpid(), linea);
				}
				close(pipe2[0]);
				printf("N2 fin!\n");
			}
		}
	} else {
		//HIJO 1
		if(fork()) {
			//HIJO 1
			printf("H1 pid: %d\n", getpid());
			close(pipe1[0]);
			close(pipe1[1]);
			close(pipe2[0]);
			char linea[255];
			while(strncmp(linea,"chau",4) != 0) {
				printf("\t\t\t\tingrese mensaje\n");
				gets(linea);
				printf("H1 [%d] envio [%s]\n", getpid(), linea);
				write(pipe2[1],linea,strlen(linea));
				sleep(1);
			}
			close(pipe2[1]);
			printf("H1 fin!\n");
		} else {
			//NIETO 1
			printf("N1 pid: %d\n", getpid());
			close(pipe1[1]);
			close(pipe2[0]);
			close(pipe2[1]);
			char linea[255];
			int n;
			while(strncmp(linea,"chau",4) != 0) {
				n = read(pipe1[0],linea,255);
				linea[n]='\0';
				printf("N1 [%d] leyo [%s]\n", getpid(),linea);
			}
			close(pipe1[0]);
			printf("N1 fin!\n");
		}
	}

	return 0;
}