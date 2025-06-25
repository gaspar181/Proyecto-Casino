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
    Color color;        // para apuesta por color (incluye VERDE)
    int tercio_inicio;  // para apuesta por rango
    int tercio_fin;
} Apuesta;

// Inicializa el arreglo de casillas de la ruleta
void inicializarRuleta(CasillaRuleta ruleta[]);

// Retorna un número aleatorio entre 0 y TOTAL_CASILLAS - 1, simulando giro ruleta
int girarRuleta();

// Calcula la ganancia para una apuesta específica según resultado y jugador
double calcularPago(Apuesta* apuesta, CasillaRuleta ruleta[], int resultado, Jugador* j);

// Calcula la ganancia total para múltiples apuestas (arreglo) según resultado y jugador
double calcularPagosMultiples(Apuesta apuestas[], int cantidad, CasillaRuleta ruleta[], int resultado, Jugador* j);

// Permite ingresar apuestas del jugador, hasta un máximo, y devuelve la cantidad de apuestas ingresadas
int ingresarApuestas(Apuesta apuestas[], int max, Jugador* jugador);

// Ejecuta el juego de ruleta para un jugador
void jugarRuleta(Jugador *j);

#endif // RULETA_H