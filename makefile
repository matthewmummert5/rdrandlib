CC = gcc

TEST.exe: main.c rdrandlib.c
	$(CC) main.c rdrandlib.c -o TEST.exe
