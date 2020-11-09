#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

//Elimino cola de mensajes
int main(void){
	int msgid = msgget(0xa,0);
	printf("destruyo cola msgid = %d\n",msgid);
	msgctl(msgid,IPC_RMID,0);
	exit(0);
}