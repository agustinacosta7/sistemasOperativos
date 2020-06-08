#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

int main(void)
{
	int contador = 0;
	
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
		sem_wait(semC);
		sem_wait(semX);
			printf("Seccion critica Proceso C\n");
			contador ++;
			
			if (contador<20)
				printf("Finalizo iteracion %d\n",contador);
			else
			{
				printf("Finalizo iteracion %d\n",contador);
				break;
			}
		sem_post(semA);
		sem_post(semB);
	}
}