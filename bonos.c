#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bonos.h"
#include "jugador.h"

#define TOTAL_BONIFICADORES 10

static Bonificador bonificadores[TOTAL_BONIFICADORES];


// Funcion que inicializa los bonificadores y entrega sus caracteristicas
void inicializarBonificadores() {

    strcpy(bonificadores[0].nombre, "Piscola brígida");
    bonificadores[0].tipo = BUENO;
    bonificadores[0].efecto = AUMENTAR_GANANCIA;
    bonificadores[0].valor_efecto = 0.3;

    strcpy(bonificadores[1].nombre, "Tequila mortal");
    bonificadores[1].tipo = MALO;
    bonificadores[1].efecto = PERDER_TURNOS;
    bonificadores[1].valor_efecto = 2;

    strcpy(bonificadores[2].nombre, "Terremoto con doble helado");
    bonificadores[2].tipo = BUENO;
    bonificadores[2].efecto = DUPLICAR_APUESTA;
    bonificadores[2].valor_efecto = 2.0;

    strcpy(bonificadores[3].nombre, "Ron con bebida dudosa");
    bonificadores[3].tipo = MALO;
    bonificadores[3].efecto = REDUCIR_MULTIPLICADOR;
    bonificadores[3].valor_efecto = 0.5;

    strcpy(bonificadores[4].nombre, "Te fuiste a la disco");
    bonificadores[4].tipo = MALO;
    bonificadores[4].efecto = PERDER_TURNOS;
    bonificadores[4].valor_efecto = 3;

    strcpy(bonificadores[5].nombre, "Alguien te invitó un bajativo");
    bonificadores[5].tipo = BUENO;
    bonificadores[5].efecto = BONO_EXTRA;
    bonificadores[5].valor_efecto = 300;

    strcpy(bonificadores[6].nombre, "Peleaste con el guardia");
    bonificadores[6].tipo = MALO;
    bonificadores[6].efecto = CAMBIO_SALDO_ALEATORIO;
    bonificadores[6].valor_efecto = 500;

    strcpy(bonificadores[7].nombre, "Caña moral");
    bonificadores[7].tipo = MALO;
    bonificadores[7].efecto = REDUCIR_MULTIPLICADOR;
    bonificadores[7].valor_efecto = 0.7;

    strcpy(bonificadores[8].nombre, "Peleaste con tu mina");
    bonificadores[8].tipo = MALO;
    bonificadores[8].efecto = PERDER_TURNOS;
    bonificadores[8].valor_efecto = 2;

    strcpy(bonificadores[9].nombre, "Te encontraste con una ex");
    bonificadores[9].tipo = MALO;
    bonificadores[9].efecto = BONO_EXTRA;
    bonificadores[9].valor_efecto = -300;
}


// Funcion que selecciona un Bono de manera aleatoria
Bonificador seleccionarBonificadorAleatorio() {
    int idx = rand() % TOTAL_BONIFICADORES;
    return bonificadores[idx];
}


// Funcion que aplica el Bono aleatorio 
void aplicarBonificador(Bonificador b, Jugador *j) {
    printf("\n>> %s te afecta...\n", b.nombre);

    switch (b.efecto) { // Aumenta el multiplicador
        case AUMENTAR_GANANCIA:
            j->multiplicador_actual += b.valor_efecto;
            printf("Ganancias aumentadas en %.0f%%\n", b.valor_efecto * 100);
            break;
        case DUPLICAR_APUESTA: // Multiplica el multiplicador
            j->multiplicador_actual *= b.valor_efecto;
            printf("Tus ganancias se multiplican por %.1f\n", b.valor_efecto);
            break;
        case PERDER_TURNOS: // Aumenta los turnos contados
            j->turnos_jugados += (int)b.valor_efecto;
            printf("Pierdes %d turnos\n", (int)b.valor_efecto);
            break;
        case REDUCIR_MULTIPLICADOR: // Reduce el multiplicador
            j->multiplicador_actual *= b.valor_efecto;
            printf("Tu multiplicador baja a %.0f%%\n", b.valor_efecto * 100);
            break;
        case BONO_EXTRA: // Suma o resta saldo directo
            j->saldo += b.valor_efecto;
            if (b.valor_efecto >= 0)
                printf("Recibes un bono de $%.0f\n", b.valor_efecto);
            else
                printf("Perdiste $%.0f por la mala vibra...\n", -b.valor_efecto);
            break;
        case CAMBIO_SALDO_ALEATORIO: { // Cambia saldo al azar dentro de un rango
            int cambio = (rand() % ((int)b.valor_efecto * 2 + 1)) - (int)b.valor_efecto;
            j->saldo += cambio;
            if (cambio >= 0)
                printf("¡Zafaste! Ganaste $%d tras el caos\n", cambio);
            else
                printf("Mala suerte... perdiste $%d\n", -cambio);
            break;
        }
        default:
            printf("Efecto desconocido.\n");
            break;
    }
}


// Funcion que printea el Bono
void mostrarBonificador(Bonificador b) {
    printf("\n=== BONIFICADOR ACTIVADO ===\n");
    printf("Trago/Situación: %s\n", b.nombre);
    printf("Tipo: %s\n", (b.tipo == BUENO ? "Bueno" : "Malo"));

    switch (b.efecto) {
        case AUMENTAR_GANANCIA: // Info textual según efecto
            printf("Efecto: Aumenta ganancia en %.0f%%\n", b.valor_efecto * 100); // Mensaje específico según efecto
            break;
        case DUPLICAR_APUESTA:
            printf("Efecto: Multiplica ganancia por %.1f\n", b.valor_efecto);
            break;
        case PERDER_TURNOS:
            printf("Efecto: Pierdes %d turnos\n", (int)b.valor_efecto);
            break;
        case REDUCIR_MULTIPLICADOR:
            printf("Efecto: Multiplicador reducido a %.0f%%\n", b.valor_efecto * 100);
            break;
        case BONO_EXTRA:
            printf("Efecto: Bono de $%.0f\n", b.valor_efecto);
            break;
        case CAMBIO_SALDO_ALEATORIO:
            printf("Efecto: Saldo cambia aleatoriamente hasta $%.0f\n", b.valor_efecto); 
            break;
        default:
            printf("Efecto no definido\n");
            break;
    }
}