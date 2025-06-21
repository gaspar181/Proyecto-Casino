#ifndef JUGADOR_H
#define JUGADOR_H

#define MAX_NOMBRE 50

#include "bonos.h"

typedef struct {
    char nombre[MAX_NOMBRE];
    double saldo;
    int turnos_jugados;
    float multiplicador_actual;
    Bonificador ultimo_bonificador;  
} Jugador;

// Función para inicializar el jugador con nombre y saldo inicial según opción
void inicializarJugador(Jugador *j);

#endif