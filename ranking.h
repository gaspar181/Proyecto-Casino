#ifndef RANKING_H
#define RANKING_H

#include "jugador.h"
// Estructura de ranking 
typedef struct {
    char nombre[100];
    float saldo;
} RegistroRanking;

// Funciones para guardar y ver ranking
void guardarRanking(Jugador *j);
void mostrarRanking();
void limpiarRanking();

#endif