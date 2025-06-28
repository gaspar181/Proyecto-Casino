# Proyecto-Casino

## Descripción

Este programa consiste en un videojuego que simula juegos clásicos de apuestas en formato de Casino Virtual. El juego consiste en iniciar una partida ingresando un nombre de usuario y eligiendo un monto de dinero ficticio para apostar. El usuario puede apostar su dinero en BlackJack, Ruleta o en un simulador de Apuesta Deportiva. Los juegos tienen multiplicadores establecidos que definen cuanto gana el jugador si su suerte le gana a la máquina. El multiplicador para el BlackJack es único, en cambio para los otros dos juegos va a depender del tipo de apuesta que se haga en la ruleta y del equipo que se elija en la apuesta deportiva.
Además de los juegos, el usuario tiene la opción de utilizar bonificadores, los cuales son aleatorios y afectan al jugador de manera positiva o negativa, pudiendo sumar o restar su saldo o modificar los multiplicadores de su próxima jugada.
Cuando el usuario termina los turnos requeridos para finalizar una partida, o se queda sin saldo, su partida queda registrada en un ranking, donde se almacenan los nombres de los jugadores y cuanto se multiplicó su dinero inicial.

## Cómo compilar y ejecutar

Este sistema ha sido desarrollado en lenguaje C y puede ejecutarse fácilmente utilizando **Visual Studio Code** junto con una extensión para C/C++, como **C/C++ Extension Pack** de Microsoft. Para comenzar a trabajar con el sistema en tu equipo local, sigue estos pasos:

### Requisitos previos:

- Tener instalado [Visual Studio Code](https://code.visualstudio.com/).
- Instalar la extensión **C/C++** (Microsoft).
- Tener instalado un compilador de C (como **gcc**). Si estás en Windows, se recomienda instalar [MinGW](https://www.mingw-w64.org/) o utilizar el entorno [WSL](https://learn.microsoft.com/en-us/windows/wsl/).
- Opcional: Para compilar más fácilmente puedes usar make. Para ello, asegúrate de tener instalado make
- Para instalar en Windows 
    Abre PowerShell como administrador y ejecuta:
    ```powershell
    choco install make
    ```
    También puedes instalar gcc con Chocolatey si lo necesitas:

    ```powershell
    choco install mingw
    ```
    en caso de complicaciones sugerimos seguir este tutorial: https://www.youtube.com/watch?v=5TavcolACQY
### Pasos para compilar y ejecutar:

1. **Abre Visual Studio Core** y selecciona **Clone Git Repository...**
2. Teniendo el proyecto abierto en **GitHub**:
    - Aprieta el botón verde **<>Code**
    - Copia la url del proyecto
    - Pega en VSCode donde dice **Clone from GitHub** (al seleccionar **Clone Git Repository...**)
3. **Selecciona carpeta de destino** para el repositorio abierto.
4. **Compila el código**
    - Abre la terminal integrada (`Terminal > Nueva terminal`).
    - En la terminal, compila el programa con el siguiente comando:
        
        ```powershell
        gcc main.c menu.c ruleta.c apuesta.c blackjack.c bonos.c utils.c jugador.c ranking.c  .\TDAS\list.c .\TDAS\map.c  -o casino.exe
        ```
    - Si utilizas make:
    - Abre la terminal integrada (`Terminal > Nueva terminal`).
    - En la terminal, compila el programa con el siguiente comando:
        
        ```powershell
        make
        ```
5. **Ejecuta el programa**
    - Una vez compilado, puedes ejecutar la aplicación con:
        
        ```
        ./casino.exe
        ```
6. **En caso de ocupar make**
    - Para borrar los archivos tenporales escribe en la terminal:
        
        ```powershell
        del *.o 
        ```
### A mejorar:

- Implementar nuevos juegos.
- Implementar nuevas bonificaciones.
- Trabajar más las apuestas deportivas, permitiendo opciones dentro de partidos simulados y apuestas combinadas (como en ruleta).

## Ejemplo de uso

**1) Menú Inicio**


```
=== Bienvenido al Casino ===
1. Iniciar Partida
2. Ver Ranking
3. Limpiar Ranking
4. Salir
Seleccione una opción: 
```

El jugador puede iniciar una partida nueva, o revisar el ranking de las partidas ya finalizadas.

**2) Iniciar juego**

El usuario debe ingresar su nombre y luego elegir con qué saldo ingresar al casino.

```
¡Bienvenido al Casino Virtual!
Por favor, ingresa tu nombre: Tito (ejemplo)

Tito, antes de comenzar, elige cuánto quieres apostar para esta noche:
1) Prefiero empezar tranquilo, con un presupuesto modesto ($500).
2) Me siento con suerte y quiero jugar con $1000.
3) Quiero una noche increíble y arriesgar $2000.
Selecciona tu opción (1, 2 o 3): 3

¡Una noche increíble! Juega con $2000 y disfruta.
```

El programa inicializó al nuevo jugador "Tito" y le puso $2000 en su saldo.

**2.1) Menú juego**

El programa comprueba si el saldo del jugador es mayor a 0 antes de darle la opción de seguir jugando.

```
=== Menú de Juegos ===
1. Blackjack
2. Ruleta
3. Apuestas Deportivas
4. Bonificadores y estado del jugador
0. Salir del casino
Seleccione una opción: 
```

El usuario selecciona la opcion para ir. 

**2.1 Blackjack**

El usuario debe ingresar el dinero a apostar y el juego comienza de manera automática repartiendo al jugador las cartas de su mazo.

```
=== BLACKJACK ===
Ingrese la cantidad a apostar: 300

Carta: 12 de pica
Puntaje actual: 10
┬┐Deseas otra carta? (s/n):
```

El jugador tiene la opción de seguir sacando cartas hasta que su puntaje sea menor o igual a 21. Si el jugador se pasa, pierde automáticamente. Si se planta antes de pasar 21 puntos con la suma de sus cartas, el dealer (programa) va a simular su turno, y va a sacar cartas hasta superar o igualar al jugador o hasta pasarse de 21. Si el dealer se pasa de 21 puntos o se planta con menos puntos que el jugador, este último gana, y el dinero que apostó se duplica y se suma a su saldo. Si el jugador empata con el dealer, se devuelve el dinero apostado, y si pierde también pierde la apuesta.

**2.2) Ruleta**

El programa indica el saldo disponible y las opciones para formar una apuesta, la cual puede combinarse de varias maneras mezclando los tres tipos de apuesta disponible: número, color y tercio.

```
=== Juego Ruleta ===

Saldo disponible: 1600.00

--- Nueva Apuesta ---
Tipo de apuesta:
1. N├║mero
2. Color
3. Tercio
0. Terminar
Opción: 1
Ingrese cantidad a apostar: 100
Ingrese n├║mero entre 0 y 36: 4
Total apostado: 100.00 / 1600.00
```
El jugador puede hacer una apuesta simple o combinada. Para las combinadas, para cada apuesta que sume se va a ingresar una cantidad de dinero. El programa escoje una casilla de manera aleatoria, la cual tiene un número y color y pertenece a uno de los 3 tercios disponibles (0-12, 13-24, 25-36). El pago se calcula según a cuantas características de la casilla acertó el jugador, y cuanto dinero puso para la apuesta ganadora.

**2.3) Apuesta deportiva**

El programa presentará al jugador la lista de equipos disponibles para apostar. La lista contiene varios equipos y un multiplicador asignado según por cuanto multiplica su victoria.

```
Equipos disponibles para apostar:
...
10. Deportes Iquique (x2.80)
11. Boca Juniors (x1.30)
12. River Plate (x1.40)
13. Independiente (x1.70)
...
Elige el nombre del equipo para apostar: Boca Juniors

Ingresa la cantidad que quieres apostar (saldo disponible: 1300.00): 300
┬íGanaste! Tu equipo Boca Juniors se lució.
Ganancia: 390.00
Saldo actual: 1390.00
```

El equipo seleccionado tendrá una probabilidad de ganar inversamente proporcional a su multiplicador asignado (menor multiplicador = mayor probabilidad de ganar). Si el equipo gana, el dinero apostado se multiplica por lo que le corresponda y se suma al saldo del jugador.

**2.4) Bonificadores y estado del jugador**

Se abre un nuevo menú para administrar los bonificadores y ver el estado del jugador.

```
=== Menú de Bonificadores ===
1. Mostrar último bonificador
2. Activar nuevo bonificador
3. Ver estado del jugador
0. Volver
Seleccione una opción:
```

**2.4.1) Bonificador**

La opción "Activar nuevo bonificador" crea una situación aleatoria que puede beneficiar o perjudicar al saldo del jugador o a su ganancia en su próximo juego, y la opción de "Mostrar último bonificador" explica la última bonificación activada.

```
=== BONIFICADOR ACTIVADO ===
Trago/Situación: Alguien te invitó un bajativo
Tipo: Bueno
Efecto: Bono de $300

>> Alguien te invitó un bajativo te afecta...
Recibes un bono de $300
```

**2.4.2) Ver estado del jugador**

El programa muestra el nombre, saldo, turnos jugados y multiplicador actual del jugador.

```
=== ESTADO DEL JUGADOR ===
Nombre: Tito
Saldo: $1400.00
Turnos jugados: 5
Multiplicador actual: 1.00
```

El "Multiplicador actual" del jugador puede cambiar si recibe una bonificación que afecta su multiplicador para el/los siguiente/s juego/s

**3) Ranking**

El jugador tiene la opción de ver el ranking del total de jugadores que han sido registrados tras sus apuestas.

```
=== RANKING DE JUGADORES ===
1. Tito - $1400.00
2. Ramon - $1358.00
```

Para ingresar al ranking hay que realizar un mínimo de apuestas tras iniciar una partida. Así podrás comparar tu saldo al salir con el del resto de jugadores.

## Consideraciones generales
- Ningún juego permite ingresar apuestas mayores al saldo del jugador.
- Para probar un juego sin apostar, se puede ingresar caracteres no numéricos al momento de elegir la apuesta, así se puede jugar sin modificar el saldo.
- El juego no permite terminar una partida si no se completó el mínimo de turnos, a menos que el jugador se quede sin saldo.
- Los bonificadores que afecten al multiplicador solo afectarán durante el siguiente turno, luego el multiplicador extra se va.
- Tanto las cartas del blackjack como las casillas de la ruleta salen de manera completamente aleatoria, en cambio en las apuestas deportivas el resultado será según el multiplicador asociado al equipo elegido.