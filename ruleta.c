#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ruleta.h"
#include "jugador.h"  

void inicializarRuleta(CasillaRuleta ruleta[]) {
    for (int i = 0; i < TOTAL_CASILLAS; i++) {
        ruleta[i].numero = i;
        if (i == 0) {
            ruleta[i].color = VERDE;
        } else if ((i >= 1 && i <= 10) || (i >= 19 && i <= 28)) {
            ruleta[i].color = (i % 2 == 0) ? NEGRO : ROJO;
        } else {
            ruleta[i].color = (i % 2 == 0) ? ROJO : NEGRO;
        }
    }
}

int girarRuleta() {
    srand((unsigned)time(NULL)); // idealmente llamar esto solo 1 vez al inicio del main
    return rand() % TOTAL_CASILLAS;
}

double calcularPago(Apuesta* apuesta, CasillaRuleta ruleta[], int resultado, Jugador* j) {
    double multiplicador = j->multiplicador_actual;
    
    switch (apuesta->tipo) {
        case APUESTA_NUMERO:
            if (apuesta->numero == resultado) {
                return apuesta->cantidad * 36 * multiplicador;
            }
            break;

        case APUESTA_COLOR:
            if (ruleta[resultado].color == apuesta->color) {
                return apuesta->cantidad * 2 * multiplicador;
            }
            break;

        case APUESTA_TERCIO:
            if (resultado >= apuesta->tercio_inicio && resultado <= apuesta->tercio_fin) {
                return apuesta->cantidad * 3 * multiplicador;
            }
            break;

        default:
            break;
    }

    return 0.0;
}
