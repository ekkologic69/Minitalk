NAME = minitalk

all: server client

server:
	gcc -Wall -Wextra -Werror  server.c -o server

client:
	gcc  -Wall -Wextra -Werror client.c -o client

clean:
	rm -f server client

fclean: clean

re: fclean all
