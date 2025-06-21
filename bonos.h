#ifndef BONOS_H
#define BONOS_H

#include "jugador.h"

#define MAX_NOMBRE_BONIFICADOR 50

typedef enum {
    BUENO,
    MALO
} TipoBonificador;

typedef enum {
    AUMENTAR_GANANCIA,
    DUPLICAR_APUESTA,
    PERDER_TURNOS,
    REDUCIR_MULTIPLICADOR,
    BONO_EXTRA,
    CAMBIO_SALDO_ALEATORIO
} EfectoBonificador;

typedef struct {
    char nombre[MAX_NOMBRE_BONIFICADOR];
    TipoBonificador tipo;
    EfectoBonificador efecto;
    double valor_efecto;
} Bonificador;

void inicializarBonificadores();
Bonificador seleccionarBonificadorAleatorio();
void aplicarBonificador(Bonificador b, Jugador *j);
void mostrarBonificador(Bonificador b);

#endif