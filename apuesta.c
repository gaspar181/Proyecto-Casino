#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "apuestas.h"

Map* crearEquipos() {
    Map* equipos = createMap(is_equal_string);
    srand(time(NULL));

    char* nombres[] = {"ColoColo", "UdeChile", "UCatolica", "Palestino", "Cobresal","Huachipato", "UnionEspanola", "Audax", "Coquimbo", "Everton"};
    int cantidad = sizeof(nombres) / sizeof(nombres[0]);

    for (int i = 0; i < cantidad; i++) {
        float* multiplicador = malloc(sizeof(float));
        *multiplicador = 1.5 + (rand() % 200) / 100.0f; // entre 1.5 y 3.5
        insertMap(equipos, nombres[i], multiplicador);
    }
    return equipos;
}

void mostrarEquipos(Map* equipos) {
    printf("\n--- Equipos Disponibles ---\n");
    Pair* actual = firstMap(equipos);
    while (actual != NULL) {
        printf("%s - Multiplicador: x%.2f\n", (char*)actual->key, *(float*)actual->value);
        actual = nextMap(equipos);
    }
}

void jugarApuestaDeportiva(Jugador* jugador, Map* equipos) {
    if (jugador->dinero_actual <= 0) {
        printf("No tienes dinero para apostar.\n");
        return;
    }

    mostrarEquipos(equipos);
    
    char equipo[50];
    printf("\nIngresa el nombre del equipo por el que apuestas: ");
    scanf("%s", equipo);

    Pair* par = searchMap(equipos, equipo);
    if (par == NULL) {
        printf("Equipo no encontrado.\n");
        return;
    }

    float* mult = (float*)par->value;

    int apuesta;
    printf("Ingresa la cantidad a apostar: ");
    scanf("%d", &apuesta);

    if (apuesta > jugador->dinero_actual) {
        printf("No tienes suficiente dinero.\n");
        return;
    }

     // Probabilidad de ganar basada en el inverso del multiplicador
    float probabilidad_ganar = 1.0f / (*mult); 
    float chance = (float)rand() / RAND_MAX;
    int gana = (chance < probabilidad_ganar);

    if (gana) {
        float ganancia = apuesta * (*mult);

        // Aplicar bonificador si existe
        if (jugador->bono_activo != NULL && jugador->bono_activo->tipo == 1) {
            ganancia *= jugador->bono_activo->efecto;
            printf("\nBonificador aplicado!\n");
        }

        jugador->dinero_actual += ganancia;
        printf("\nGanaste! Tu dinero ahora es: %.2f\n", jugador->dinero_actual);
    } else {
        jugador->dinero_actual -= apuesta;
        printf("\nPerdiste! Tu dinero ahora es: %.2f\n", jugador->dinero_actual);
    }

    jugador->turnos++;
}
