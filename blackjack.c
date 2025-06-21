#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "blackjack.h"
#include "utils.h" 

// Función de comparación para mapa ordenado
int ordenar(void *a, void *b) {
    int int_a = *(int *)a;
    int int_b = *(int *)b;
    return int_a < int_b;
}

// Crear las 156 cartas (3 mazos) barajadas en mapa ordenado
Map *barajarCartas() {
    Map *mapa = sorted_map_create(ordenar);
    srand(time(NULL)); // para mezcla aleatoria

    char *pintas[] = {"pica", "corazón", "diamante", "trébol"};

    for (int m = 0; m < 3; m++) { // 3 mazos
        for (int p = 0; p < 4; p++) {
            for (int n = 1; n <= 13; n++) {
                Carta *c = malloc(sizeof(Carta));
                c->numero = n;
                strcpy(c->pinta, pintas[p]);

                int *clave = malloc(sizeof(int));
                do {
                    *clave = rand() % 10000 + 1;
                } while (map_search(mapa, clave) != NULL);

                map_insert(mapa, clave, c);
            }
        }
    }
    return mapa;
}

// Genera el mazo en pila desde el mapa ordenado
Stack *generarMazo() {
    Stack *mazo = stack_create(NULL);
    Map *baraja = barajarCartas();

    MapPair *par = map_first(baraja);
    while (par != NULL) {
        stack_push(mazo, par->value); // solo cartas
        par = map_next(baraja);
    }

    map_clean(baraja);
    return mazo;
}

// Devuelve el valor numérico de una carta para el juego
int obtenerValorCarta(Carta *c) {
    if (c->numero >= 10) return 10;
    return c->numero;
}

// Jugar una partida simple de blackjack
void jugarBlackjack(Jugador *j) {
    if (j->saldo <= 0) {
        printf("Oye, no tienes ni un peso para apostar en Blackjack...\n");
        printf("Vuelve cuando traigas plata, compadre.\n");
        presioneTeclaParaContinuar();
        return;
    }

    printf("=== BLACKJACK ===\n");

    double apuesta;
    printf("Ingrese la cantidad a apostar: ");
    scanf("%lf", &apuesta);

    if (apuesta <= 0 || apuesta > j->saldo) {
        printf("Apuesta inválida. Tu saldo es %.2f\n", j->saldo);
        presioneTeclaParaContinuar();
        return;
    }

    Stack *mazo = generarMazo();
    int puntaje = 0, ases = 0;
    char opcion;

    // Turno del jugador
    while (1) {
        Carta *carta = stack_pop(mazo);
        if (!carta) {
            printf("Se acabaron las cartas. Se regenerará el mazo.\n");
            mazo = generarMazo();
            carta = stack_pop(mazo);
        }

        printf("Carta: %d de %s\n", carta->numero, carta->pinta);
        int valor = obtenerValorCarta(carta);
        if (carta->numero == 1) ases++;
        puntaje += valor;

        while (puntaje > 21 && ases > 0) {
            puntaje -= 10;
            ases--;
        }

        printf("Puntaje actual: %d\n", puntaje);

        if (puntaje > 21) {
            printf("Te pasaste. Pierdes esta ronda.\n");
            double perdida = apuesta * j->multiplicador_actual;
            j->saldo -= perdida;
            printf("Perdiste %.2f. Saldo actual: %.2f\n", perdida, j->saldo);
            j->turnos_jugados++;
            presioneTeclaParaContinuar();
            return;
        }

        printf("¿Deseas otra carta? (s/n): ");
        scanf(" %c", &opcion);
        if (opcion == 'n' || opcion == 'N') break;
    }

    // Simular turno del dealer
    int dealer = 0, ases_d = 0;
    printf("\nMi turno waton, se te viene pesado\n");
    while (dealer < 17) {
        Carta *carta = stack_pop(mazo);
        if (!carta) {
            mazo = generarMazo();
            carta = stack_pop(mazo);
        }

        printf("Ahora yo saco: %d de %s\n", carta->numero, carta->pinta);
        int val = obtenerValorCarta(carta);
        if (carta->numero == 1) ases_d++;
        dealer += val;

        while (dealer > 21 && ases_d > 0) {
            dealer -= 10;
            ases_d--;
        }
    }

    printf("Puntaje dealer: %d\n", dealer);
    printf("Tu puntaje final: %d\n", puntaje);

    // Resultado
    if ((dealer > 21) || (puntaje > dealer)) {
        double ganancia = apuesta * j->multiplicador_actual;
        j->saldo += ganancia;
        printf("¡Ganaste! +%.2f | Saldo actual: %.2f\n", ganancia, j->saldo);
    } else if (puntaje == dealer) {
        printf("Empate. Se devuelve tu apuesta.\n");
        // saldo queda igual
    } else {
        double perdida = apuesta * j->multiplicador_actual;
        j->saldo -= perdida;
        printf("Perdiste %.2f. Saldo actual: %.2f\n", perdida, j->saldo);
    }

    j->turnos_jugados++;
    presioneTeclaParaContinuar();
}