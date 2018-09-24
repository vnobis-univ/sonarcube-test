mftp: client.o func.o
	gcc client.o func.o -o mftp
client.o: client.c func.h
	gcc -c client.c
func.o: func.c func.h
	gcc -c func.c
