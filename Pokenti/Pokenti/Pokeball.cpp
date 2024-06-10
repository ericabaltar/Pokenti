#include "Pokeball.h"


PokeBall::PokeBall() {

    srand(time(0));
}

void PokeBall::GestionarPokeBalls(Mapa& mapa, Settings& settings)
{
    int PokeBallsPresentesZona1 = 0;
    for (int i = 0; i < settings.FILAS / 2; ++i) {
        for (int j = 0; j < settings.COLUMNAS / 2; ++j) {
            if (mapa.casillas[i][j] == Casilla::POKEBALL) {
                PokeBallsPresentesZona1++;
            }
        }
    }

    if (PokeBallsPresentesZona1 < 1) {
        int nuevaPokeBallX, nuevaPokeBallY;
        do {
            nuevaPokeBallX = rand() % (settings.COLUMNAS / 2 - 1) + 1;
            nuevaPokeBallY = rand() % (settings.FILAS / 2 - 1) + 1;
        } while (mapa.casillas[nuevaPokeBallY][nuevaPokeBallX] != Casilla::VACIO);

        mapa.casillas[nuevaPokeBallY][nuevaPokeBallX] = Casilla::POKEBALL;
    }

    int PokeBallsPresentesZona2 = 0;
    for (int i = 0; i < settings.FILAS / 2; ++i) {
        for (int j = settings.COLUMNAS / 2; j < settings.COLUMNAS; ++j) {
            if (mapa.casillas[i][j] == Casilla::POKEBALL) {
                PokeBallsPresentesZona2++;
            }
        }
    }

    if (PokeBallsPresentesZona2 < 1) {
        int nuevaPokeBallX, nuevaPokeBallY;
        do {
            nuevaPokeBallX = rand() % (settings.COLUMNAS / 2 - 1) + settings.COLUMNAS / 2 - 1;
            nuevaPokeBallY = rand() % (settings.FILAS / 2 - 1) + 1;
        } while (mapa.casillas[nuevaPokeBallY][nuevaPokeBallX] != Casilla::VACIO);

        mapa.casillas[nuevaPokeBallY][nuevaPokeBallX] = Casilla::POKEBALL;
    }

}

bool PokeBall::VerificarPokeball(int jugadorX, int jugadorY, Mapa& mapa, Position ashPos, Ash& ash, Settings& settings) {
    // Coordenadas adyacentes a la posici�n de Ash
    int adyacentes[4][2] = {
        {jugadorX, jugadorY - 1}, // Arriba
        {jugadorX, jugadorY + 1}, // Abajo
        {jugadorX - 1, jugadorY}, // Izquierda
        {jugadorX + 1, jugadorY}  // Derecha
    };

    // Guardar la posici�n de la POKEBALL adyacente
    int pokeballX = -1;
    int pokeballY = -1;

    // Verificar cada posici�n adyacente
    for (int i = 0; i < 4; ++i) {
        int x = adyacentes[i][0];
        int y = adyacentes[i][1];

        // Asegurarse de que la coordenada est� dentro de los l�mites del mapa
        if (x >= 0 && x < settings.COLUMNAS && y >= 0 && y < settings.FILAS) {
            if (mapa.casillas[y][x] == Casilla::POKEBALL) {
                pokeballX = x;
                pokeballY = y;
                break; // Encontramos una POKEBALL, salimos del bucle
            }
        }
    }

    // Si encontramos una POKEBALL adyacente
    if (pokeballX != -1 && pokeballY != -1) {
        // Verificar si la posici�n de Ash es igual a la posici�n de la POKEBALL guardada
        if (jugadorX == pokeballX && jugadorY == pokeballY) {
            ash.PokeBall += 1;
            // Eliminar la Pok�Ball del mapa
            mapa.casillas[pokeballY][pokeballX] = Casilla::VACIO;
            return true; // Se recogi� una Pok�Ball
        }
    }

    return false; // No se recogi� una Pok�Ball
}


