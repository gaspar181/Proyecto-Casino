# Nombre del ejecutable
TARGET = casino.exe

# Compilador
CC = gcc

# Flags de compilación (opcional)
CFLAGS = -Wall -Wextra -std=c99 -Wno-unused-parameter -Wno-old-style-declaration

# Archivos fuente
SRCS = main.c menu.c ruleta.c apuesta.c blackjack.c bonos.c utils.c jugador.c ranking.c \
       ./TDAS/list.c ./TDAS/map.c

# Archivos objeto (cambia .c por .o)
OBJS = $(SRCS:.c=.o)

# Regla por defecto
all: $(TARGET)

# Cómo construir el ejecutable
$(TARGET): $(OBJS)
	@echo "Casino Abierto"
	@$(CC) $(OBJS) -o $(TARGET)

# Regla para compilar los .c en .o
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	del /Q *.o *.exe 2>nul || true

# Limpiar todo
mrproper: clean
	del /Q *~ 2>nul || true