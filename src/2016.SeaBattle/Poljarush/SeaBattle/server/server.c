// A simple server in the internet domain using TCP.  // default port number is 8888.AWD // commands:
// cd [dir] - change directory
// pwd - show current directory
// ls [dir] - show directory content
// mv FILENAME DEST_DIRECTORY- move file FILENAME from current directory to DEST_DIRECTORY

#include "func.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
	SOCKET connection_socket;
	int port = 8888;
	struct sockaddr_in* server_addr = setup_server( &connection_socket, port );

	socket_init();
	manage_connections( connection_socket );
	socket_stop( connection_socket );
     
	return 0;
}
