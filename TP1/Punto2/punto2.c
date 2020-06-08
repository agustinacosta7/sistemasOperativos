#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>

//Un proceso padre crea n hijos, n será ingresado por consola 
//Cada hijo devolverá un valor distinto, el cual esta dado 
//por el numero de hijo que es.
//El primer hijo retornará 1, el segundo 2 y así sucesivamente

int main(int argc, char const *argv[])
{
	int num = atoi (argv[1]);
	pid_t pid, hijoter;
	int i, status;
	printf("Proceso padre %d\n”, getpid()); 

	for (i=0; i<num; i++)
	{
	if (fork() == 0)
		{
			printf("Hijo %d, padre es %d\n”, getpid(), getppid());
			exit(i+1);
		}
	else
		{
			hijoter = wait(&status); 
			printf("Proceso %d, mi hijo me devolvio %d\n", getpid(), status/256);
		}
	}
	return 0;
}
