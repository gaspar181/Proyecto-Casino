#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ruleta.h"
#include "jugador.h"
#include "utils.h"  

// Funcion que para generar la ruleta 
void inicializarRuleta(CasillaRuleta ruleta[]) {
    for (int i = 0; i < TOTAL_CASILLAS; i++) {
        ruleta[i].numero = i;
        if (i == 0) ruleta[i].color = VERDE;
        else if ((i >= 1 && i <= 10) || (i >= 19 && i <= 28))
            ruleta[i].color = (i % 2 == 0) ? NEGRO : ROJO;
        else
            ruleta[i].color = (i % 2 == 0) ? ROJO : NEGRO;
    }
}


// Seleccionar un numero de la ruleta
int girarRuleta() {
    return rand() % TOTAL_CASILLAS;
}

// Calcular el pago del jugador segun el tipo de apuesta que realizo
double calcularPago(Apuesta* apuesta, CasillaRuleta ruleta[], int resultado, Jugador* j) {
    double m = j->multiplicador_actual;
    switch (apuesta->tipo) {
        case APUESTA_NUMERO:
            return (apuesta->numero == resultado) ? apuesta->cantidad * 36 * m : 0;

        case APUESTA_COLOR:
            if (apuesta->color == VERDE) {
                return (ruleta[resultado].color == VERDE) ? apuesta->cantidad * 17 * m : 0;
            } else {
                return (ruleta[resultado].color == apuesta->color) ? apuesta->cantidad * 2 * m : 0;
            }

        case APUESTA_TERCIO:
            return (resultado >= apuesta->tercio_inicio && resultado <= apuesta->tercio_fin) ? apuesta->cantidad * 3 * m : 0;

        default:
            return 0;
    }
}


// Revisar la lista de apuestas y dar su pago total
double calcularPagosMultiples(List *apuestas, CasillaRuleta ruleta[], int resultado, Jugador* j) {
    double total = 0;
    Apuesta *apuesta = (Apuesta *)list_first(apuestas);
    while (apuesta != NULL) {
        total += calcularPago(apuesta, ruleta, resultado, j);
        apuesta = (Apuesta *)list_next(apuestas);
    }
    return total;
}


// Funcion que crea la lista y genera las apuestas multiples
List *ingresarApuestas(Jugador* jugador) {
    List *apuestas = list_create();
    if (!apuestas) {
        printf("Error al crear la lista de apuestas.\n");
        return NULL;
    }

    double total_apostado = 0;
    while (1) {
        printf("\nSaldo disponible: %.2f\n", jugador->saldo - total_apostado);

        int tipo;
        printf("\n--- Nueva Apuesta ---\n");
        printf("Tipo de apuesta:\n1. Número\n2. Color\n3. Tercio\n0. Terminar\nOpción: ");
        scanf("%d", &tipo);

        if (tipo == 0) break;
        if (tipo < 1 || tipo > 3) {
            printf("Opción inválida.\n");
            continue;
        }

        Apuesta *a = malloc(sizeof(Apuesta));
        if (!a) {
            printf("Error al reservar memoria para apuesta.\n");
            break;
        }

        a->tipo = tipo - 1;

        printf("Ingrese cantidad a apostar: ");
        scanf("%lf", &a->cantidad);

        if (a->cantidad <= 0 || total_apostado + a->cantidad > jugador->saldo) {
            printf("Monto inválido o excede el saldo restante.\n");
            free(a);
            continue;
        }

        switch (a->tipo) {
            case APUESTA_NUMERO:
                printf("Ingrese número entre 0 y 36: ");
                scanf("%d", &a->numero);
                if (a->numero < 0 || a->numero > 36) {
                    printf("Número inválido.\n");
                    free(a);
                    continue;
                }
                break;

            case APUESTA_COLOR: {
                printf("Ingrese color (0 = VERDE, 1 = ROJO, 2 = NEGRO): ");
                int c;
                scanf("%d", &c);
                if (c < VERDE || c > NEGRO) {
                    printf("Color inválido.\n");
                    free(a);
                    continue;
                }
                a->color = (Color)c;
                break;
            }

            case APUESTA_TERCIO: {
                printf("Seleccione el tercio para apostar:\n");
                printf("1. Del 1 al 12\n");
                printf("2. Del 13 al 24\n");
                printf("3. Del 25 al 36\n");
                printf("Opción: ");
                int opcion_tercio;
                scanf("%d", &opcion_tercio);

                if (opcion_tercio < 1 || opcion_tercio > 3) {
                    printf("Opción de tercio inválida.\n");
                    free(a);
                    continue;
                }

                if (opcion_tercio == 1) {
                    a->tercio_inicio = 1;
                    a->tercio_fin = 12;
                } else if (opcion_tercio == 2) {
                    a->tercio_inicio = 13;
                    a->tercio_fin = 24;
                } else {
                    a->tercio_inicio = 25;
                    a->tercio_fin = 36;
                }
                break;
            }
        }

        list_pushBack(apuestas, a);
        total_apostado += a->cantidad;
        printf("Total apostado: %.2f / %.2f\n", total_apostado, jugador->saldo);
    }

    jugador->saldo -= total_apostado;
    return apuestas;
}


// Vacias la lista de apuestas
void limpiarApuestas(List *apuestas) {
    if (!apuestas) return;

    Apuesta *apuesta = (Apuesta *)list_first(apuestas);
    while (apuesta != NULL) {
        free(apuesta);
        apuesta = (Apuesta *)list_next(apuestas);
    }
    list_clean(apuestas);
    free(apuestas);
}


// Funcion para jugar a la ruleta
void jugarRuleta(Jugador *j) {
    CasillaRuleta ruleta[TOTAL_CASILLAS];
    inicializarRuleta(ruleta);

    limpiarPantalla();
    printf("=== Juego Ruleta ===\n");

    List *apuestas = ingresarApuestas(j);
    if (apuestas == NULL || list_size(apuestas) == 0) {
        printf("No ingresaste apuestas. Volviendo al menú.\n");
        presioneTeclaParaContinuar();
        if (apuestas) limpiarApuestas(apuestas);
        return;
    }

    int resultado = girarRuleta();

    printf("La ruleta giró y cayó en el número %d de color %s.\n", resultado,
           (ruleta[resultado].color == ROJO) ? "ROJO" :
           (ruleta[resultado].color == NEGRO) ? "NEGRO" :
           "VERDE");

    double ganancia = calcularPagosMultiples(apuestas, ruleta, resultado, j);
    if (ganancia > 0) {
        printf("¡Ganaste $%.2f!\n", ganancia);
        j->saldo += ganancia;
    } else {
        printf("No ganaste esta vez.\n");
    }

    j->turnos_jugados++;
    j->multiplicador_actual = 1;
    presioneTeclaParaContinuar();

    limpiarApuestas(apuestas);
}