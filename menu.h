#ifndef MENU_H
#define MENU_H

#include "jugador.h"

// Menús principales
void menu_inicio();
void menu_juego(Jugador *j);
void menu_bonificadores(Jugador *j);

// Funciones de los juegos
void jugarBlackjack(Jugador *j);
void jugarRuleta(Jugador *j);
void jugarApuestasDeportivas(Jugador *j);


#endif