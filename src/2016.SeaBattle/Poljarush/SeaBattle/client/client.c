
#include "func.h"
#include <stdio.h>

int main(int argc, char *argv[])
{

    if (argc != 2){
        fprintf(stderr, "incorrect arguments. usage:\nmftp host_ip_address\n");
        return 0;
    }
	socket_init();
	SOCKET connection_socket;
	if ( (connection_socket = connect_to_host(argv[1])) == INVALID_SOCKET )
        	fprintf(stderr, "can't connect to host:\t%s\n", argv[1]);
	socket_stop(connection_socket);

    return 0;
}
