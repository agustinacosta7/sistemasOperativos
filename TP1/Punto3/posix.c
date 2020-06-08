#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

void *hiloA();
void *hiloB();
void *hiloC();

pthread_t ha, hb, hc;
sem_t sa, sb, sc, sc;
int contador = 0;

int main(void)
{
	sem_init(&sa,0,1);
	sem_init(&sb,0,1);
	sem_init(&sc,0,0);
	sem_init(&sa,0,0);
	
	printf("main(): lanzo hilo A\n");
	pthread_create(&ha, NULL, hiloA, NULL);
	printf("main(): lanzo hilo B\n");
	pthread_create(&ha, NULL, hiloB, NULL);
	printf("main(): lanzo hilo C\n");
	pthread_create(&ha, NULL, hiloC, NULL);
	
	printf("main(): espero finalizacion de los hilos\n");
	pthread_join(ha,NULL);
	pthread_join(hb,NULL);
	pthread_join(hc,NULL);
	
	sem_destroy(&sa);
	sem_destroy(&sb);
	sem_destroy(&sc);
	sem_destroy(&sx);
	
	printf("main(): Fin!\n");
	return 0;
}

void *hiloA()
{
	while(1)
	{
		sem_wait(&sa);
			printf("Seccion critica Proceso A\n");
		sem_post(&sx);
	}
	pthread_exit(0);
}

void *hiloB()
{
	while(1)
	{
		sem_wait(&sb);
		sem_wait(&sx);
			printf("Seccion critica Proceso B\n");
		sem_post(&sa);
		sem_post(&sc);
	}
	pthread_exit(0);
}

void *hiloC()
{
	while(1)
	{
		sem_wait(&sc);
		sem_wait(&sx);
			printf("Seccion critica Proceso C\n");
			contador ++;
			
			if (contador<20)
				printf("Fin iteracion %d\n",contador);
			else
			{
				printf("Fin iteracion %d\n",contador);
				break;
			}
		sem_post(&sa);
		sem_post(&sb);
	}
	printf("Fin 20 iteraciones. Cierre de hilos\n");
	pthread_cancel(ha);
	pthread_cancel(hb);
	pthread_exit(0);
}