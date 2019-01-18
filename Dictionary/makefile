CC = gcc
CFLAGS = -Wall -Iinclude

main:
	$(CC) $(CFLAGS) -o bin/main src/main.c src/HashTableAPI.c src/spellCheck.c

testMain:
	$(CC) $(CFLAGS) -o bin/testMain src/testMain.c src/HashTableAPI.c

clean:
		rm bin/*
