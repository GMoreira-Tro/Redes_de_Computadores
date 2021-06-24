#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define ECHOMAX 81

int main(int argc, char *argv[]) {

	/* ESTACAO REMOTA */
	char *rem_hostname;
	int rem_port;
	/* Estrutura: familia + endereco IP + porta */
	struct sockaddr_in rem_addr;
	int rem_sockfd;

	char linha[ECHOMAX];

	if (argc != 3) {
		printf("Parametros:<remote_host> <remote_port> \n");
		exit(1);
	}

	/* Construcao da estrutura do endereco local */
	/* Preenchendo a estrutura socket loc_addr (familia, IP, porta) */
	rem_hostname = argv[1];
	rem_port = atoi(argv[2]);
	rem_addr.sin_family = AF_INET; /* familia do protocolo*/
	rem_addr.sin_addr.s_addr = inet_addr(rem_hostname); /* endereco IP local */
	rem_addr.sin_port = htons(rem_port); /* porta local  */

   	/* Cria o socket para enviar e receber datagramas */
	/* parametros(familia, tipo, protocolo) */
	rem_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (rem_sockfd < 0) {
		perror("Criando stream socket");
		exit(1);
	}
	printf("> Conectando no servidor '%s:%d'\n", rem_hostname, rem_port);

   	/* Estabelece uma conexao remota */
	/* parametros(descritor socket, estrutura do endereco remoto, comprimento do endereco) */
	if (connect(rem_sockfd, (struct sockaddr *) &rem_addr, sizeof(rem_addr)) < 0) {
		perror("Conectando stream socket");
		exit(1);
	}
	do  {
        //gets(linha);
        fgets (linha, ECHOMAX, stdin);
        linha[strlen(linha)-1] = '\0';

        /* parametros(descritor socket, endereco da memoria, tamanho da memoria, flag) */
        send(rem_sockfd, &linha, sizeof(linha), 0);

        /* parametros(descritor socket, endereco da memoria, tamanho da memoria, flag) */
        recv(rem_sockfd, &linha, sizeof(linha), 0);
        printf("Recebi %s\n", linha);
	} while(strcmp(linha,"exit"));
	/* fechamento do socket remota */
	close(rem_sockfd);
}
