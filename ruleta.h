#ifndef RULETA_H
#define RULETA_H

#include "jugador.h"
#include "TDAS/list.h"  

#define TOTAL_CASILLAS 37

// Estructuras para toda la ruleta

typedef enum {
    VERDE = 0,          // para division de Colores 
    ROJO = 1,           
    NEGRO = 2           
} Color;

typedef struct {
    int numero;          // Estructura numero ruleta 
    Color color;         // Color del numero (ruleta europea)
} CasillaRuleta;

typedef enum {
    APUESTA_NUMERO = 0,         // para division de tercios
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


// Inicializar para el funcionamiento de la ruleta
void inicializarRuleta(CasillaRuleta ruleta[]);
int girarRuleta();
double calcularPago(Apuesta* apuesta, CasillaRuleta ruleta[], int resultado, Jugador* j);
double calcularPagosMultiples(List *apuestas, CasillaRuleta ruleta[], int resultado, Jugador* j);
List *ingresarApuestas(Jugador* jugador);
void limpiarApuestas(List *apuestas);
void jugarRuleta(Jugador *j);

#endif