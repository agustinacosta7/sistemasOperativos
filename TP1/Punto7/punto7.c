#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


#define CANT_SUC 5

double venta[CANT_SUC][31];
double total = 0.0;
double totalSuc[CANT_SUC];

pthread_mutex_t cargaMutex[CANT_SUC];
pthread_cond_t cargaCV[CANT_SUC];

void *cargarVentas(void*);
void *sumarVentas(void*);

int cargadas[CANT_SUC];

int main(void) {
	long s;
	pthread_t carga,suma;

	memset(&cargadas,0,sizeof(int)*CANT_SUC);
	memset(&venta,0,sizeof(double)*CANT_SUC*31);
	memset(&totalSuc,0,sizeof(double)*CANT_SUC);

	printf("main(): creo thread para carga de ventas\n");
	pthread_create(&carga, NULL, cargarVentas, NULL);

	for(s=0; s< CANT_SUC; s++) {
		printf("main(): creando thread de sucursal %d\n", s);
		pthread_create(&suma,NULL,sumarVentas,(void*)s);

	}
	printf("main(): espero por fin de cargarVentas\n");
	pthread_join(carga, NULL);
	printf("main(): espero por fin de sumarVentas\n");
	pthread_join(suma,NULL);
	printf("main(): fin main\n");

	int t;
	for(t=0; t < CANT_SUC; t++) 
		total += totalSuc[t];
	printf("main(): total general = $ %12.2f\n", total);
}

void *cargarVentas(void *p) {
	int s,d;
	printf("thread cargarVentas\n");
	
	for(s=0; s < CANT_SUC; s++) {

		for(d=0; d < 31; d++) {
			venta[s][d] = ( (double) random() ) / 10000000.0;
		}
	
		cargadas[s] = 1;

		pthread_cond_signal(&cargaCV[s]);
		printf("Espero por carga de sucursal %d\n", s);
		sleep(1);
	}
	printf("fin thread cargarVentas\n");
}

void *sumarVentas(void *sucursalId) {
	int sucId;
	sucId = (long) sucursalId;

	pthread_mutex_lock(&cargaMutex[sucId]);

	if(!cargadas[sucId]) {
		printf("thread %d esperando condicion de carga para sucursal %d\n",sucId,sucId);
		pthread_cond_wait(&cargaCV[sucId], &cargaMutex[sucId]);
	}

	printf("thread %d sumo ventas sucursal %d\n", sucId, sucId);
	totalSuc[sucId] = 0.0;
	int d;
	for(d=0; d < 31; d++) {
		totalSuc[sucId] += venta[sucId][d];
	}
	
	pthread_mutex_unlock(&cargaMutex[sucId]);
	printf("fin thread %d sumatoria de sucursal %d = $ %10.2f\n", sucId, sucId, totalSuc[sucId]);
}