
#include "user_commands.h"
static const char end_session[5] = "exit";
#ifndef _WIN32

#include <dirent.h>		//LINUX
static const char list_contents[3] = "ls";
static const char curr_dir[4] = "pwd";
static const char mv_file[3] = "mv";
static const char change_dir[3] = "cd";

#else

#include <direct.h>		//WINDOWS
#include <io.h>
#define chdir _chdir
#define getcwd _getcwd
static const char list_contents[4] = "dir";
static const char curr_dir[3] = "cd";
static const char mv_file[5] = "move";
static const char* change_dir = curr_dir;

#endif

#include <stdlib.h> 
#include <string.h>
#include <errno.h>

char* execute( char* user_command )
{
	char* arg_1;
	char* arg_2;
	parse( user_command, &arg_1, &arg_2 ); //parse user_command string into format "user_command arg_1 arg_2"

	static const size_t kBuffSz = 128; 					//get current working directory
	char* path = (char*)malloc(kBuffSz);
	getcwd( path, kBuffSz );

	char* client_output;
	if( strcmp( user_command, list_contents ) == 0 || strcmp( user_command, change_dir ) == 0 )
	{
		if (arg_1 != NULL ) 
		{
			free(path);
			path = arg_1;
		}	

		client_output = dir_contents( path );
		if( strcmp( user_command, change_dir ) == 0 )
			chdir( path );
	}
	else
	if( strcmp( user_command, curr_dir ) == 0 || strcmp( user_command, end_session ) == 0 )
		client_output = path;
	else
	if( strcmp( user_command, mv_file ) == 0 )
	{
		client_output = move_file( arg_1, path, arg_2 );
		free( path );
	}

	return client_output;
}	
char* dir_contents( char* path )
{
	const size_t kDirContentsSz = 256;
	char* contents = (char*) malloc( kDirContentsSz );
	char* offset = contents;
	DIR* dir_stream;
	if ( ( dir_stream = opendir( path ) ) == NULL )  
	{
		contents = error_occured ( errno );
	}
	else
	{
		struct dirent* current_dir = readdir( dir_stream );  
		while( ( current_dir = readdir( dir_stream ) ) != NULL )
		{
			if ( '.' != current_dir->d_name[0] )		//ignore hidden files and directories
			{
				strcpy( offset, current_dir->d_name );
				offset += strlen( current_dir->d_name );
				*offset++ = '\n';
			}
		}
		if( contents == offset )		//if directory is empty 
			*offset++ = '\n';			//return blank line
		*offset = '\0';
	}
	return contents;
}
char* move_file( char* file, char* source_dir, char* dest_dir )
{
	char* new_filepath;
	char* old_filepath;
	FILE* cur_file = fopen( file, "rb");
	if( cur_file == NULL )
	{
		new_filepath = error_occured ( errno );
	}
	else
	{
		new_filepath = parse_path ( file, dest_dir );
		old_filepath = parse_path ( file, source_dir );

		FILE* new_file = fopen( new_filepath , "wb" );
		if( new_file == NULL )
		{
			free( new_filepath );
			new_filepath = error_occured ( errno );
		}
		else
		{
			copy_file ( cur_file, new_file );
			unlink ( old_filepath );													//delete file from previous location
			fclose ( new_file );
		}
		fclose( cur_file );
		free( old_filepath );
	}

	return new_filepath;
}
char* error_occured(int err_num)
{
	char* msg = strerror(err_num);
	char* err_msg = (char*)malloc( strlen(msg) );
	memcpy( err_msg, msg, strlen(msg) );
	return err_msg;
}	
void parse ( char* user_command, char** arg_1, char** arg_2 )
{
	*arg_1 = strpbrk( user_command, " " );			 //parse user_command string into format "user_command arg_1 arg_2"
	if( *arg_1 != NULL )
	{
		**arg_1 = '\0';								//seperate arg_1 from user_command: |user_command|'\0'|arg_1|
		++(*arg_1);									//advance to start of arg_1
		*arg_2 = strpbrk( *arg_1, " " );	
		if( *arg_2 != NULL )
		{
			**arg_2 = '\0';							//seperate arg_2 from arg_1: |user_command|'\0\|arg_1|'\0'|arg_2|
			++(*arg_2);								//advance to start of arg_2
		}		
	}
}
char* parse_path ( const char* filename, const char* dirpath )
{
	#ifndef _WIN32
	static const char delim = '/';		//delimiter used in pathways in linux
	static const short delim_sz = 2;
	#else
	static const char delim = "\\";		//delimiter used in pathways in windows
	static const short delim_sz = 3;
	#endif

	char* filepath = (char*)malloc( strlen(dirpath) + delim_sz + strlen(filename) );	// memory block of filepath at thios point:|____________|
	char* offset = (char*)memcpy( filepath, dirpath, strlen(dirpath) );					// copy dirpath into filepath: |/dirpath______|
	offset += strlen(dirpath);															// move pointer to the end of dirpath section of filepath
	*offset = delim;																	// and insert delimiter: |/dirpath/______|
	offset += delim_sz - 1;																// move ptr to correct postion
	strcpy( offset, filename );															// and copy filename to filepath to get: |/dirpath/filename|'\0'|

	return filepath;
}
void copy_file( FILE* cur_file, FILE* new_file )
{
	const unsigned ONE_MB = 1024*1024;

	fseek( cur_file, 0, SEEK_END);		//get file size
	unsigned file_sz = ftell( cur_file ); 
	unsigned block_sz = file_sz;
	char* buffer; 
	rewind(cur_file);				//go to start of file

	if (file_sz < ONE_MB)
		buffer = (char*)malloc(file_sz);
	else	
	{
		buffer = (char*)malloc(ONE_MB);
		block_sz = ONE_MB;
	}

	while ( !feof( cur_file ) && fread( buffer, block_sz, 1, cur_file )  )		//copy file to new location
		fwrite( buffer, block_sz, 1, new_file );	

	free(buffer);
}
