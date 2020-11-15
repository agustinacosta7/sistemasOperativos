#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]){
	
	sem_t *semE1;
	sem_t *semE2;
	sem_t *semL1;
	sem_t *semL2;
	
	semE1 = sem_open("/semE1",0);
	semE2 = sem_open("/semE2",0);
	semL1 = sem_open("/semL1",0);
	semL2 = sem_open("/semL2",0);
	
	int shmid = shmget(0xa,0,0);
	printf("memoria = %d\n",shmid);
	
	char *msg = (char *)shmat(shmid,0,0);
	
	memset(msg,0,256);
	char mensaje[256];
	
	pid_t pid;
	pid = fork();
	
	if (pid>0){ //padre escritor en primeros 256 bytes
		do{
			sem_wait(semE1);
			printf("Escribir en extremo 1>>");
			scanf("%s",mensaje);
			memcpy(msg,mensaje,sizeof(mensaje));
			printf("\n");
			sem_post(semL2);
		} while(strcmp(mensaje,"chau",4) != 0);
	}	
	else { // hijo lector de los ultimos 256 bytes
		while(1){
			sem_wait(semL1);
			memcpy(mensaje,msg+256,256);
			printf("    %s << Leido de extremo 2\n",mensaje);
			memset(msg+256,0,256);
			sem_post(semE2);
		}
	}
	return 0;
}	