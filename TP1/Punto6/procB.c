#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

int main(void)
{
	sem_t * semA;
	sem_t * semB;
	sem_t * semC;
	sem_t * semX;
	
	int contador = 0;
	
	semA = sem_open("/semA",0);
	semB = sem_open("/semB",0);
	semC = sem_open("/semC",0);
	semX = sem_open("/semX",0);
	
	while(1)
	{
		sem_wait(semB);
		sem_wait(semX);
			printf("Iteracion %d\n",contador);
			printf("Seccion critica Proceso B\n");
			contador ++;
		sem_post(semA);
		sem_post(semC);
		
		if (contador == 21)
			exit(0);
	}
	
	return 0;
}