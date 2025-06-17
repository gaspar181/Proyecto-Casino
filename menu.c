#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "ruleta.h"
#include "utils.h"
#include <time.h>

// Funciones auxiliares para juegos y bonificaciones
void jugarBlackjack(Jugador *j) {
    printf("Blackjack aún no implementado.\n");
    presioneTeclaParaContinuar();
}

void jugarRuleta(Jugador *j) {
    CasillaRuleta ruleta[TOTAL_CASILLAS];
    inicializarRuleta(ruleta);

    Apuesta apuesta;
    int opcion;
    printf("=== Juego de Ruleta ===\n");
    printf("Tipos de apuesta:\n");
    printf("1. Número (0-36)\n");
    printf("2. Color (Rojo o Negro)\n");
    printf("3. Rango (1-12, 13-24, 25-36)\n");
    printf("Seleccione tipo de apuesta: ");
    scanf("%d", &opcion);
    getchar();

    apuesta.cantidad = 0;
    apuesta.tipo = 0;

    switch (opcion) {
        case 1:
            apuesta.tipo = APUESTA_NUMERO;
            printf("Ingrese el número al que desea apostar (0-36): ");
            scanf("%d", &apuesta.numero);
            while (apuesta.numero < 0 || apuesta.numero > 36) {
                printf("Número inválido. Ingrese un número entre 0 y 36: ");
                scanf("%d", &apuesta.numero);
            }
            break;

        case 2:
            apuesta.tipo = APUESTA_COLOR;
            printf("Ingrese el color al que desea apostar (1=Rojo, 2=Negro): ");
            scanf("%d", &opcion);
            while (opcion != 1 && opcion != 2) {
                printf("Color inválido. Ingrese 1 para Rojo o 2 para Negro: ");
                scanf("%d", &opcion);
            }
            apuesta.color = (opcion == 1) ? ROJO : NEGRO;
            break;

        case 3:
            apuesta.tipo = APUESTA_RANGO;
            printf("Seleccione rango:\n");
            printf("1. 1 - 12\n");
            printf("2. 13 - 24\n");
            printf("3. 25 - 36\n");
            scanf("%d", &opcion);
            switch (opcion) {
                case 1:
                    apuesta.rango_inicio = 1;
                    apuesta.rango_fin = 12;
                    break;
                case 2:
                    apuesta.rango_inicio = 13;
                    apuesta.rango_fin = 24;
                    break;
                case 3:
                    apuesta.rango_inicio = 25;
                    apuesta.rango_fin = 36;
                    break;
                default:
                    printf("Rango inválido, se asignará 1-12 por defecto.\n");
                    apuesta.rango_inicio = 1;
                    apuesta.rango_fin = 12;
                    break;
            }
            break;

        default:
            printf("Opción inválida.\n");
            presioneTeclaParaContinuar();
            return;
    }

    printf("Ingrese la cantidad a apostar: ");
    scanf("%lf", &apuesta.cantidad);
    while (apuesta.cantidad <= 0) {
        printf("Cantidad inválida. Ingrese un valor positivo: ");
        scanf("%lf", &apuesta.cantidad);
    }

    int resultado = girarRuleta();
    printf("La ruleta gira... y sale el número %d (%s)\n",
           resultado,
           ruleta[resultado].color == ROJO ? "Rojo" :
           ruleta[resultado].color == NEGRO ? "Negro" : "Verde");

    double multiplicadorBonificacion = 1.0; // Por ahora sin bonificadores activos
    double ganancia = calcularPago(&apuesta, ruleta, resultado, multiplicadorBonificacion);

    if (ganancia > 0) {
        printf("¡Felicidades! Ganó %.2f unidades.\n", ganancia);
        j->saldo += ganancia;
    } else {
        printf("No ganó esta vez.\n");
        j->saldo -= apuesta.cantidad;
    }

    printf("Saldo actual: %.2f\n", j->saldo);

    presioneTeclaParaContinuar();
}

void jugarApuestasDeportivas(Jugador *j) {
    printf("Apuestas deportivas aún no implementadas.\n");
    presioneTeclaParaContinuar();
}

void mostrarBonificadores(Jugador *j) {
    printf("Gestión de bonificadores aún no implementada.\n");
    presioneTeclaParaContinuar();
}

// Menú principal de juegos
void menu_juego(Jugador *j) {
    int opcion;
    do {
        limpiarPantalla();
        printf("=== Menú de Juegos ===\n");
        printf("1. Blackjack\n");
        printf("2. Ruleta\n");
        printf("3. Apuestas Deportivas\n");
        printf("0. Volver\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                jugarBlackjack(j);
                break;
            case 2:
                jugarRuleta(j);
                break;
            case 3:
                jugarApuestasDeportivas(j);
                break;
            case 0:
                return;
            default:
                printf("Opción inválida.\n");
                presioneTeclaParaContinuar();
                break;
        }
    } while (opcion != 0);
}

// Menú de bonificaciones
void menu_bonificadores(Jugador *j) {
    int opcion;
    do {
        limpiarPantalla();
        printf("=== Menú de Bonificadores ===\n");
        printf("1. Mostrar bonificadores activos\n");
        printf("2. Activar bonificador\n");
        printf("3. Desactivar bonificador\n");
        printf("0. Volver\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
            case 2:
            case 3:
                mostrarBonificadores(j);
                break;
            case 0:
                return;
            default:
                printf("Opción inválida.\n");
                presioneTeclaParaContinuar();
                break;
        }
    } while (opcion != 0);
}

// Menú principal de la aplicación
void menu_principal(Jugador *j) {
    int opcion;
    do {
        limpiarPantalla();
        printf("=== Menú Principal ===\n");
        printf("1. Iniciar Juego\n");
        printf("2. Ver Ranking (pendiente)\n");
        printf("3. Bonificadores\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                menu_juego(j);
                break;
            case 2:
                printf("Ranking aún no implementado.\n");
                presioneTeclaParaContinuar();
                break;
            case 3:
                menu_bonificadores(j);
                break;
            case 0:
                printf("Gracias por jugar.\n");
                return;
            default:
                printf("Opción inválida.\n");
                presioneTeclaParaContinuar();
                break;
        }
    } while (opcion != 0);
}

// Menú de inicio (login o nueva partida)
void menu_inicio() {
    limpiarPantalla();
    printf("=== Bienvenido al Casino ===\n");
    printf("1. Iniciar Partida\n");
    printf("2. Ver Ranking (pendiente)\n");
    printf("3. Salir\n");
    printf("Seleccione una opción: ");

    int opcion;
    scanf("%d", &opcion);
    getchar();

    Jugador jugador;
    inicializarJugador(&jugador);

    switch (opcion) {
        case 1:
            menu_principal(&jugador);
            break;
        case 2:
            printf("Ranking aún no implementado.\n");
            presioneTeclaParaContinuar();
            menu_inicio();
            break;
        case 3:
            printf("Gracias por visitar el Casino.\n");
            exit(0);
        default:
            printf("Opción inválida.\n");
            presioneTeclaParaContinuar();
            menu_inicio();
            break;
    }
}