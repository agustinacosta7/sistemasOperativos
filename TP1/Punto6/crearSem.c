#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	sem_t * semA;
	sem_t * semB;
	sem_t * semC;
	sem_t * semX;
	
	int valSemA, valSemB, valSemC, valSemX;
	
	sem_unlink("/semA");
	sem_unlink("/semB");
	sem_unlink("/semC");
	sem_unlink("/semX");
	
	semA = sem_open("/semA",O_CREAT|O_EXCL,0644,0);
	semB = sem_open("/semB",O_CREAT|O_EXCL,0644,1);
	semC = sem_open("/semC",O_CREAT|O_EXCL,0644,0);
	semX = sem_open("/semX",O_CREAT|O_EXCL,0644,1);
	
	sem_getvalue(semA,&valSemA);
	sem_getvalue(semB,&valSemB);
	sem_getvalue(semC,&valSemC);
	sem_getvalue(semX,&valSemX);
	
	printf("/semA: %d\n",valSemA);
	printf("/semB: %d\n",valSemB);
	printf("/semC: %d\n",valSemC);
	printf("/semX: %d\n",valSemX);
}