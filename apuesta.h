#ifndef APUESTAS_H
#define APUESTAS_H

#include "jugador.h"
#include "TDAS/map.h"

void to_lowercase(char* str);
void inicializarEquipos(Map* mapa);
void mostrarEquipos(Map* mapa);
void jugarApuestasDeportivas(Jugador* j);

#endif