#ifndef JUGADOR_H
#define JUGADOR_H

#define MAX_NOMBRE 50

typedef struct {
    char nombre[MAX_NOMBRE];
    double saldo;               // Dinero con el que empieza y juega el jugador
    int turnos_jugados;         // Cantidad de turnos que ha jugado
    float multiplicador_actual; // Multiplicador activo por bonificadores
} Jugador;

// Función para inicializar el jugador con nombre y saldo inicial según opción
void inicializarJugador(Jugador *j);

#endif