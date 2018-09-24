
#include "func.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int socket_init()
{
#ifndef _WIN32
	return 0;
#else
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

    wVersionRequested = MAKEWORD(1, 1); // Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h
    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        printf("WSAStartup failed with error: %d\n", err); 	// Tell the user that we could not find a usable  Winsock DLL.
        return 1;
    }
	return 0;
#endif
}

int socket_stop(SOCKET connection_socket)
{
#ifdef _WIN32
	closesocket(connection_socket);
	WSACleanup();
#else
	close(connection_socket);
#endif
	return 0;
}
int connect_to_host(const char* host)
{
	struct hostent* server =  gethostbyname(host);
	SOCKET server_socket;
	if (server != NULL)
		server_socket = socket( server->h_addrtype, SOCK_STREAM, 0 );
	else
		return INVALID_SOCKET;
	int port = 8888;
	struct sockaddr_in server_addr;

	setup_server_addr( host, port, server_socket, &server_addr, server );		
	move_at_server( server_socket );

	return server_socket;
}
void setup_server_addr(const char* host, int port, SOCKET server_socket,  struct sockaddr_in* server_addr, const struct hostent* server)
{
	server_addr->sin_family = server->h_addrtype;
	memcpy( &server_addr->sin_addr.s_addr, server->h_addr, server->h_length );

	server_addr->sin_port = htons(port);

	if ( connect( server_socket, (struct sockaddr* ) server_addr, sizeof( *server_addr ) ) < 0 )
        	error("ERROR connecting");
}

void move_at_server( SOCKET server_socket )
{
	const size_t kSocketBufferSize = 256;		            
	const size_t kUserCommandSize = 64;		                
	char* socket_buffer = (char*)malloc(kSocketBufferSize);
	char* user_command = (char*)malloc(kUserCommandSize);
	const char* kQquit = "exit";

	do
	{
		do
		{
			user_command[0]='\0';		//in case user inputs incorrect command
			fgets( user_command, kUserCommandSize, stdin );
			size_t last_char = strlen( user_command ) -1;		// to overwrite '\n' in user_command char array.
			user_command[last_char] = '\0';
		}
		while( incorrect_command( user_command ) );
		
		send( server_socket, user_command, kUserCommandSize, 0 );
		recv( server_socket, socket_buffer, kSocketBufferSize, 0 );

		printf( "%s\n", socket_buffer );
		reset_buffers( socket_buffer, user_command );	//set buffers to zero
        
	}
	while( strcmp( user_command, kQquit ) != 0 );

	free( socket_buffer );
	free( user_command );
}
int incorrect_command( char* user_command )
{
	int incorrect = 0;
	if	( (	
		 strncmp(user_command, "ls", 2)  &&
		 strncmp(user_command, "cd", 2)  &&
	 	 strncmp(user_command, "mv", 2) && 
	 	 strncmp(user_command, "pwd", 3) &&
	 	 strncmp(user_command, "exit", 4) 
		) )
	{
		incorrect = -1;
		printf("incorrect command\n");
	}
	return incorrect;
}
void reset_buffers(char* socket_buffer, char* user_command)
{
	memset( socket_buffer, 0, strlen(socket_buffer) );
	if ( strcmp( user_command, "exit" ) != 0 )
    		memset( user_command, 0, strlen(user_command) );
}
void error(const char *msg)
{
	perror(msg);
	exit(0);
}
