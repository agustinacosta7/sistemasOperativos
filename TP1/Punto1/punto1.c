#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

/*
Se puede -----
* Ejecutar comandos con argumentos
* Ejecutar comandos en foreground
* Ejecutar comandos en background
* Cambiar de directorio 
* Redireccionar salida a archivo
*/

#define LARGO_MAX_SWITCH	50 	//Un switch de comando no puede tener mas caracteres que LARGO_MAX_SWITCH
#define LARGO_MAX_CMD		512 //Un comando no puede tener mas caracteres que LARGO_MAX_CMD
#define MAXIMO_SWITCHES_CMD 	100 //Un comando puede tener hasta MAXIMO_SWITCHES_CMD switches
#define SEGUNDOS_CHEQUEO 	25 	//Se chequea y mata zombies cada SEGUNDOS_CHEQUEO segundos

//Signal handlers
void mata_zombies(int);
void fallo_cmd_background(int);

void ingreso_cmd(char *);
void borrar_espacios_final(char *);
void borrar_espacios_inicio(char *);
void borrar_caracteres_control(char *);
void borrar_ampersand(char *);
void parse_comando(char *, int, char *[]);
int comando_background(char *);
int comando_redireccion(char *);

//Ultimo pid creado
pid_t ultimo_pid = 0;

int main(int argc, char **argv) {
	char comando[LARGO_MAX_CMD];
	char *comando_argv[MAXIMO_SWITCHES_CMD];
	int retorno;

	signal(SIGALRM, mata_zombies);
	signal(SIGUSR1, fallo_cmd_background);
	alarm(SEGUNDOS_CHEQUEO);

	ingreso_cmd(comando);
	
	while(strncmp(comando,"fin",3))
	{
		pid_t pid = fork();
		if ( pid == 0 ) {  // proceso hijo
			signal(SIGALRM,SIG_DFL);
			signal(SIGUSR1,SIG_DFL);
			int back = comando_background(comando);
			if ( comando_background(comando) ) borrar_ampersand(comando);
	
			parseo_cmd(comando,MAXIMO_SWITCHES_CMD,comando_argv);
			/* chequeo parsing de comando
			int i=0;
			while(comando_argv[i]) {
				printf("switch [%d]=[%s]\n",i,comando_argv[i]);
				i++;
			} */
			execvp(comando_argv[0],comando_argv);
			printf("Comando [%s] de proceso %d Erroneo!\n",comando,getpid());
			if ( back ) kill(getppid(),SIGUSR1);  // envio se#al al padre para notificar fallo en hijo
			exit(127); // llamada al sistema para terminar proceso con determinado valor de retorno
		} else {  // proceso padre
			ultimo_pid = pid;
			if ( !comando_background(comando) ) {
				pid = waitpid(pid,&retorno,0);
				if (WEXITSTATUS(retorno) != 127)
					printf("Proceso %d finalizo con status = %d\n",pid,WEXITSTATUS(retorno));
			}
		}
		ingreso_cmd(comando);
	} 
	//Antes de finalizar, elimino todo posible proceso zombie
	//Pueden quedar procesos huerfanos en ejecucion background
	mata_zombies(0);
	
	return 0;
}

//FUNCIONES -----------------------

void ingreso_cmd(char *cmd) {
	printf("Ingrese Comando sin argumentos (fin,ls,ps,cal,./fore25,./back50&,./fore25&):\n");
	memset(cmd, 0, LARGO_MAX_CMD);
	printf("%%");
	//en cmd me quedan los caracteres tipeados + \n + \0
	fgets(cmd, LARGO_MAX_CMD, stdin);

	//Con esta funcion reemplazo el \n al final del comando por \0
	borrar_caracteres_control(cmd);
	borrar_espacios_final(cmd);
	borrar_espacios_inicio(cmd);
}

/*
 * Verifica si el comando termina con &
 * devuelve verdadero o falso
 */
int comando_background(char *cmd) {
	int n = strlen(cmd)-1;
	return( n >= 0 && cmd[n] == '&');
}

/* Borra espacios al final del cmd*/
void borrar_espacios_final(char *cmd) {
	int n = strlen(cmd) - 1;
	while( n >= 0 && cmd[n] == ' ') {
		cmd[n] = '\0';
		n--;
	}
}

//Borra los espacios al inicio
void borrar_espacios_inicio(char *cmd) {
	char *p = cmd;
	while( *p && *p == ' ') p++;
	if (p == cmd) return; //no tenia espacios al inicio
	char tmp[LARGO_MAX_CMD];
	strcpy(tmp,p);
	strcpy(cmd,tmp);
}

/*
 * Quita caracteres de control (return,tab,intro,etc)
 */
void borrar_caracteres_control(char *cmd) {
	char *p = cmd;
	while(*p) {
		switch(*p) {
			case '\n':
			case '\r':
			case '\t':
			case '\b':
				*p = ' ';
				break;
		}
		p++;
	}
}

// Quita caracter & al final del comando
void borrar_ampersand(char *cmd) {
	cmd[strlen(cmd)-1]= '\0'; // borro &
	borrar_espacios_final(cmd);
}

void parse_comando(char *cmd, int argc, char *argv[]) {
	int i = 0;
	int pos1 = 0;
	int pos2 = 0; // posicion desde - hasta de caracteres a tomar como switch
	int nc = 0;
	int tope = strlen(cmd); // limite del string cmd
	do {
		pos1= i;
		while(i < tope && cmd[i] != ' ') i++;
		pos2= i;
		if ( pos1 == pos2 ) break;
		if ( (pos2 - pos1) > LARGO_MAX_SWITCH) {
			printf("parseo_cmd(): argumento %d de comando [%s] supera los %d caracteres\n",nc,cmd,LARGO_MAX_SWITCH);
			break;	
		}
		argv[nc] = strndup(cmd+pos1,pos2-pos1);
		//avanzo hasta el proximo switch
		while( i < tope && cmd[i] == ' ') i++;
		nc++;
	} while( nc < argc && i < tope);
	argv[nc] = NULL;
}


void mata_zombies(int signo) {
	int retorno = 0;
	pid_t pid = 0;
	while((pid = waitpid(0, &retorno, WNOHANG)) > 0) {
		//Mata un zombie
	}
	alarm(SEGUNDOS_CHEQUEO);
}
/*
 * Recibe esta se#al cada vez que falla un comando background
 * es decir, cada vez que falla exec()
 */
 
void fallo_cmd_background(int signo) {
	int retorno;
	waitpid(ultimo_pid, &retorno, 0);
}

//EXTRA ----------------



int comando_redireccion(char *cmd) 
{

	for (int i=0; i< strlen(cmd); i++)
		{
		if (cmd[i] == '>') 
			{
			return 1;
			}
		}
	return 0;
}
