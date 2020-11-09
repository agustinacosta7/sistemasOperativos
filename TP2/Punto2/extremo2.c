#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

//Estructura de mensaje
struct mensaje {
	long tipo;
	char texto[512];
};

int main(){
	pid_t pid;
	int msgid = mssget(0xa,0);
	pid = fork();
	if (pid > 0){ //padre escritor 2
		struct mensaje msg;
		msg.tipo = 2;
		do {
			printf("mensaje a enviar en <%ld>",msg.tipo);
			fgets(msg.texto,512,stdin);
			msgsnd(msgid,&msg,512,0);
		} while (strncmp(msg.texto,"chau",4) != 0);
	}
	else { // hijo lector 1
		struct mensaje msg;
		msg.tipo = 1;
		do {
			memset(&msg,0,sizeof(struct mensaje));
			msgrcv(msgid,&msg,512,1,0);
			printf("mensaje leido de tipo <%ld> : %s\n",msg.tipo,msg.texto);
		} while (strncmp(msg.texto,"chau",4) != 0);
	}
	exit(0)
}
