#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "ruleta.h"
#include "utils.h"
#include <time.h>

// Menú principal de juegos
void menu_juego(Jugador *j) {
    if (j->saldo <= 0) {
        printf("¡Ya fue po! Al casino nunca se le gana, mi xan...\n");
        printf("Andate pa’ la casa con las manos vacías y vuelve cuando tengas plata.\n");
        presioneTeclaParaContinuar();
        return;
    }

    int opcion;
    do {
        limpiarPantalla();
        printf("=== Menú de Juegos ===\n");
        printf("1. Blackjack\n");
        printf("2. Ruleta\n");
        printf("3. Apuestas Deportivas\n");
        printf("4. Bonificadores\n");
        printf("0. Salir del casino\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                jugarBlackjack(j);
                menu_bonificadores(j);
                break;
            case 2:
                jugarRuleta(j);
                menu_bonificadores(j);
                break;
            case 3:
                jugarApuestasDeportivas(j);
                menu_bonificadores(j);
                break;
            case 4:
                menu_bonificadores(j);
                break;
            case 0:
                if (j->turnos_jugados >= j->turnos_jugados) {
                    printf("Gracias por visitarnos, que te vaya bonito compadrito.\n");
                    exit(0);
                } else {
                    printf("¡Oye no po! Aún no cumplís los %d turnos mínimos.\n", j->turnos_jugados);
                    printf("¡No se arranca del casino tan fácil!\n");
                    presioneTeclaParaContinuar();
                }
                break;
            default:
                printf("Opción inválida.\n");
                presioneTeclaParaContinuar();
                break;
        }
    } while (1);
}


// Menú de bonificaciones
void menu_bonificadores(Jugador *j) {
    int opcion;
    do {
        limpiarPantalla();
        printf("=== Menú de Bonificadores ===\n");
        printf("1. Mostrar último bonificador\n");
        printf("2. Activar nuevo bonificador\n");
        printf("3. Ver estado del jugador\n");
        printf("0. Volver\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1: {
                mostrarBonificador(j->ultimo_bonificador); // O el último guardado
                presioneTeclaParaContinuar();
                break;
            }
            case 2: {
                Bonificador nuevo = seleccionarBonificadorAleatorio();
                mostrarBonificador(nuevo);
                aplicarBonificador(nuevo, j);
                j->ultimo_bonificador = nuevo; // si lo guardas
                presioneTeclaParaContinuar();
                break;
            }
            case 3: {
                limpiarPantalla();
                printf("=== ESTADO DEL JUGADOR ===\n");
                printf("Nombre: %s\n", j->nombre);
                printf("Saldo: $%.2f\n", j->saldo);
                printf("Turnos jugados: %d\n", j->turnos_jugados);
                printf("Multiplicador actual: %.2f\n", j->multiplicador_actual);
                presioneTeclaParaContinuar();
                break;
            }
            case 0:
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