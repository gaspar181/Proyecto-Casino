#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ruleta.h"
#include "jugador.h"
#include "utils.h"  // limpiarPantalla y presioneTeclaParaContinuar

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

int girarRuleta() {
    return rand() % TOTAL_CASILLAS;
}

double calcularPago(Apuesta* apuesta, CasillaRuleta ruleta[], int resultado, Jugador* j) {
    double m = j->multiplicador_actual;
    switch (apuesta->tipo) {
        case APUESTA_NUMERO:
            return (apuesta->numero == resultado) ? apuesta->cantidad * 36 * m : 0;
        case APUESTA_COLOR:
            return (ruleta[resultado].color == apuesta->color) ? apuesta->cantidad * 2 * m : 0;
        case APUESTA_TERCIO:
            return (resultado >= apuesta->tercio_inicio && resultado <= apuesta->tercio_fin)
                ? apuesta->cantidad * 3 * m : 0;
        default:
            return 0;
    }
}

double calcularPagosMultiples(Apuesta apuestas[], int cantidad, CasillaRuleta ruleta[], int resultado, Jugador* j) {
    double total = 0;
    for (int i = 0; i < cantidad; i++)
        total += calcularPago(&apuestas[i], ruleta, resultado, j);
    return total;
}

void mostrarResumenApuestas(Apuesta apuestas[], int cantidad) {
    printf("\nResumen de tus apuestas:\n");
    for (int i = 0; i < cantidad; i++) {
        printf("Apuesta #%d: ", i + 1);
        switch (apuestas[i].tipo) {
            case APUESTA_NUMERO:
                printf("Número %d | Monto: $%.2f\n", apuestas[i].numero, apuestas[i].cantidad);
                break;
            case APUESTA_COLOR:
                printf("Color %s | Monto: $%.2f\n", (apuestas[i].color == ROJO) ? "ROJO" : "NEGRO", apuestas[i].cantidad);
                break;
            case APUESTA_TERCIO:
                printf("Tercio %d-%d | Monto: $%.2f\n", apuestas[i].tercio_inicio, apuestas[i].tercio_fin, apuestas[i].cantidad);
                break;
        }
    }
}

int ingresarApuestas(Apuesta apuestas[], int max, Jugador* jugador) {
    int count = 0;
    double total_apostado = 0;

    printf("\nSaldo disponible: %.2f\n", jugador->saldo);

    while (count < max) {
        printf("\n--- Apuesta #%d ---\n", count + 1);
        printf("Tipo de apuesta:\n1. Número\n2. Color\n3. Tercio\n0. Terminar\nOpción: ");
        int opcion_tipo;
        scanf("%d", &opcion_tipo);

        if (opcion_tipo == 0) break;
        if (opcion_tipo < 1 || opcion_tipo > 3) {
            printf("Opción inválida.\n");
            continue;
        }

        Apuesta a;
        a.tipo = opcion_tipo - 1;

        printf("Ingrese cantidad a apostar: ");
        scanf("%lf", &a.cantidad);

        if (a.cantidad <= 0 || total_apostado + a.cantidad > jugador->saldo) {
            printf("Monto inválido o excede el saldo disponible.\n");
            continue;
        }

        int valido = 1;
        switch (a.tipo) {
            case APUESTA_NUMERO:
                printf("Ingrese número entre 0 y 36: ");
                scanf("%d", &a.numero);
                if (a.numero < 0 || a.numero > 36) {
                    printf("Número inválido.\n");
                    valido = 0;
                }
                break;

            case APUESTA_COLOR: {
                int color;
                printf("Ingrese color (0 = ROJO, 1 = NEGRO): ");
                scanf("%d", &color);
                if (color != ROJO && color != NEGRO) {
                    printf("Color inválido.\n");
                    valido = 0;
                } else {
                    a.color = (ColorRuleta)color;
                }
                break;
            }

            case APUESTA_TERCIO:
                printf("Ingrese inicio y fin del tercio (ej: 1 12): ");
                scanf("%d %d", &a.tercio_inicio, &a.tercio_fin);
                if (a.tercio_inicio < 1 || a.tercio_fin > 36 || a.tercio_inicio >= a.tercio_fin) {
                    printf("Tercio inválido.\n");
                    valido = 0;
                }
                break;
        }

        if (!valido) continue;

        apuestas[count++] = a;
        total_apostado += a.cantidad;
        printf("Apuesta registrada. Total apostado: %.2f / %.2f\n", total_apostado, jugador->saldo);
    }

    jugador->saldo -= total_apostado;
    return count;
}

void jugarRuleta(Jugador *j) {
    CasillaRuleta ruleta[TOTAL_CASILLAS];
    inicializarRuleta(ruleta);

    const int MAX_APUESTAS = 10;
    Apuesta apuestas[MAX_APUESTAS];
    int cantidad_apuestas;

    limpiarPantalla();
    printf("=== Juego Ruleta ===\n");

    cantidad_apuestas = ingresarApuestas(apuestas, MAX_APUESTAS, j);
    if (cantidad_apuestas == 0) {
        printf("No ingresaste apuestas. Volviendo al menú.\n");
        presioneTeclaParaContinuar();
        return;
    }

    mostrarResumenApuestas(apuestas, cantidad_apuestas);
    printf("\nPresiona Enter para girar la ruleta...");
    presioneTeclaParaContinuar();

    int resultado = girarRuleta();

    printf("\nLa ruleta giró y cayó en el número %d de color %s.\n", resultado,
        (ruleta[resultado].color == ROJO) ? "ROJO" :
        (ruleta[resultado].color == NEGRO) ? "NEGRO" : "VERDE");

    double ganancia = calcularPagosMultiples(apuestas, cantidad_apuestas, ruleta, resultado, j);
    if (ganancia > 0) {
        printf("¡Ganaste $%.2f!\n", ganancia);
        j->saldo += ganancia;
    } else {
        printf("No ganaste esta vez.\n");
    }

    j->turnos_jugados++;
    presioneTeclaParaContinuar();
}