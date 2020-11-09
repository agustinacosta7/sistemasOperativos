#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

//Creo cola de mensajes
int main(void){
	int msgid = msgget(0xa,IPC_CREAT|0777);
	printf("msgid = %d\n",msgid);
	exit(0);
}