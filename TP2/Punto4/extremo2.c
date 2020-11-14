#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

//El proceso padre escribira en Archivo2.txt
//El proceso hijo leera de Archivo1.txt lo que escriba el otro proceso padre

int main(int argc, char **argv[]){
	sem_t *semE1;
	sem_t *semE2;
	sem_t *semL1;
	sem_t *semL2;
	
	semE1 = sem_open("/semE1",0);
	semE2 = sem_open("/semE2",0);
	semL1 = sem_open("/semL1",0);
	semL2 = sem_open("/semL2",0);
	
	char mensaje[256];
	char caracter;
	
	pid_t pid;
	
	pid = fork();
	
	if (pid > 0){
		while(1){
			sem_wait(semE2);
				printf("Escribir en Archivo2 >\n");
				FILE *archivo = fopen("archivo2.txt","w");
				fgets(mensaje,256,stdin);
				fprintf(archivo,"%s\n",mensaje);
				fclose(archivo);
			sem_post(semL1);
		}
		wait(0);
	}
	
	else{
		while(1){
			sem_wait(semL2);
				memset(mensaje,0,256);
				FILE *archivo = fopen("archivo1.txt","r");
				int i=0;
				while (feof(archivo)==0){
					caracter = fgetc(archivo);
					mensaje[i]=caracter;
					i++;
					if (caraceter == '\n') break;
					printf("%c",caracter);
				}
				printf("< Leido de archivo1\n");
				fclose(archivo);
			sem_post(semE1);
		}
	}
	return 0;
}