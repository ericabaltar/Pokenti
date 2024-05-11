#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Types.h"
#include <algorithm>
#include <cstdlib> // Para la generación de números aleatorios
#include <ctime>   // Para inicializar la semilla de generación aleatoria

using namespace std;

struct Mapa
{
    int FILAS;
    int COLUMNAS;
    int FIRST_AREA_POK;
    int FIRST_AREA_MIN_POK;
    int SECOND_AREA_POK;
    int SECOND_AREA_MIN_POK;
    int limiteMapa_x;
    int limiteMapa_y;
    const char VACIO = ' ';
    const char PARED = 'X';
    const char SEPARADOR = 'x';
    const char POKEMON = 'P';
    char** casillas;

    Mapa() {

        {
            //leer datos del fichero
            ifstream myFile("config.txt");
            if (!myFile.is_open())
            {
                cout << "CAGASTE";
                abort();
            }

            char aux;
            myFile >> FILAS >> aux >> COLUMNAS >> aux;
            myFile >> FIRST_AREA_POK >> aux >> FIRST_AREA_MIN_POK >> aux;
            myFile >> SECOND_AREA_POK >> aux >> SECOND_AREA_MIN_POK >> aux;

            myFile.close();
        }

        int mitadFilas = limiteMapa_y = FILAS / 2;
        int mitadColumnas = limiteMapa_x = COLUMNAS / 2;

        casillas = new char* [FILAS];
        for (int i = 0; i < FILAS; ++i) {
            casillas[i] = new char[COLUMNAS];

            for (int j = 0; j < COLUMNAS; ++j) {
                casillas[i][j] = VACIO;

                if (i == 0 || j == 0 || i == FILAS - 1 || j == COLUMNAS - 1) {
                    casillas[i][j] = PARED;
                }
                else if (i == mitadFilas || j == mitadColumnas) {
                    casillas[i][j] = SEPARADOR;
                }
            }
        }

        // Cuadrante 1: Pueblo Paleta
        for (int i = 1; i < mitadFilas - 1; ++i) {
            for (int j = 1; j < mitadColumnas - 1; ++j) {
                casillas[i][j] = VACIO;
            }
        }

        // Inicializar la semilla de generación aleatoria
        srand(time(NULL));

        // Agregar los seis pokémons aleatoriamente en el Pueblo Paleta
        for (int k = 0; k < 6; ++k) {
            int randomRow = rand() % (mitadFilas - 1) + 1;     // Generar fila aleatoria
            int randomCol = rand() % (mitadColumnas - 1) + 1;  // Generar columna aleatoria

            // Verificar si la casilla está vacía antes de colocar el pokémon
            if (casillas[randomRow][randomCol] == VACIO) {
                casillas[randomRow][randomCol] = POKEMON;
            }
        }
    }

    ~Mapa()
    {
        for (int i = 0; i < FILAS; ++i) {
            delete[] casillas[i];
        }
        delete[] casillas;
    }

    void PintarVista()
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(hConsole, &cursorInfo);

        // Generar posición aleatoria para el jugador
        int jugadorX = rand() % (limiteMapa_x - 1) + 1;
        int jugadorY = rand() % (limiteMapa_y - 1) + 1;

        // Contar la cantidad de pokémons presentes en el mapa
        int pokemonsPresentes = 0;
        for (int i = 0; i < FILAS; ++i) {
            for (int j = 0; j < COLUMNAS; ++j) {
                if (casillas[i][j] == POKEMON) {
                    pokemonsPresentes++;
                }
            }
        }

        // Si hay menos de 6 pokémons, generar y colocar uno nuevo
        if (pokemonsPresentes < 6) {
            int nuevoPokemonX, nuevoPokemonY;
            do {
                nuevoPokemonX = rand() % (limiteMapa_x - 1) + 1;
                nuevoPokemonY = rand() % (limiteMapa_y - 1) + 1;
            } while (casillas[nuevoPokemonY][nuevoPokemonX] != VACIO);

            casillas[nuevoPokemonY][nuevoPokemonX] = POKEMON; // Colocar el nuevo Pokémon
        }

        //int clampedViewMinX = std::max<int>(0, playerPos.x - RANGO_VISTA_JUGADOR);
        int clampedViewMinX = 0;
        int clampedViewMaxX = limiteMapa_x;
        //int clampedViewMaxX = std::min<int>(MaxX, playerPos.x + RANGO_VISTA_JUGADOR);
        //int clampedViewMinY = std::max<int>(0, playerPos.y - RANGO_VISTA_JUGADOR);
        int clampedViewMinY = 0;
        int clampedViewMaxY = limiteMapa_y;
        //int clampedViewMaxY = std::min<int>(MaxY, playerPos.y + RANGO_VISTA_JUGADOR);

        for (int i = clampedViewMinY; i <= clampedViewMaxY; i++)
        {
            for (int j = clampedViewMinX; j <= clampedViewMaxX; j++)
            {
                // Verificar si el jugador está en la misma posición que un Pokémon
                if (i == jugadorY && j == jugadorX && casillas[i][j] == POKEMON) {
                    // Generar una nueva posición aleatoria para un Pokémon
                    int nuevoPokemonX, nuevoPokemonY;
                    do {
                        nuevoPokemonX = rand() % (limiteMapa_x - 1) + 1;
                        nuevoPokemonY = rand() % (limiteMapa_y - 1) + 1;
                    } while (casillas[nuevoPokemonY][nuevoPokemonX] != VACIO);

                    casillas[nuevoPokemonY][nuevoPokemonX] = POKEMON; // Colocar el nuevo Pokémon
                }

                switch (casillas[i][j]) {
                case '<':
                case '>':
                case 'v':
                case '^':
                    SetConsoleTextAttribute(hConsole, 12); // Rojo
                    break;
                case 'X':
                    SetConsoleTextAttribute(hConsole, 8); // Gris          
                    break;
                case 'x':
                    SetConsoleTextAttribute(hConsole, 9); // Azul
                    break;
                default:
                    SetConsoleTextAttribute(hConsole, 15); // Blanco
                    break;
                }
                cout << casillas[i][j];
                SetConsoleTextAttribute(hConsole, 15); // Blanco
            }
            cout << endl;
        }
    }
};
