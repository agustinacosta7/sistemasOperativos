#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void)
{
	sem_t * semA;
	sem_t * semB;
	sem_t * semC;
	sem_t * semX;
	
	int valSemA, valSemB, valSemC, valSemX;
	
	semA = sem_open("/semA",0);
	semB = sem_open("/semB",0);
	semC = sem_open("/semC",0);
	semX = sem_open("/semX",0);
	
	pid_t pid;
	int contador = 0;
	
	pid = fork();
	
	if (pid == 0) //hijo B
	{
		while(1)
		{
			sem_wait(semB);
			sem_wait(semX);
				printf("Seccion critica Hijo B\n");
			sem_post(semC);
			sem_post(semA);
		}
	}
	else
	{
		pid = fork();
		if (pid == 0) // hijo C
		{
			while(1)
			{
				sem_wait(semC);
				sem_wait(semX);
					printf("Seccion critica Hijo C\n");
					contador ++;
					
				if (contador<20)
					printf("Final iteracion %d\n",contador);
				else
				{
					printf("Final iteracion %d\n",contador);
					exit(-1);
				}
				
				sem_post(semA);
				sem_post(semB);
			}
		}
		
		else //padre A
		{
			while(1)
			{
				sem_wait(semA);
					printf("Seccion critica Padre A\n");
				sem_post(semX);
			}
		}
	}
	return 0;
}