#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ranking.h"

#define ARCHIVO_RANKING "ranking.txt" // Archivo donde se guarda el ranking

// Guarda el nombre y saldo del jugador actual al final del archivo de ranking
void guardarRanking(Jugador *j) {
    FILE *f = fopen(ARCHIVO_RANKING, "a");
    if (!f) {
        printf("Error al guardar el ranking.\n");
        return;
    }
    fprintf(f, "%s,%.2f\n", j->nombre, j->saldo); // Guarda en formato txt
    fclose(f);
}

// Función de comparación para ordenar de mayor a menor por saldo
int comparar(const void *a, const void *b) {
    RegistroRanking *ra = (RegistroRanking *)a;
    RegistroRanking *rb = (RegistroRanking *)b;
    return (rb->saldo - ra->saldo); // Descendente
}

// Lee los datos del archivo, los ordena y muestra el top 10
void mostrarRanking() {
    FILE *f = fopen(ARCHIVO_RANKING, "r");
    if (!f) {
        printf("No hay ranking disponible aún.\n");
        return;
    }

    RegistroRanking registros[100];
    int count = 0;

    // Lee cada línea del archivo y la guarda en el arreglo
    while (fscanf(f, "%[^,],%f\n", registros[count].nombre, &registros[count].saldo) == 2) {
        count++;
        if (count >= 100) break; // Límite de 100 registros
    }
    fclose(f);

    qsort(registros, count, sizeof(RegistroRanking), comparar); // Ordena por saldo

    printf("=== RANKING DE JUGADORES ===\n");
    for (int i = 0; i < count && i < 10; i++) { // Muestra solo el top 10
        printf("%d. %s - $%.2f\n", i + 1, registros[i].nombre, registros[i].saldo);
    }
}

// Vacía el contenido del archivo de ranking
void limpiarRanking() {
    FILE *f = fopen(ARCHIVO_RANKING, "w");
    if (!f) {
        printf("Error al intentar limpiar el ranking.\n");
        return;
    }
    fclose(f);
    printf("Ranking limpiado exitosamente.\n");
}