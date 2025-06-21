CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRC = main.c menu.c ruleta.c apuestas.c blackjack.c bonos.c utils.c jugador.c \TDAS/map.c TDAS/list.c TDAS/stack.c
OBJ = $(SRC:.c=.o)
EXEC = casino

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)