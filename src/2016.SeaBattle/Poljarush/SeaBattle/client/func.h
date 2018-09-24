#ifndef FUNC_H_
#define FUNC_H_

#ifndef _WIN32
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#define INVALID_SOCKET -1
typedef int SOCKET;
#else
#include <winsock.h>
#endif

int socket_init();
int socket_stop(SOCKET);
void setup_server_addr( const char* ,int , SOCKET, struct sockaddr_in* , const struct hostent* server );
void move_at_server( SOCKET ); 
int incorrect_command( char* );
void setup_buffers(const size_t, const size_t);
void reset_buffers(char*, char*);
void reset(char**);
int connect_to_host(const char*);
void error(const char *);


#endif // FUNC_H_
