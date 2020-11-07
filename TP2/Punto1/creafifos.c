#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv){
	int fd;
	fd = mkfifo("fifo1",0600);
	if (fd != -1){
		fd = mkfifo("fifo2",0600);
		if ( fd != -1)
			printf("fifo1 y fifo2 creados\n");
		else
			printf("Error creando fifo2\n2");
	}
	else
		prinf("Error creando fifo1\n");
	return 0;
}