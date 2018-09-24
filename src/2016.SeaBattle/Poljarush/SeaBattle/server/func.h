#ifndef FUNC_H_
#define FUNC_H_

#ifndef _WIN32

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

#define INVALID_SOCKET -1
typedef int SOCKET;

#else

#include <winsock.h>
typedef int socklen_t

#endif

int socket_init();
int socket_stop(SOCKET);
struct sockaddr_in* setup_server( SOCKET* socket_descr, int port );
void manage_connections(SOCKET socket_descr);

#endif // FUNC_H_
