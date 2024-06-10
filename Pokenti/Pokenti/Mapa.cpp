#include "Mapa.h"


Mapa::Mapa(const Settings& settings) {
    srand(time(0));

    FILAS = settings.FILAS;
    COLUMNAS = settings.COLUMNAS;
    FIRST_AREA_POKE = settings.FIRST_AREA_POKE;
    FIRST_AREA_MIN_POKE = settings.FIRST_AREA_MIN_POKE;
    SECOND_AREA_POKE = settings.SECOND_AREA_POKE;
    SECOND_AREA_MIN_POKE = settings.SECOND_AREA_MIN_POKE;

    limiteMapa_x = settings.COLUMNAS;
    limiteMapa_y = settings.FILAS;
    limiteMov_X = settings.COLUMNAS / 2 + 1;
    limiteMov_Y = settings.FILAS / 2 + 1;

    int mitadFilas = settings.FILAS / 2;
    int mitadColumnas = settings.COLUMNAS / 2;

    casillas = new Casilla * [FILAS];
    for (int i = 0; i < FILAS; ++i) {
        casillas[i] = new Casilla[COLUMNAS];

        for (int j = 0; j < COLUMNAS; ++j) {
            casillas[i][j] = Casilla::VACIO;

            if (i == 0 || j == 0 || i == FILAS - 1 || j == COLUMNAS - 1) {
                casillas[i][j] = Casilla::PARED;
            }
            else if (i == mitadFilas || j == mitadColumnas) {
                casillas[i][j] = Casilla::SEPARADOR;
            }
        }
    }

    for (int i = 1; i < mitadFilas - 1; ++i) {
        for (int j = 1; j < mitadColumnas - 1; ++j) {
            casillas[i][j] = Casilla::VACIO;
        }
    }
    for (int i = 1; i < mitadFilas - 1; ++i) {
        for (int j = mitadColumnas + 1; j < COLUMNAS - 1; ++j) {
            casillas[i][j] = Casilla::VACIO;
        }
    }

    for (int i = mitadFilas + 1; i < FILAS - 1; ++i) {
        for (int j = 1; j < mitadColumnas - 1; ++j) {
            casillas[i][j] = Casilla::VACIO;
        }
    }

    for (int i = mitadFilas + 1; i < FILAS - 1; ++i) {
        for (int j = mitadColumnas + 1; j < COLUMNAS - 1; ++j) {
            casillas[i][j] = Casilla::VACIO;
        }
    }

    for (int i = 0; i < FIRST_AREA_POKE; i++) {
        int nuevoPokemonX, nuevoPokemonY;
        do {
            nuevoPokemonX = rand() % (mitadColumnas / 2 - 1) + 1;
            nuevoPokemonY = rand() % (mitadFilas / 2 - 1) + 1;
        } while (casillas[nuevoPokemonY][nuevoPokemonX] != Casilla::VACIO);

        casillas[nuevoPokemonY][nuevoPokemonX] = Casilla::POKEMON;
    }

    for (int i = 0; i < SECOND_AREA_POKE - 3; i++) {
        int nuevoPokemonX, nuevoPokemonY;
        do {
            nuevoPokemonX = rand() % (COLUMNAS / 2 - 1) + COLUMNAS / 2 - 1;
            nuevoPokemonY = rand() % (FILAS / 2 - 1) + 1;
        } while (casillas[nuevoPokemonY][nuevoPokemonX] != Casilla::VACIO);

        casillas[nuevoPokemonY][nuevoPokemonX] = Casilla::POKEMON;
    }
}

Mapa::~Mapa() {
    for (int i = 0; i < FILAS; ++i) {
        delete[] casillas[i];
    }
    delete[] casillas;
}


void Mapa::PintarVista(Position playerPos) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    int clampedViewMinX = std::max<int>(0, playerPos.x - RANGO_VISTA_JUGADOR_X);
    int clampedViewMaxX = std::min<int>(limiteMapa_x, playerPos.x + RANGO_VISTA_JUGADOR_X);
    int clampedViewMinY = std::max<int>(0, playerPos.y - RANGO_VISTA_JUGADOR_Y);
    int clampedViewMaxY = std::min<int>(limiteMapa_y, playerPos.y + RANGO_VISTA_JUGADOR_Y);

    for (int i = clampedViewMinY; i <= clampedViewMaxY; i++) {
        for (int j = clampedViewMinX; j <= clampedViewMaxX; j++) {
            switch (casillas[i][j]) {
            case Casilla::DIRECCION_IZQUIERDA:
            case Casilla::DIRECCION_DERECHA:
            case Casilla::DIRECCION_ABAJO:
            case Casilla::DIRECCION_ARRIBA:
                SetConsoleTextAttribute(hConsole, 12);
                break;
            case Casilla::PARED:
                SetConsoleTextAttribute(hConsole, 8);
                break;
            case Casilla::SEPARADOR:
                SetConsoleTextAttribute(hConsole, 9);
                break;
            case Casilla::POKEMON:
                SetConsoleTextAttribute(hConsole, 10);
                break;
            case Casilla::POKEBALL:
                SetConsoleTextAttribute(hConsole, 14);
                break;
            case Casilla::MEWTWO:
                SetConsoleTextAttribute(hConsole, 13);
                break;
            default:
                SetConsoleTextAttribute(hConsole, 15);
                break;
            }
            std::cout << static_cast<char>(casillas[i][j]);
            SetConsoleTextAttribute(hConsole, 15);
        }
        std::cout << std::endl;
    }
}


void Mapa::PintarTodo() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            switch (casillas[i][j]) {
            case Casilla::DIRECCION_IZQUIERDA:
            case Casilla::DIRECCION_DERECHA:
            case Casilla::DIRECCION_ABAJO:
            case Casilla::DIRECCION_ARRIBA:
                SetConsoleTextAttribute(hConsole, 12);
                break;
            case Casilla::PARED:
                SetConsoleTextAttribute(hConsole, 8);
                break;
            case Casilla::SEPARADOR:
                SetConsoleTextAttribute(hConsole, 9);
                break;
            case Casilla::POKEMON:
                SetConsoleTextAttribute(hConsole, 13);
                break;
            case Casilla::POKEBALL:
                SetConsoleTextAttribute(hConsole, 14);
                break;
            default:
                SetConsoleTextAttribute(hConsole, 15);
                break;
            }
            std::cout << static_cast<char>(casillas[i][j]);
            SetConsoleTextAttribute(hConsole, 15);
        }
        std::cout << std::endl;
    }
}



void Mapa::UnlockBosque() {
    limiteMapa_x = COLUMNAS - 1;
    limiteMov_X = COLUMNAS - 1;
    limiteMapa_y = FILAS - 1;

    for (int i = 1; i < FILAS / 2; ++i) {
        casillas[i][COLUMNAS / 2] = Casilla::VACIO;
    }
}

void Mapa::UnlockCueva() {
    limiteMapa_x = COLUMNAS - 1;
    limiteMov_X = COLUMNAS - 1;
    limiteMov_Y = FILAS - 1;
    limiteMapa_y = FILAS - 1;

    for (int i = COLUMNAS / 2; i < COLUMNAS - 1; ++i) {
        casillas[FILAS / 2][i] = Casilla::VACIO;
    }
}
