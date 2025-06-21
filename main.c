#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "menu.h"
#include "jugador.h"
#include "bonos.h"

int main() {
    srand(time(NULL)); // Inicializa números aleatorios

    limpiarPantalla();

    // Crear jugador
    Jugador jugador;
    crearJugador(&jugador); // Esta función debe pedir nombre y saldo inicial

    // Inicializar bonificadores (una vez al inicio)
    inicializarBonificadores();

    // Mostrar menú de inicio (jugar, ranking, salir)
    menu_inicio(); 
    
    // Ingresar al menú principal del juego
    menu_principal(&jugador);

    limpiarPantalla();
    printf("Gracias por jugar, %s. ¡Vuelve pronto al casino!\n", jugador.nombre);
    
    return 0;
}
