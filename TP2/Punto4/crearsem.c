#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv){
	sem_t *semE1;
	sem_t *semE2;
	sem_t *semL1;
	sem_t *semL2;
	
	sem_unlink("/semE1");
	sem_unlink("/semE2");
	sem_unlink("/semL1");
	sem_unlink("/semL2");
	
	semE1 = sem_open("/semE1", O_CREAT|O_EXCL, 0644, 1);
	semE2 = sem_open("/semE2", O_CREAT|O_EXCL, 0644, 1);
	semL1 = sem_open("/semL1", O_CREAT|O_EXCL, 0644, 0);
	semL2 = sem_open("/semL2", O_CREAT|O_EXCL, 0644, 0);
	
	return 0;
}