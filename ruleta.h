#ifndef RULETA_H
#define RULETA_H

#include "jugador.h"

#define TOTAL_CASILLAS 37

typedef enum {
    VERDE = 0,
    ROJO = 1,
    NEGRO = 2
} Color;

typedef struct {
    int numero;
    Color color;
} CasillaRuleta;

typedef enum {
    APUESTA_NUMERO = 0,
    APUESTA_COLOR = 1,
    APUESTA_TERCIO = 2
} TipoApuesta;

typedef struct {
    TipoApuesta tipo;
    double cantidad;
    int numero;         // para apuesta por número
    Color color;        // para apuesta por color
    int tercio_inicio;  // para apuesta por rango
    int tercio_fin;
} Apuesta;

void inicializarRuleta(CasillaRuleta ruleta[]);
int girarRuleta();
double calcularPago(Apuesta* apuesta, CasillaRuleta ruleta[], int resultado, Jugador* j);
double calcularPagosMultiples(Apuesta apuestas[], int cantidad, CasillaRuleta ruleta[], int resultado, Jugador* j);
int ingresarApuestas(Apuesta apuestas[], int max, Jugador* jugador);
void jugarRuleta(Jugador *j);

#endif