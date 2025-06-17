#ifndef MENU_H
#define MENU_H

#include "jugador.h"

// Menús principales
void menu_inicio();
void menu_principal(Jugador *j);
void menu_juego(Jugador *j);
void menu_bonificadores(Jugador *j);

// Funciones de los juegos (se pueden implementar en sus propios archivos)
void jugarBlackjack(Jugador *j);
void jugarRuleta(Jugador *j);
void jugarApuestasDeportivas(Jugador *j);

// Función para mostrar y manejar bonificadores
void mostrarBonificadores(Jugador *j);

#endif