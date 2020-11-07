//Extremo1 de la conversacion
//Proceso padre escritor en fifo1
//Proceso hijo lector de fifo2

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
	if (pid > 0){ //padre escritor
		int status;
		int fd = open("fifo1",O_WRONLY);
		char entrada[512];
		do{
			memset(entrada,'\0',512);
			printf("mensaje a enviar en fifo1:");
			gets(entrada);
			write(fd,entrada,512);
		} while (strcmp(entrada,"chau"));
		close(fd);
		wait(&status);
	}
	else { //hijo lector
		int fd = open("fifo2",O_RDONLY);
		printf("Hijo lector is alive!\n");
		char entrada[512];
		do{
			memset(entrada,'\0',512);
			read(fd,entrada,512);
			printf("------- mensaje lei de fifo2: %s\n",entrada);
		} while (strcmp(entrada,"chau"));
		close(fd);
	}
	exit(0);
}