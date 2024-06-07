#include "PokeBall.h"
#include <cstdlib> // Para la generación de números aleatorios
#include <ctime>   // Para inicializar la semilla de generación aleatoria

PokeBall::PokeBall() {
    // Inicializar la semilla de números aleatorios
    srand(time(0));
}

bool PokeBall::RecogerPokeball(int limiteMapa_x, int limiteMapa_y, char** casillas) {
    // Generar una nueva posición aleatoria para una PokeBall
    int nuevaPokeBallX, nuevaPokeBallY;
    do {
        nuevaPokeBallX = rand() % (limiteMapa_x - 1) + 1;
        nuevaPokeBallY = rand() % (limiteMapa_y - 1) + 1;
    } while (casillas[nuevaPokeBallY][nuevaPokeBallX] != ' ');

    casillas[nuevaPokeBallY][nuevaPokeBallX] = 'O'; // Colocar la nueva PokeBall
    return true;
}
