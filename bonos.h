#ifndef BONOS_H
#define BONOS_H

#define MAX_NOMBRE_BONIFICADOR 50

// Estructuras necesarias para los bonificadores 

struct Jugador;

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

typedef struct Bonificador{
    char nombre[MAX_NOMBRE_BONIFICADOR];
    TipoBonificador tipo;
    EfectoBonificador efecto;
    double valor_efecto;
} Bonificador;

void inicializarBonificadores();
Bonificador seleccionarBonificadorAleatorio();
void aplicarBonificador(Bonificador b, struct Jugador *j);
void mostrarBonificador(Bonificador b);

#endif