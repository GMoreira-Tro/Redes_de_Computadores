#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	/* Variaveis Locais */
	int loc_sockfd, loc_newsockfd, tamanho;
	char linha[81];
	/* Estrutura: familia + endereco IP + porta */
	struct sockaddr_in loc_addr;

	if (argc != 2) {
		printf("Parametros: <local_port> \n");
		exit(1);
	}

   	/* Cria o socket para enviar e receber datagramas */
	/* parametros(familia, tipo, protocolo) */
	loc_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (loc_sockfd < 0) {
		perror("Criando stream socket");
		exit(1);
	}

	/* Construcao da estrutura do endereco local */
	/* Preenchendo a estrutura socket loc_addr (familia, IP, porta) */
	loc_addr.sin_family = AF_INET; /* familia do protocolo*/
	loc_addr.sin_addr.s_addr = INADDR_ANY; /* endereco IP local */
	loc_addr.sin_port = htons(atoi(argv[1])); /* porta local  */
	bzero(&(loc_addr.sin_zero), 8);

   	/* Bind para o endereco local*/
	/* parametros(descritor socket, estrutura do endereco local, comprimento do endereco) */
	if (bind(loc_sockfd, (struct sockaddr *) &loc_addr, sizeof(struct sockaddr)) < 0)
	{
		perror("Ligando stream socket");
		exit(1);
	}

	/* parametros(descritor socket,
	numeros de conexoes em espera sem serem aceites pelo accept)*/
	listen(loc_sockfd, 5);
	printf("> aguardando conexao\n");

	tamanho = sizeof(struct sockaddr_in);
   	/* Accept permite aceitar um pedido de conexao, devolve um novo "socket" ja ligado ao emissor do pedido e o "socket" original*/
	/* parametros(descritor socket, estrutura do endereco local, comprimento do endereco)*/
    loc_newsockfd =	accept(loc_sockfd, (struct sockaddr *)&loc_addr, &tamanho);

	do {
		/* parametros(descritor socket, endereco da memoria, tamanho da memoria, flag) */
 		recv(loc_newsockfd, &linha, sizeof(linha), 0);
		printf("Recebi %s\n", linha);

		/* parametros(descritor socket, endereco da memoria, tamanho da memoria, flag) */
		send(loc_newsockfd, &linha, sizeof(linha), 0);
		printf("Renvia %s\n", linha);
	} while(strcmp(linha,"exit"));
	/* fechamento do socket local */
	close(loc_sockfd);
	close(loc_newsockfd);
}
