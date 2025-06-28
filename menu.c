#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "ruleta.h"
#include "utils.h"
#include <time.h>
#include "bonos.h"
#include "jugador.h"
#include "ranking.h"

#define TURNOS_MINIMOS 3

void menu_juego(Jugador *j) {
    if (j->saldo <= 0) {
        printf("¡Ya fue po! Al casino nunca se le gana, mi xan...\n");
        printf("Andate pa’ la casa con las manos vacías y vuelve cuando tengas plata.\n");
        guardarRanking(j);
        menu_inicio(&j);
        presioneTeclaParaContinuar();
        return;
    } else{
        int opcion;
        do {
            limpiarPantalla();
            printf("=== Menú de Juegos ===\n");
            printf("1. Blackjack\n");
            printf("2. Ruleta\n");
            printf("3. Apuestas Deportivas\n");
            printf("4. Bonificadores y estado del jugador\n");
            printf("0. Salir del casino\n");
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
                case 4:
                    menu_bonificadores(j);
                    break;
                case 0:
                    if (j->turnos_jugados >= TURNOS_MINIMOS || j->saldo <= 0) {
                        guardarRanking(j);
                        printf("Arrancaste con un saldo de: $%.2f\n", j->saldo);
                        printf("Se actualizo tu lugar en el ranking\n");
                        printf("Gracias por visitarnos, que te vaya bonito compadrito.\n");
                        exit(0);
                    } else {
                        int falta = TURNOS_MINIMOS - j->turnos_jugados;
                        printf("¡Oye no po! Aún no cumplís los turnos mínimos. Te faltan %d\n", falta);
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
                mostrarBonificador(j->ultimo_bonificador); 
                presioneTeclaParaContinuar();
                break;
            }
            case 2: {
                Bonificador nuevo = seleccionarBonificadorAleatorio();
                mostrarBonificador(nuevo);
                aplicarBonificador(nuevo, j);
                j->ultimo_bonificador = nuevo;
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
    srand(time(NULL));
    inicializarBonificadores();

    Jugador jugador;
    int opcion;

    while (1) {
        limpiarPantalla();
        printf("=== Bienvenido al Casino ===\n");
        printf("1. Iniciar Partida\n");
        printf("2. Ver Ranking\n");
        printf("3. Limpiar Ranking\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");

        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                inicializarJugador(&jugador);
                menu_juego(&jugador);
                break;

            case 2:
                mostrarRanking();
                presioneTeclaParaContinuar();
                break;

            case 3: {
                char opcion2;
                printf("¿Deseas limpiar el ranking? (s/n): \n");
                scanf(" %c", &opcion2);
                getchar(); // limpia salto de línea

                if (opcion2 == 's' || opcion2 == 'S') {
                    limpiarRanking();
                    printf("Ranking limpio\n");
                } else if (opcion2 == 'n' || opcion2 == 'N') {
                    printf("No se limpió el ranking\n");
                } else {
                    printf("No se seleccionó una opción válida\n");
                }
                presioneTeclaParaContinuar();
                break;
            }

            case 4:
                printf("Gracias por visitar el Casino.\n");
                exit(0);

            default:
                printf("Opción inválida.\n");
                presioneTeclaParaContinuar();
                break;
        }
    }
}