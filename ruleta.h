#ifndef RULETA_H
#define RULETA_H
#include "jugador.h"

#define TOTAL_CASILLAS 37

typedef enum { VERDE, ROJO, NEGRO } Color;

typedef struct {
    int numero;
    Color color;
} CasillaRuleta;

typedef enum {
    APUESTA_NUMERO,
    APUESTA_COLOR,
    APUESTA_TERCIO
} TipoApuesta;

typedef struct {
    TipoApuesta tipo;
    int numero; // Para APUESTA_NUMERO
    Color color; // Para APUESTA_COLOR
    int tercio_inicio, tercio_fin; // Para APUESTA_TERCIO
    double cantidad; // Monto apostado
} Apuesta;


void inicializarRuleta(CasillaRuleta ruleta[]);
int girarRuleta();
double calcularPago(Apuesta* apuesta, CasillaRuleta ruleta[], int resultado, Jugador *j);

#endif