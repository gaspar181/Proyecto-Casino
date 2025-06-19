#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "TDAS/stack.h"
#include "TDAS/map.h"
#include "jugador.h"

typedef struct {
    int numero;      // 1 al 13
    char pinta[10];  // pica, corazón, diamante, trébol
} Carta;

Map *barajarCartas();      // Devuelve un mapa ordenado con claves aleatorias
Stack *generarMazo();      // Usa el mapa barajado para crear el mazo en pila
int obtenerValorCarta(Carta *c); // 1 para As, 10 para J/Q/K, etc.
void jugarBlackjack(Jugador *j); // Modo consola, una ronda básica

#endif