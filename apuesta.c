#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "TDAS/map.h"
#include "jugador.h"
#include "utils.h" 

// Convierte una cadena a minúsculas (para búsquedas insensibles a mayúsculas)
void to_lowercase(char* str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + ('a' - 'A');
        }
    }
}

// Compara strings sin distinguir mayúsculas
int cmp_strings(void *a, void *b) {
    return strcasecmp((char *)a, (char *)b) == 0;
}

// Inserta todos los equipos y sus multiplicadores al mapa con claves en minúsculas
void inicializarEquipos(Map* mapa) {
    struct {
        const char* nombre;
        float multiplicador;
    } equipos[] = {
        {"Colo Colo", 1.4f}, {"Universidad de Chile", 1.5f}, {"Universidad Católica", 1.3f},
        {"Audax Italiano", 2.3f}, {"Everton", 2.5f}, {"Union Española", 2.0f},
        {"O'Higgins", 2.1f}, {"Cobresal", 2.2f}, {"Huachipato", 2.4f}, {"Deportes Iquique", 2.8f},
        {"Boca Juniors", 1.3f}, {"River Plate", 1.4f}, {"Independiente", 1.7f},
        {"Racing Club", 1.8f}, {"San Lorenzo", 2.0f}, {"Vélez Sarsfield", 2.2f},
        {"Estudiantes", 2.3f}, {"Lanús", 2.5f}, {"Newell's Old Boys", 2.7f}, {"Rosario Central", 2.8f},
        {"Real Madrid", 1.2f}, {"Barcelona", 1.2f}, {"Manchester United", 1.5f},
        {"Bayern Munich", 1.3f}, {"Juventus", 1.6f}, {"Liverpool", 1.4f},
        {"Paris Saint-Germain", 1.7f}, {"Chelsea", 1.6f}, {"Arsenal", 1.8f}, {"Borussia Dortmund", 1.9f},
        {"Flamengo", 2.0f}, {"Palmeiras", 1.9f}, {"Atlético Mineiro", 2.1f},
        {"Santos", 2.3f}, {"Gremio", 2.2f}, {"Universitario", 2.5f},
        {"Tiburones FC", 3.0f}, {"Cóndores SC", 3.2f}, {"Alianza Lima", 2.9f},
        {"Jaguares FC", 3.1f}, {"Cóndores Rojos", 3.3f},
        {"Santiago Wanderers", 3.0f}, {"Águilas Doradas", 2.8f}, {"Brujas de Salamanca", 3.2f},
        {"Gamba Osaka", 3.1f}, {"Fénix FC", 3.4f},
        {"Estrellas del Norte", 3.5f}, {"Nottingham Forest", 3.3f}, {"CSD Albion", 3.6f},
        {"Gladiadores FC", 3.7f}, {"Halcones Dorados", 3.8f},
        {"Deportes La Serena", 2.6f}, {"Coquimbo Unido", 2.7f}, {"Magallanes", 2.9f},
        {"Godoy Cruz", 2.6f}, {"Argentinos Juniors", 2.7f},
        {"Inter Milan", 1.6f}, {"AC Milan", 1.7f}, {"Napoli", 1.8f},
        {"Valencia", 1.9f}, {"Sevilla", 2.0f},
        {"Tormenta FC", 3.1f}, {"PUCV FC", 3.2f}, {"Glorias Navales", 3.3f},
        {"Centinelas FC", 3.4f}, {"Vikingos FC", 3.5f},
        {"Águilas Reales", 3.6f}, {"Bolivar", 3.7f}, {"Mamelodi Sundowns", 3.8f},
        {"Osos Negros", 3.9f}, {"Raptors FC", 4.0f}, {"Búfalos FC", 4.1f}, {"Fénix Negro", 4.2f},
        {"Deportes Limache", 4.3f}, {"Botafogo Gómez Carreño", 4.4f}, {"Panteras FC", 4.5f},
        {"Caracas", 4.6f}, {"Lota Schwager", 4.7f}, {"Chile", 4.8f},
        {"Santiago City", 4.9f}, {"Concón National", 5.0f},
        {"Wrexham United", 3.9f}, {"Vodka Juniors", 3.8f}, {"Malaga", 3.7f},
        {"Gladiadores Dorados", 3.6f}, {"Espartanos FC", 3.5f}, {"AC Malajax", 3.4f},
        {"Tigres Negros", 3.3f}, {"Rojos FC", 3.2f}, {"Azules FC", 3.1f},
        {"Barras Bravas", 2.9f}, {"Leones Negros", 2.8f}, {"Estrella de Plata", 2.7f},
        {"ICD FC", 2.6f}, {"Fénix Dorado", 2.5f}
    };

    int totalEquipos = sizeof(equipos) / sizeof(equipos[0]);

    for (int i = 0; i < totalEquipos; i++) { // Copia nombre dinámicamente
        char* nombreEquipo = strdup(equipos[i].nombre);
        to_lowercase(nombreEquipo);
        float* multPtr = malloc(sizeof(float));
        *multPtr = equipos[i].multiplicador;
        map_insert(mapa, nombreEquipo, multPtr);
    }
}



void mostrarEquipos(Map* mapa) { // Muestra lista numerada de equipos disponibles con sus multiplicadores
    printf("Equipos disponibles para apostar:\n");
    MapPair* par = map_first(mapa);
    int idx = 1;
    while (par != NULL) {
        printf("%d. %s (x%.2f)\n", idx, (char*)par->key, *(float*)par->value);
        par = map_next(mapa);
        idx++;
    }
}

void jugarApuestasDeportivas(Jugador* j) {
    if (j->saldo <= 0) {
        printf("No tienes plata para apostar, vuelve cuando tengas lucas.\n");
        presioneTeclaParaContinuar();
        return;
    }

    Map* mapaEquipos = map_create(cmp_strings); // Crea mapa
    inicializarEquipos(mapaEquipos); // Carga equipos

    mostrarEquipos(mapaEquipos);

    char opcionEquipo[50];
    printf("Elige el nombre del equipo para apostar: ");
    fgets(opcionEquipo, sizeof(opcionEquipo), stdin); // Lee nombre del equipo con espacios
    opcionEquipo[strcspn(opcionEquipo, "\n")] = 0;
    to_lowercase(opcionEquipo);

    MapPair* pair = map_search(mapaEquipos, opcionEquipo); // Busca equipo elegido
    if (pair == NULL) {
        printf("Equipo no encontrado.\n");
        map_clean(mapaEquipos);
        free(mapaEquipos);
        presioneTeclaParaContinuar();
        return;
    }

    float* multiplicador = (float*)pair->value;

    double apuesta;
    printf("Ingresa la cantidad que quieres apostar (saldo disponible: %.2f): ", j->saldo);
    scanf("%lf", &apuesta);
    getchar();

    if (apuesta <= 0 || apuesta > j->saldo) {
        printf("Monto inválido o excede saldo.\n");
        map_clean(mapaEquipos);
        free(mapaEquipos);
        presioneTeclaParaContinuar();
        return;
    }

    float prob_ganar = 1.0f / (*multiplicador); // multiplicador como probabilidad
    float r = (float)rand() / RAND_MAX; // Número aleatorio para ver si gana 

    if (r <= prob_ganar) {
        double ganancia = apuesta * (*multiplicador); 
        j->saldo += ganancia - apuesta; // Recupera apuesta + ganancia neta
        printf("¡Ganaste! Tu equipo %s se lució.\nGanancia: %.2f\nSaldo actual: %.2f\n", opcionEquipo, ganancia, j->saldo);
    } else {
        j->saldo -= apuesta;
        printf("Perdiste la apuesta. Tu equipo %s no pudo.\nSaldo restante: %.2f\n", opcionEquipo, j->saldo); // Pierde el monto apostado
    }

    j->turnos_jugados++;
    j->multiplicador_actual = 1;
    // Libera memoria de claves y valores del mapa
    MapPair* p = map_first(mapaEquipos);
    while (p != NULL) {
        free(p->key);
        free(p->value);
        p = map_next(mapaEquipos);
    }
    map_clean(mapaEquipos);
    free(mapaEquipos);

    presioneTeclaParaContinuar();
}