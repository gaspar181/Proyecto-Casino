// utils.c
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif

void limpiarPantalla() {
    system(CLEAR_COMMAND);
}

void presioneTeclaParaContinuar() {
    printf("\nPresione ENTER para continuar...");
    while (getchar() != '\n'); // Espera limpiar buffer
    getchar(); // Espera ENTER real
}

void saltarLineas(int n) {
    for (int i = 0; i < n; i++) {
        printf("\n");
    }
}

void lineaSeparadora() {
    printf("\n----------------------------------------\n");
}