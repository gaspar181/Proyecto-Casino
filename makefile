CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRC = main.c menu.c ruleta.c apuestas.c blackjack.c bonificadores.c utils.c jugador.c
OBJ = $(SRC:.c=.o)
EXEC = casino

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)