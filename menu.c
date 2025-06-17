#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void presioneTeclaParaContinuar() {
    printf("Presione una tecla para continuar...");
    getchar(); // Limpia el buffer
    getchar(); // Espera la tecla
}

void menu_inicio() {
    int opcion = 0;
    do {
        limpiarPantalla();
        printf("===== Bienvenido al Casino Virtual =====\n");
        printf("1. Iniciar partida\n");
        printf("2. Ver ranking\n");
        printf("3. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar(); // Limpia el salto de línea

        switch (opcion) {
            case 1:
                // Aquí debería crearse o inicializarse el jugador
                printf("Iniciando partida...\n");
                presioneTeclaParaContinuar();
                // Por ahora solo volver al menú para ejemplo
                break;
            case 2:
                printf("Mostrando ranking (no implementado aún)...\n");
                presioneTeclaParaContinuar();
                break;
            case 3:
                printf("Gracias por jugar. Hasta luego.\n");
                break;
            default:
                printf("Opción inválida. Intente nuevamente.\n");
                presioneTeclaParaContinuar();
        }
    } while (opcion != 3);
}

void menu_principal(Jugador *j) {
    int opcion = 0;
    do {
        limpiarPantalla();
        printf("===== Menú Principal =====\n");
        printf("Jugador: %s\n", j->nombre);
        printf("Dinero actual: %.2f\n", j->dinero);
        printf("1. Jugar\n");
        printf("2. Bonificadores\n");
        printf("3. Salir a menú inicial\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                menu_juego(j);
                break;
            case 2:
                menu_bonificadores(j);
                break;
            case 3:
                printf("Volviendo al menú inicial...\n");
                presioneTeclaParaContinuar();
                break;
            default:
                printf("Opción inválida. Intente nuevamente.\n");
                presioneTeclaParaContinuar();
        }
    } while (opcion != 3);
}

void menu_juego(Jugador *j) {
    int opcion = 0;
    do {
        limpiarPantalla();
        printf("===== Menú de Juegos =====\n");
        printf("1. Blackjack\n");
        printf("2. Ruleta\n");
        printf("3. Apuestas Deportivas\n");
        printf("4. Volver al menú principal\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                printf("Iniciando Blackjack (no implementado aún)...\n");
                presioneTeclaParaContinuar();
                break;
            case 2:
                printf("Iniciando Ruleta (no implementado aún)...\n");
                presioneTeclaParaContinuar();
                break;
            case 3:
                printf("Iniciando Apuestas Deportivas (no implementado aún)...\n");
                presioneTeclaParaContinuar();
                break;
            case 4:
                printf("Volviendo al menú principal...\n");
                presioneTeclaParaContinuar();
                break;
            default:
                printf("Opción inválida. Intente nuevamente.\n");
                presioneTeclaParaContinuar();
        }
    } while (opcion != 4);
}

void menu_bonificadores(Jugador *j) {
    int opcion = 0;
    do {
        limpiarPantalla();
        printf("===== Menú de Bonificadores =====\n");
        printf("1. Comprar bonificador\n");
        printf("2. Usar bonificador\n");
        printf("3. Volver al menú principal\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                printf("Comprar bonificador (no implementado aún)...\n");
                presioneTeclaParaContinuar();
                break;
            case 2:
                printf("Usar bonificador (no implementado aún)...\n");
                presioneTeclaParaContinuar();
                break;
            case 3:
                printf("Volviendo al menú principal...\n");
                presioneTeclaParaContinuar();
                break;
            default:
                printf("Opción inválida. Intente nuevamente.\n");
                presioneTeclaParaContinuar();
        }
    } while (opcion != 3);
}