#include "Pokeball.h"


PokeBall::PokeBall() {
    iteracion = 0;
    iteracionZona2 = 0;
    srand(time(0));
}

void PokeBall::GestionarPokeBalls(int jugadorX, int jugadorY, Mapa& mapa, Ash& ash, Settings& settings)
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
        int nuevaPokeBallX;
        int nuevaPokeBallY;
        do {
            nuevaPokeBallX = rand() % (settings.COLUMNAS / 2 - 1) + 1;
            nuevaPokeBallY = rand() % (settings.FILAS / 2 - 1) + 1;
            PokeBall::iteracion++;
        } while (mapa.casillas[nuevaPokeBallY][nuevaPokeBallX] != Casilla::VACIO);

        mapa.casillas[nuevaPokeBallY][nuevaPokeBallX] = Casilla::POKEBALL;

        if (PokeBall::iteracion >= 2)
            ash.PokeBall += 1;
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
        int nuevaPokeBallX;
        int nuevaPokeBallY;
        do {
            nuevaPokeBallX = rand() % (settings.COLUMNAS / 2 - 1) + settings.COLUMNAS / 2 - 1;
            nuevaPokeBallY = rand() % (settings.FILAS / 2 - 1) + 1;
            PokeBall::iteracionZona2++;
        } while (mapa.casillas[nuevaPokeBallY][nuevaPokeBallX] != Casilla::VACIO);

        mapa.casillas[nuevaPokeBallY][nuevaPokeBallX] = Casilla::POKEBALL;

        if (PokeBall::iteracionZona2 >= 2)
            ash.PokeBall += 1;
    }

}


