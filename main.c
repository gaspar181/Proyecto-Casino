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

    menu_inicio(); 

    limpiarPantalla();

    return 0;
}