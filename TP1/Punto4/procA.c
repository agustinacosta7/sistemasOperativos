#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

int main(void)
{
	sem_t * semA;
	sem_t * semB;
	
	semA = sem_open("/semA",0);
	semB = sem_open("/semB",0);
	
	while(1)
	{
		sem_wait(semA);
			printf("Seccion critica Proceso A\n");
		sem_post(semX);
	}
}