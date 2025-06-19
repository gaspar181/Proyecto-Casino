#ifndef RULETA_H
#define RULETA_H

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

typedef struct {
    char nombre[50];
    double saldo;
    double saldo_inicial;
    int turnos_jugados;
    int puede_retirarse; // 0 o 1
    // bonificador, si implementan más adelante
} Jugador;

void inicializarRuleta(CasillaRuleta ruleta[]);
int girarRuleta();
double calcularPago(Apuesta* apuesta, CasillaRuleta ruleta[], int resultado, double bonificador);

#endif