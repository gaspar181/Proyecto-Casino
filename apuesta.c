#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "TDAS/map.h"
#include "apuesta.h"

// Función de comparación de claves para el mapa
int is_equal(void* key1, void* key2) {
    return strcmp((char*)key1, (char*)key2) == 0;
}

Map* crearEquipos() {
    Map* equipos = map_create(is_equal);
    srand(time(NULL));  // Idealmente se inicializa solo una vez en el main

    char* nombres[] = {"ColoColo", "UdeChile", "UCatolica", "Palestino", "Cobresal", "Huachipato", "UnionEspanola", "Audax", "Coquimbo", "Everton", "Wanderers"};
    int cantidad = sizeof(nombres) / sizeof(nombres[0]);

    for (int i = 0; i < cantidad; i++) {
        float* multiplicador = malloc(sizeof(float));
        *multiplicador = 1.5 + (rand() % 200) / 100.0f; // entre 1.5 y 3.5
        map_insert(equipos, nombres[i], multiplicador);
    }
    return equipos;
}

void mostrarEquipos(Map* equipos) {
    printf("\n--- Equipos Disponibles ---\n");
    MapPair* actual = map_first(equipos);
    while (actual != NULL) {
        printf("%s - Multiplicador: x%.2f\n", (char*)actual->key, *(float*)actual->value);
        actual = map_next(equipos);
    }
}

void jugarApuestaDeportiva(Jugador* jugador, Map* equipos) {
    if (jugador->saldo <= 0) {
        printf("No tienes dinero para apostar.\n");
        return;
    }

    mostrarEquipos(equipos);
    
    char equipo[50];
    printf("\nIngresa el nombre del equipo por el que apuestas: ");
    scanf("%s", equipo);

    MapPair* par = map_search(equipos, equipo);
    if (par == NULL) {
        printf("Equipo no encontrado.\n");
        return;
    }

    float* mult = (float*)par->value;

    int apuesta;
    printf("Ingresa la cantidad a apostar: ");
    scanf("%d", &apuesta);

    if (apuesta > jugador->saldo || apuesta <= 0) {
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
        if (jugador->multiplicador_actual != NULL && jugador->multiplicador_actual->tipo == 1) {
            ganancia *= jugador->multiplicador_actual->efecto;
            printf("\nBonificador aplicado!\n");
        }

        jugador->saldo += ganancia;
        printf("\nGanaste! Tu dinero ahora es: %.2f\n", jugador->saldo);
    } else {
        jugador->saldo -= apuesta;
        printf("\nPerdiste! Tu dinero ahora es: %.2f\n", jugador->saldo);
    }

    jugador->turnos_jugados++;
}
