#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

int main(void)
{
	sem_t * semA;
	sem_t * semX;
	
	int contador = 0;
	
	semA = sem_open("/semA",0);
	semX = sem_open("/semX",0);
	
	while(1)
	{
		sem_wait(semA);
			printf("Seccion critica Proceso B\n");
			contador ++;
		sem_post(semX);
		
		if (contador == 40)
			exit(0);
	}
	
	return 0;
}