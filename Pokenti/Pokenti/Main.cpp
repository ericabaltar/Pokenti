#include "mapa.h"

int main() {
    
    const int FILAS = 10;
    const int COLUMNAS = 20;
    char vacio = ' ';
    char pared = 'X';

    
    char** mapa = new char*[FILAS];
    for (int i = 0; i < FILAS; ++i) {
        mapa[i] = new char[COLUMNAS];
        
        for (int j = 0; j < COLUMNAS; ++j) {
            mapa[i][j] = vacio;
        }
    }

    
    int mitadFilas = FILAS / 2;
    int mitadColumnas = COLUMNAS / 2;

    // Cuadrante 1: Pueblo Paleta
    for (int i = 0; i < mitadFilas; ++i) {
        for (int j = 0; j < mitadColumnas; ++j) {
            mapa[i][j] = vacio;
        }
    }

    // Cuadrante 2: Bosque
    for (int i = 0; i < mitadFilas; ++i) {
        for (int j = mitadColumnas; j < COLUMNAS; ++j) {
            mapa[i][j] = vacio;
        }
    }

    // Cuadrante 3: Cueva Celeste
    for (int i = mitadFilas; i < FILAS; ++i) {
        for (int j = 0; j < mitadColumnas; ++j) {
            mapa[i][j] = vacio;
        }
    }

    // Cuadrante 4: Liga PokENTI
    for (int i = mitadFilas; i < FILAS; ++i) {
        for (int j = mitadColumnas; j < COLUMNAS; ++j) {
            mapa[i][j] = vacio;
        }
    }

    // Imprimir el mapa
    imprimirMapa(mapa, FILAS, COLUMNAS);

    // Liberar la memoria asignada para el mapa
    for (int i = 0; i < FILAS; ++i) {
        delete[] mapa[i];
    }
    delete[] mapa;

    return 0;
}