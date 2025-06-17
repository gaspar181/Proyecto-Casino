#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include "jugador.h"

void menu_inicio();
void menu_principal(Jugador *j);
void menu_juego(Jugador *j);
void menu_bonificadores(Jugador *j);

// Funciones utilitarias directamente en este archivo
void limpiarPantalla();
void presioneTeclaParaContinuar();

#endif
