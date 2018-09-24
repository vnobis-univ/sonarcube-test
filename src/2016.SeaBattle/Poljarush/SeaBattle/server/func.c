
#include "func.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <errno.h>
#include "user_commands.h"

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
struct sockaddr_in* setup_server( SOCKET* socket_descr, int port )
{
	const int backlog_quantity = 5;
	struct sockaddr_in* server_addr = (struct sockaddr_in*)malloc( sizeof(struct sockaddr_in) );
	*socket_descr = socket( AF_INET, SOCK_STREAM, 0 );
	if ( *socket_descr == INVALID_SOCKET )
		error_occured(errno);
	
	memset( (char *) server_addr, 0, sizeof( *server_addr ) );
	server_addr->sin_family = AF_INET;
	server_addr->sin_addr.s_addr = htonl( INADDR_ANY );
	server_addr->sin_port = htons( port );

	if ( bind( *socket_descr, (struct sockaddr *) server_addr, sizeof( *server_addr ) ) < 0 )
		error_occured(errno);
	listen( *socket_descr, backlog_quantity );

	return server_addr;
}
void manage_connections( SOCKET socket_descr )
{
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);

	const size_t kUserCmmndSz = 100;	
	char* user_command = (char*)malloc( kUserCmmndSz );
	char* client_output; 
	int newsocket_descr;	
	while(1)
   	{
		newsocket_descr = accept( socket_descr, (struct sockaddr *) &client_addr, &client_len );
		do
		{
			memset( user_command, 0, kUserCmmndSz );
			recv( newsocket_descr, user_command, kUserCmmndSz, 0 );
			client_output = execute( user_command );

			printf( "%s", client_output );
			send( newsocket_descr, client_output, strlen( client_output ), 0 );
			memset( client_output, 0, strlen(client_output) );
			free( client_output );
		}
		while( strcmp( user_command, "exit" ) != 0 );
	#ifndef _WIN32
		close(newsocket_descr);
	#else
		closesocket(newsocket_descr);
	#endif
	}
	free( user_command );
}
