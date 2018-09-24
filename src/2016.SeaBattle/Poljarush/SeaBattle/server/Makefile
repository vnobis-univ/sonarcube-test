server: server.o func.o user_commands.o
	gcc -o server server.o func.o user_commands.o
server.o: server.c
	gcc -c server.c
func.o: func.c func.h user_commands.h
	gcc -c func.c
user_commands.o: user_commands.c user_commands.h
	gcc -c user_commands.c
