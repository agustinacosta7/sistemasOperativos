//Proceso que elimina los fifos

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
	int fd;
	fd = unlink("fifo1");
	if (fd != -1){
		fd = unlink("fifo2");
		if (fd != -1){
			printf("fifo1 y fifo2 eliminados\n");
		}
		else{
			printf("Error eliminando fifo2\n");
		}
	}
	else{
		printf("Error eliminando fifo2\n");
	}
	return 0;
}