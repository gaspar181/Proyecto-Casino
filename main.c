#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "menu.h"
#include "jugador.h"
#include "bonos.h"
#include "utils.h"

int main() {
    srand(time(NULL)); // Inicializa números aleatorios

    limpiarPantalla();

    Jugador jugador;
    crearJugador(&jugador); 

    inicializarBonificadores();

    menu_inicio(&jugador); // <-- Ahora pasa el puntero al jugador

    limpiarPantalla();
    printf("Gracias por jugar, %s. ¡Vuelve pronto al casino!\n", jugador.nombre);

    return 0;
}