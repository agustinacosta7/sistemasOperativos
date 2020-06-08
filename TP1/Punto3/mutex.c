#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h> 
#include <semaphore.h>

void *hiloA(); 
void *hiloB();
void *hiloc();

int contador = 0;

pthread_mutex_t ma = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mb = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mc = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t mx = PTHREAD_MUTEX_INITIALIZER;

pthread_t ha, hb, hc;

int main(void)
{
	pthread_mutex_lock(&mc); 
	pthread_mutex_lock(&mx);
	printf("main(): lanzo hilo A\n"); 
	pthread_create(&ha, NULL,hiloA, NULL); 
	printf("main(): lanzo hilo B\n");
	pthread_create(&hb, NULL, hiloB, NULL); 
	printf(“main(): lanzo hilo C\n");
	pthread_create(&hc, NULL, hiloC, NULL);
	printf("main(): espero por la finalizacion de todos los hilos\n");

	pthread_join(hc,NULL);

	printf(“main(): fin!\n”;
	return 0;
}

void *hiloA()
{
	while(1)
	{
		pthread_mutex_lock(&ma);
		  printf(“Seccion critica Proceso A\n”);
		pthread_mutex_unlock(&mx);
	}
	pthread_exit(0);
}

void *hiloB()
{
	while(1)
	{
		pthread_mutex_lock(&mb);
		pthread_mutex_lock(&mx);
		  printf(“Seccion critica Proceso B\n”);
		pthread_mutex_unlock(&ma);
		pthread_mutex_unlock(&mc);
	}
	pthread_exit(0);
}

void *hiloC()
{
	while(1)
	{
		pthread_mutex_lock(&mc);
		pthread_mutex_lock(&mx);
		   printf(“Seccion critica Proceso C\n”);
		   contador ++;
		
		if (contador<20)
			printf(“Iteraciones finalizadas %d\n”,contador);
		else
		{
			printf(“Iteraciones finalizadas %d\n”,contador);
			break;
		}

		pthread_mutex_unlock(&ma);
		pthread_mutex_unlock(&mb);
	}
	
	printf(“Fin 20 iteraciones. Cierre de hilos\n”);
	pthread_cancel(ha);
	pthread_cancel(hb);
	pthread_exit(0);
}
