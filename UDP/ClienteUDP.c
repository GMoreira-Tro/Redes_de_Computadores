#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

#define DEFAULT_PROTOCOL 0
#define INVALID -1
#define ECHOMAX 255

int main(int argc, char* argv[])
{
    //Acho extremamente feio um array de char, prefereria mil vezes um ponteiro de char. Mas, porém, todavia, entretanto,
    // eu entendi porque char* é extremamente inseguro de ler em runtime.
    char message[ECHOMAX];
	struct sockaddr_in serverTarget = {0};
	char* serverIP;

	int socketID = socket(AF_INET, SOCK_DGRAM, DEFAULT_PROTOCOL);
	if(socketID == INVALID)
	{
		perror("failed to create socket");
		exit(EXIT_FAILURE);
	}

	serverTarget.sin_family = AF_INET;
	serverIP = argv[1];
	serverTarget.sin_addr.s_addr = inet_addr(serverIP);
	serverTarget.sin_port = htons(6000);

	do
	{
        fgets(message, sizeof(message), stdin);
        message[strlen(message)- 1] = '\0';
        printf("%s - %d\n", message, (int)strlen(message));

        sendto(socketID, message, strlen(message),
		0, (const struct sockaddr *)&serverTarget, sizeof(serverTarget));

	}
	while (strcmp(message, "Sayonara"));

    close(socketID);
    return 0;
}
