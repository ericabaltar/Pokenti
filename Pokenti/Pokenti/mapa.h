#pragma once
#include <iostream>
#include <Windows.h>

using namespace std;

void dibujarMapa(char** mapa, int filas, int columnas) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            switch (mapa[i][j]) {
            case 'X':
                SetConsoleTextAttribute(hConsole, 8); // Gris
                cout << char(219);
                break;
            default:
                SetConsoleTextAttribute(hConsole, 15); // Blanco
                cout << mapa[i][j];
                break;
            }
        }
        cout << endl;
    }

    SetConsoleTextAttribute(hConsole, 15); // Restablecer el color de la consola
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}



