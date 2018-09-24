
#include <stdio.h>

char* execute( char* user_command );
char* dir_contents(char* path);
char* move_file( char* file, char* source_dir, char* dest_dir );
char* error_occured(int err_num);
void parse ( char* , char** , char** );
char* parse_path ( const char* filename, const char* dirpath );
void copy_file( FILE* cur_file, FILE* new_file );
