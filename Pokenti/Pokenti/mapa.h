#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Types.h"
#include <algorithm>

using namespace std;

struct Mapa
{
    int FILAS;
    int COLUMNAS;
    int FIRST_AREA_POK;
    int FIRST_AREA_MIN_POK;
    int SECOND_AREA_POK;
    int SECOND_AREA_MIN_POK;
    const char VACIO = ' ';
    const char PARED = 'X';
    const char POKEMON = 'P';
    const int RANGO_VISTA_JUGADOR = 1;
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
        
        casillas = new char* [FILAS];
        for (int i = 0; i < FILAS; ++i) {
            casillas[i] = new char[COLUMNAS];

            for (int j = 0; j < COLUMNAS; ++j) {
                casillas[i][j] = VACIO;

                if (i == 0 || j == 0 || i == FILAS - 1 || j == COLUMNAS - 1) {
                    casillas[i][j] = PARED;
                }
            }
        }

        int mitadFilas = FILAS / 2;
        int mitadColumnas = COLUMNAS / 2;

        // Cuadrante 1: Pueblo Paleta
        for (int i = 1; i < mitadFilas; ++i) {
            for (int j = 1; j < mitadColumnas; ++j) {
                casillas[i][j] = 'a';
            }
        }

        // Cuadrante 2: Bosque
        for (int i = 1; i < mitadFilas; ++i) {
            for (int j = mitadColumnas; j < COLUMNAS - 1; ++j) {
                casillas[i][j] = 'b';
            }
        }

        // Cuadrante 3: Cueva Celeste
        for (int i = mitadFilas; i < FILAS - 1; ++i) {
            for (int j = 1; j < mitadColumnas; ++j) {
                casillas[i][j] = 'c';
            }
        }

        // Cuadrante 4: Liga PokENTI
        for (int i = mitadFilas; i < FILAS - 1; ++i) {
            for (int j = mitadColumnas; j < COLUMNAS - 1; ++j) {
                casillas[i][j] = 'd';
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

    void PintarVista(Position playerPos, int MaxX, int MaxY)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(hConsole, &cursorInfo);

        int clampedViewMinX = std::max<int>(0, playerPos.x - RANGO_VISTA_JUGADOR);
        int clampedViewMaxX = std::min<int>(MaxX, playerPos.x + RANGO_VISTA_JUGADOR);
        int clampedViewMinY = std::max<int>(0, playerPos.y - RANGO_VISTA_JUGADOR);
        int clampedViewMaxY = std::min<int>(MaxY, playerPos.y + RANGO_VISTA_JUGADOR);
        
        for (int i = clampedViewMinY; i <= clampedViewMaxY; i++)
        {
            for (int j = clampedViewMinX; j <= clampedViewMaxX; j++)
            {
                switch (casillas[i][j]) {
                case 'X':
                    SetConsoleTextAttribute(hConsole, 8); // Gris          
                    break;
                default:
                    SetConsoleTextAttribute(hConsole, 15); // Blanco
                    break;
                }
                cout << casillas[i][j];
                cout << '\t';
            }
            cout << endl << endl;
        }
    }

    void Pintar()
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(hConsole, &cursorInfo);

        for (int i = 0; i < FILAS; ++i) {
            for (int j = 0; j < COLUMNAS; ++j) {
                cout << ' ';
                switch (casillas[i][j]) {
                case 'X':
                    SetConsoleTextAttribute(hConsole, 8); // Gris          
                    break;
                default:
                    SetConsoleTextAttribute(hConsole, 15); // Blanco
                    break;
                }
                cout << casillas[i][j];
            }
            cout << endl << endl;
        }

        SetConsoleTextAttribute(hConsole, 15); // Restablecer el color de la consola
        cursorInfo.bVisible = true;
        SetConsoleCursorInfo(hConsole, &cursorInfo);
    }
};


