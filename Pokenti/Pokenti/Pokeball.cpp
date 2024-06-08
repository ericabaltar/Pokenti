#include "Pokeball.h"


PokeBall::PokeBall() {
    // Inicializar la semilla de números aleatorios
    srand(time(0));
}
void PokeBall::GestionarPokeBalls(Mapa& mapa)
{
    // Contar la cantidad de pokémons presentes en el mapa
    int PokeBallsPresentesZona1 = 0;
    for (int i = 0; i < mapa.FILAS / 2; ++i) {
        for (int j = 0; j < mapa.COLUMNAS / 2; ++j) {
            if (mapa.casillas[i][j] == mapa.POKEBALL) {
                PokeBallsPresentesZona1++;
            }
        }
    }
    // Si hay menos de 1 PokeBall, generar y colocar una nueva
    if (PokeBallsPresentesZona1 < 1) {
        int nuevaPokeBallX, nuevaPokeBallY;
        do {
            nuevaPokeBallX = rand() % (mapa.COLUMNAS / 2 - 1) + 1;
            nuevaPokeBallY = rand() % (mapa.FILAS / 2 - 1) + 1;
        } while (mapa.casillas[nuevaPokeBallY][nuevaPokeBallX] != mapa.VACIO);

        mapa.casillas[nuevaPokeBallY][nuevaPokeBallX] = mapa.POKEBALL; // Colocar la nueva PokeBall
    }

    int PokeBallsPresentesZona2 = 0;
    for (int i = 0; i < mapa.FILAS / 2; ++i) {
        for (int j = mapa.COLUMNAS / 2; j < mapa.COLUMNAS; ++j) {
            if (mapa.casillas[i][j] == mapa.POKEBALL) {
                PokeBallsPresentesZona2++;
            }
        }
    }
    // Si hay menos de 18 pokémons, generar y colocar uno nuevo
    if (PokeBallsPresentesZona2 < 1) {
        int nuevaPokeBallX, nuevaPokeBallY;
        do {
            nuevaPokeBallX = rand() % (mapa.COLUMNAS / 2 - 1) + mapa.COLUMNAS / 2 - 1;
            nuevaPokeBallY = rand() % (mapa.FILAS / 2 - 1) + 1;
        } while (mapa.casillas[nuevaPokeBallY][nuevaPokeBallX] != mapa.VACIO);

        mapa.casillas[nuevaPokeBallY][nuevaPokeBallX] = mapa.POKEBALL; // Colocar el nuevo Pokémon
    }

}
bool PokeBall::VerificarPokeball(int jugadorX, int jugadorY, Mapa& mapa, Position ashPos, Ash& ash) {
    // Coordenadas adyacentes a la posición de Ash
    int adyacentes[4][2] = {
        {jugadorX, jugadorY - 1}, // Arriba
        {jugadorX, jugadorY + 1}, // Abajo
        {jugadorX - 1, jugadorY}, // Izquierda
        {jugadorX + 1, jugadorY}  // Derecha
    };

    // Guardar la posición de la POKEBALL adyacente
    int pokeballX = -1;
    int pokeballY = -1;

    // Verificar cada posición adyacente
    for (int i = 0; i < 4; ++i) {
        int x = adyacentes[i][0];
        int y = adyacentes[i][1];

        // Asegurarse de que la coordenada está dentro de los límites del mapa
        if (x >= 0 && x < mapa.COLUMNAS && y >= 0 && y < mapa.FILAS) {
            if (mapa.casillas[y][x] == mapa.POKEBALL) {
                pokeballX = x;
                pokeballY = y;
                break; // Encontramos una POKEBALL, salimos del bucle
            }
        }
    }

    // Si encontramos una POKEBALL adyacente
    if (pokeballX != -1 && pokeballY != -1) {
        // Verificar si la posición de Ash es igual a la posición de la POKEBALL guardada
        if (jugadorX == pokeballX && jugadorY == pokeballY) {
            ash.PokeBall += 1;
            // Eliminar la PokéBall del mapa
            mapa.casillas[pokeballY][pokeballX] = mapa.VACIO;
            return true; // Se recogió una PokéBall
        }
    }

    return false; // No se recogió una PokéBall
}


