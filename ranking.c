#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ranking.h"

#define ARCHIVO_RANKING "ranking.txt"

void guardarRanking(Jugador *j) {
    FILE *f = fopen(ARCHIVO_RANKING, "a");
    if (!f) {
        printf("Error al guardar el ranking.\n");
        return;
    }
    fprintf(f, "%s,%.2f\n", j->nombre, j->saldo);
    fclose(f);
}

typedef struct {
    char nombre[100];
    float saldo;
} RegistroRanking;

int comparar(const void *a, const void *b) {
    RegistroRanking *ra = (RegistroRanking *)a;
    RegistroRanking *rb = (RegistroRanking *)b;
    return (rb->saldo - ra->saldo);
}

void mostrarRanking() {
    FILE *f = fopen(ARCHIVO_RANKING, "r");
    if (!f) {
        printf("No hay ranking disponible aún.\n");
        return;
    }

    RegistroRanking registros[100];
    int count = 0;

    while (fscanf(f, "%[^,],%f\n", registros[count].nombre, &registros[count].saldo) == 2) {
        count++;
        if (count >= 100) break;
    }
    fclose(f);

    qsort(registros, count, sizeof(RegistroRanking), comparar);

    printf("=== RANKING DE JUGADORES ===\n");
    for (int i = 0; i < count && i < 10; i++) {
        printf("%d. %s - $%.2f\n", i + 1, registros[i].nombre, registros[i].saldo);
    }
}

void limpiarRanking() {
    FILE *f = fopen(ARCHIVO_RANKING, "w");
    if (!f) {
        printf("Error al intentar limpiar el ranking.\n");
        return;
    }
    fclose(f);
    printf("Ranking limpiado exitosamente.\n");
}