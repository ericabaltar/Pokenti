#include "mapa.h"
#include "Ash.h"

int main() {
    
    const int FILAS = 10;
    const int COLUMNAS = 20;
    char vacio = ' ';
    char pared = 'X';
    Ash ash;
    
    char** mapa = new char*[FILAS];
    for (int i = 0; i < FILAS; ++i) {
        mapa[i] = new char[COLUMNAS];
        
        for (int j = 0; j < COLUMNAS; ++j) {
            mapa[i][j] = vacio;

            if (i == 0 || j == 0 || i == FILAS - 1 || j == COLUMNAS - 1) {
                mapa[i][j] = pared;
            }
        }
    }

    
    int mitadFilas = FILAS / 2;
    int mitadColumnas = COLUMNAS / 2;

    // Cuadrante 1: Pueblo Paleta
    for (int i = 1; i < mitadFilas; ++i) {
        for (int j = 1; j < mitadColumnas; ++j) {
            mapa[i][j] = 'a';
        }
    }

    // Cuadrante 2: Bosque
    for (int i = 1; i < mitadFilas; ++i) {
        for (int j = mitadColumnas; j < COLUMNAS-1; ++j) {
            mapa[i][j] = 'b';
        }
    }

    // Cuadrante 3: Cueva Celeste
    for (int i = mitadFilas; i < FILAS-1; ++i) {
        for (int j = 1; j < mitadColumnas; ++j) {
            mapa[i][j] = 'c';
        }
    }

    // Cuadrante 4: Liga PokENTI
    for (int i = mitadFilas; i < FILAS-1; ++i) {
        for (int j = mitadColumnas; j < COLUMNAS-1; ++j) {
            mapa[i][j] = 'd';
        }
    }

    while (true) {
        ash.MoveAsh();
        //ash.printAsh();
        std::cout << ash.pos.x << " " << ash.pos.y;
        std::cout << std::endl;
        mapa[ash.prevPos.y][ash.prevPos.x] = vacio;
        mapa[ash.pos.y][ash.pos.x] = ash.AshLook;
        dibujarMapa(mapa, FILAS, COLUMNAS);
        Sleep(250);
        system("cls");
    }

    // Liberar la memoria asignada para el mapa
    for (int i = 0; i < FILAS; ++i) {
        delete[] mapa[i];
    }
    delete[] mapa;

    return 0;
}