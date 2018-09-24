#include "tests.h"
#include "user_commands.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	if (test_ls() == 1)
		printf("test_ls passed\n");
	else
		printf("test_ls FAILED\n");

	if (test_move_file() == 1)
		printf("test_move_file passed\n");
	else
		printf("test_move_file FAILED\n");
		
}
int test_ls()
{
	int passed = -1;
	chdir("/home");
	char* dir_contents = "dim\n";
	char* command = "ls /home";
	char* user_command = (char*)malloc(strlen(command));
	memcpy(user_command, command, strlen(command) );

	char* client_output = execute( user_command );
	if ( strcmp ( dir_contents, client_output ) == 0 )
		passed = 1;
	else
		passed = -1;

	free(user_command);
	free(client_output);
	return passed;
}
int test_move_file()
{
	int passed = -1;
	static char* source_dir = "/home/dim";
	static char* filename = "move_file";
	static char* dest_dir = "Videos";
	static char* output = "Videos/move_file";
	static char* command = "mv move_file Videos";

	char* user_command = (char*)malloc( strlen(command) );
	memcpy( user_command, command, strlen(command) );
	chdir(source_dir);
	char* client_output = execute(user_command);

	if ( strcmp ( output, client_output ) == 0 )
		passed = 1;
	else
		passed = -1;

	free(user_command);
	free(client_output);
	return passed;
}
