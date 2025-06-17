#include <stdio.h>
#include <string.h>
#include "jugador.h"

void inicializarJugador(Jugador *j) {
    printf("¡Bienvenido al Casino Virtual!\n");
    printf("Por favor, ingresa tu nombre: ");
    fgets(j->nombre, MAX_NOMBRE, stdin);
    size_t len = strlen(j->nombre);
    if (len > 0 && j->nombre[len - 1] == '\n') {
        j->nombre[len - 1] = '\0';
    }

    int opcion = 0;
    char buffer[10];

    printf("\n%s, antes de comenzar, elige cuánto quieres apostar para esta noche:\n", j->nombre);
    printf("1) Prefiero empezar tranquilo, con un presupuesto modesto ($500).\n");
    printf("2) Me siento con suerte y quiero jugar con $1000.\n");
    printf("3) Quiero una noche increíble y arriesgar $2000.\n");

    while (1) {
        printf("Selecciona tu opción (1, 2 o 3): ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &opcion) == 1) {
                if (opcion >= 1 && opcion <= 3) {
                    break;  // opción válida
                }
            }
        }
        printf("Opción inválida. Por favor ingresa 1, 2 o 3.\n");
    }

    switch (opcion) {
        case 1:
            j->saldo = 500.0;
            printf("\nHas escogido comenzar tranquilo. ¡Buena suerte con $500!\n");
            break;
        case 2:
            j->saldo = 1000.0;
            printf("\nConfías en tu suerte. ¡A jugar con $1000!\n");
            break;
        case 3:
            j->saldo = 2000.0;
            printf("\n¡Una noche increíble! Juega con $2000 y disfruta.\n");
            break;
    }

    j->turnos_jugados = 0;
    j->multiplicador_actual = 1.0;
}