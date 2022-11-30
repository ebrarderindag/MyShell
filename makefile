CC = gcc

all: execx writef myshell

execx: execx.c
	$(CC) execx.c -o execx

writef: writef.c
	$(CC) writef.c -o writef


myshell: myshell.c
	$(CC) myshell.c -o myshell

clean:
	rm -rf *o all
