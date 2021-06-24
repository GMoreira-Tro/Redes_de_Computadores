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
    char buffer[ECHOMAX];

	struct sockaddr_in serverSender = {0};
	struct sockaddr_in serverFrom;

	int sizeOfServerSender = sizeof(serverSender);

	int socketID = socket(AF_INET, SOCK_DGRAM, DEFAULT_PROTOCOL);
	if (socketID == INVALID)
	{
		perror("failed to create socket");
		exit(EXIT_FAILURE);
	}

	serverSender.sin_family = AF_INET;
	serverSender.sin_port = htons(6000);
	serverSender.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(socketID, (const struct sockaddr *)&serverSender,
		sizeof(serverSender)) == INVALID)
	{
		perror("failed to bind");
		close(socketID);
		exit(EXIT_FAILURE);
	}
	else
	{
        do
        {
            memset(buffer, 0, strlen(buffer));

            recvfrom(socketID, buffer, sizeof(buffer), DEFAULT_PROTOCOL, (struct sockaddr*)&serverFrom,
            &sizeOfServerSender);

            printf("%s\n", buffer);

        }
        while(strcmp(buffer, "Sayonara"));
	}

	close(socketID);
    return 0;
}
