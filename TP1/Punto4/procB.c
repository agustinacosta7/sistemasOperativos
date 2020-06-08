#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

int main(void)
{
	sem_t * semA;
	sem_t * semB;
	sem_t * semC;
	sem_t * semX;
	
	semA = sem_open("/semA",0);
	semB = sem_open("/semB",0);
	semC = sem_open("/semC",0);
	semX = sem_open("/semX",0);
	
	while(1)
	{
		sem_wait(semB);
		sem_wait(semX);
			printf("Seccion critica Proceso B\n");
		sem_post(semC);
		sem_post(semA);
	}
}