#ifndef APUESTAS_H
#define APUESTAS_H

#include "TDAS/map.h"
#include "jugador.h"

// Inicializa el mapa de equipos deportivos con multiplicadores aleatorios
Map* crearEquipos();

// Muestra los equipos y sus multiplicadores
void mostrarEquipos(Map* equipos);

// Ejecuta una apuesta deportiva del jugador
void jugarApuestaDeportiva(Jugador* jugador, Map* equipos);

#endif
