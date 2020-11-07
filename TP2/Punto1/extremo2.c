//Extremo2 de la conversacion
//Proceso padre escritor en fifo2
//Proceso hijo lector en fifo1

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char **argv){
	pid_t pid;
	pid = fork();
	if (pid >0){ //padre escritor
		int status;
		int fd = open("fifo2",O_WRONLY);
		char entrada[512];
		do{
			printf("mensaje a enviar en fifo2:");
			memset(entrada,'\0',512);
			gets(entrada);
			write(fd,entrada,512);
		} while (strcmp(entrada,"chau"));
		close(fd);
		wait(&status);
	}
	else { //hijo lector
		int fd = open("fifo1",O_RDONLY);
		printf("hijo lector is alive!\n");
		char entrada[512];
		do{
			sleep(10);
			memset(entrada,'\0',512);
			read(fd,entrada,512);
			printf("-----------mensaje leido de fifo1: %s\n",entrada);
		} while (strcmp(entrada,"chau"));
		close(fd);
	}
	exit(0):
}