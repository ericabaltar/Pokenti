#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Types.h"
#include "Ash.h"
#include <algorithm>
#include <cstdlib> // Para la generación de números aleatorios
#include <ctime>   // Para inicializar la semilla de generación aleatoria
#include <conio.h> // Incluir la librería para getch()

using namespace std;

struct Mapa
{
    int FILAS;
    int COLUMNAS;
    int FIRST_AREA_POK;
    int FIRST_AREA_MIN_POK;
    int SECOND_AREA_POK;
    int SECOND_AREA_MIN_POK;
    int ERICACHU_DAMAGE;
    int POKEMON_LIFE;
    int MEWTWO_LIFE;
    int MIN_TIME_MOVE_POKEMON;
    int MAX_TIME_MOVE_POKEMON;

    int limiteMapa_x;
    int limiteMapa_y;
    int limiteMov_X;
    int limiteMov_Y;
    const char VACIO = ' ';
    const char PARED = 'X';
    const char SEPARADOR = 'x';
    const char POKEMON = 'P';
    const char POKEBALL = 'O';
    int contadorPokeballs = 0;
    const int RANGO_VISTA_JUGADOR_X = 22;
    const int RANGO_VISTA_JUGADOR_Y = 12;
    char** casillas;

    Mapa() {
        // Inicializar la semilla de números aleatorios
        srand(time(0));

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
        myFile >> ERICACHU_DAMAGE >> aux;
        myFile >> POKEMON_LIFE >> aux >> MEWTWO_LIFE >> aux;
        myFile >> MIN_TIME_MOVE_POKEMON >> aux >> MAX_TIME_MOVE_POKEMON >> aux;

        myFile.close();

        limiteMapa_x = COLUMNAS;
        limiteMapa_y = FILAS / 2;
        limiteMov_X = COLUMNAS / 2 + 1;
        limiteMov_Y = FILAS / 2 + 1;

        int mitadFilas = FILAS / 2;
        int mitadColumnas = COLUMNAS / 2;

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
        // Cuadrante 2: Bosque
        for (int i = 1; i < mitadFilas - 1; ++i) {
            for (int j = mitadColumnas + 1; j < COLUMNAS - 1; ++j) {
                casillas[i][j] = VACIO;
            }
        }

        // Cuadrante 3: Cueva Celeste
        for (int i = mitadFilas + 1; i < FILAS - 1; ++i) {
            for (int j = 1; j < mitadColumnas - 1; ++j) {
                casillas[i][j] = VACIO;
            }
        }
        // Cuadrante 4: Liga PokENTI
        for (int i = mitadFilas + 1; i < FILAS - 1; ++i) {
            for (int j = mitadColumnas + 1; j < COLUMNAS - 1; ++j) {
                casillas[i][j] = VACIO;
            }
        }

        // Agregar los seis pokémons aleatoriamente en el Pueblo Paleta
        for (int i = 0; i < FIRST_AREA_POK; i++) {
            // Verificar si la casilla está vacía antes de colocar el pokémon
            int nuevoPokemonX, nuevoPokemonY;
            do {
                nuevoPokemonX = rand() % (mitadColumnas / 2 - 1) + 1;
                nuevoPokemonY = rand() % (mitadFilas / 2 - 1) + 1;
            } while (casillas[nuevoPokemonY][nuevoPokemonX] != VACIO);

            casillas[nuevoPokemonY][nuevoPokemonX] = POKEMON; // Colocar el nuevo Pokémon
        }

        for (int i = 0; i < SECOND_AREA_POK; i++) {
            int nuevoPokemonX, nuevoPokemonY;
            do {
                nuevoPokemonX = rand() % (COLUMNAS / 2 - 1) + COLUMNAS / 2 - 1;
                nuevoPokemonY = rand() % (FILAS / 2 - 1) + 1;
            } while (casillas[nuevoPokemonY][nuevoPokemonX] != VACIO);

            casillas[nuevoPokemonY][nuevoPokemonX] = POKEMON; // Colocar el nuevo Pokémon
        }

        // Inicializar una Pokeball en una posición aleatoria
        GestionarPokeBalls();
    }

    ~Mapa()
    {
        for (int i = 0; i < FILAS; ++i) {
            delete[] casillas[i];
        }
        delete[] casillas;
    }

    void GestionarPokeBalls()
    {
        // Contar la cantidad de pokémons presentes en el mapa
        int PokeBallsPresentesZona1 = 0;
        for (int i = 0; i < FILAS / 2; ++i) {
            for (int j = 0; j < COLUMNAS / 2; ++j) {
                if (casillas[i][j] == POKEBALL) {
                    PokeBallsPresentesZona1++;
                }
            }
        }
        // Si hay menos de 1 PokeBall, generar y colocar una nueva
        if (PokeBallsPresentesZona1 < 1) {
            int nuevaPokeBallX, nuevaPokeBallY;
            do {
                nuevaPokeBallX = rand() % (COLUMNAS / 2 - 1) + 1;
                nuevaPokeBallY = rand() % (FILAS / 2 - 1) + 1;
            } while (casillas[nuevaPokeBallY][nuevaPokeBallX] != VACIO);

            casillas[nuevaPokeBallY][nuevaPokeBallX] = POKEBALL; // Colocar la nueva PokeBall
        }

        int PokeBallsPresentesZona2 = 0;
        for (int i = 0; i < FILAS / 2; ++i) {
            for (int j = COLUMNAS / 2; j < COLUMNAS; ++j) {
                if (casillas[i][j] == POKEBALL) {
                    PokeBallsPresentesZona2++;
                }
            }
        }
        // Si hay menos de 18 pokémons, generar y colocar uno nuevo
        if (PokeBallsPresentesZona2 < 1) {
            int nuevaPokeBallX, nuevaPokeBallY;
            do {
                nuevaPokeBallX = rand() % (COLUMNAS / 2 - 1) + COLUMNAS / 2 - 1;
                nuevaPokeBallY = rand() % (FILAS / 2 - 1) + 1;
            } while (casillas[nuevaPokeBallY][nuevaPokeBallX] != VACIO);

            casillas[nuevaPokeBallY][nuevaPokeBallX] = POKEBALL; // Colocar el nuevo Pokémon
        }
    
    }

    bool RecogerPokeball(int jugadorX, int jugadorY)
    {
        if (casillas[jugadorY][jugadorX] == POKEBALL)
        {
            // Generar una nueva posición aleatoria para una PokeBall
            int nuevaPokeBallX, nuevaPokeBallY;
            do {
                nuevaPokeBallX = rand() % (limiteMapa_x - 1) + 1;
                nuevaPokeBallY = rand() % (limiteMapa_y - 1) + 1;
            } while (casillas[nuevaPokeBallY][nuevaPokeBallX] != VACIO);

            casillas[nuevaPokeBallX][nuevaPokeBallX] = POKEBALL; // Colocar el nuevo Pokémon
            return true;
        }
        return false;
    }

    void GestionarPokemons()
    {
        // Contar la cantidad de pokémons presentes en el mapa
        int pokemonsPresentesZona1 = 0;
        for (int i = 0; i < FILAS / 2; ++i) {
            for (int j = 0; j < COLUMNAS / 2; ++j) {
                if (casillas[i][j] == POKEMON) {
                    pokemonsPresentesZona1++;
                }
            }
        }
        // Si hay menos de 6 pokémons, generar y colocar uno nuevo
        if (pokemonsPresentesZona1 < FIRST_AREA_POK) {
            int nuevoPokemonX, nuevoPokemonY;
            do {
                nuevoPokemonX = rand() % (COLUMNAS / 2 - 1) + 1;
                nuevoPokemonY = rand() % (FILAS / 2 - 1) + 1;
            } while (casillas[nuevoPokemonY][nuevoPokemonX] != VACIO);

            casillas[nuevoPokemonY][nuevoPokemonX] = POKEMON; // Colocar el nuevo Pokémon
        }
        int pokemonsPresentesZona2 = 0;
        for (int i = 0; i < FILAS / 2; ++i) {
            for (int j = COLUMNAS / 2; j < COLUMNAS; ++j) {
                if (casillas[i][j] == POKEMON) {
                    pokemonsPresentesZona2++;
                }
            }
        }
        // Si hay menos de 18 pokémons, generar y colocar uno nuevo
        if (pokemonsPresentesZona2 < SECOND_AREA_POK) {
            int nuevoPokemonX, nuevoPokemonY;
            do {
                nuevoPokemonX = rand() % (COLUMNAS / 2 - 1) + COLUMNAS / 2 - 1;
                nuevoPokemonY = rand() % (FILAS / 2 - 1) + 1;
            } while (casillas[nuevoPokemonY][nuevoPokemonX] != VACIO);

            casillas[nuevoPokemonY][nuevoPokemonX] = POKEMON; // Colocar el nuevo Pokémon
        }
    }

    bool CazarPokemon(int jugadorX, int jugadorY, Position playerPos)
    {
        //if(Ash PokeBall == 1) {
            if (casillas[jugadorY - 1][jugadorX] == POKEMON || casillas[jugadorY + 1][jugadorX] == POKEMON
                || casillas[jugadorY][jugadorX + 1] == POKEMON || casillas[jugadorY][jugadorX - 1] == POKEMON)
            {
                if (casillas[jugadorY - 1][jugadorX] == POKEMON)
                    casillas[jugadorY - 1][jugadorX] = VACIO;
                else if (casillas[jugadorY + 1][jugadorX] == POKEMON)
                    casillas[jugadorY + 1][jugadorX] = VACIO;
                else if (casillas[jugadorY][jugadorX + 1] == POKEMON)
                    casillas[jugadorY][jugadorX + 1] = VACIO;
                else if (casillas[jugadorY][jugadorX - 1] == POKEMON)
                    casillas[jugadorY][jugadorX - 1] = VACIO;
                    

                    // Generar una nueva posición aleatoria para un Pokémon

                int nuevoPokemonX, nuevoPokemonY;
                do {
                    nuevoPokemonX = rand() % (limiteMapa_x - 1) + 1;
                    nuevoPokemonY = rand() % (limiteMapa_y - 1) + 1;
                } while (casillas[nuevoPokemonY][nuevoPokemonX] != VACIO);

                casillas[nuevoPokemonY][nuevoPokemonX] = POKEMON; // Colocar el nuevo Pokémon
              

                // Mostrar la pantalla actualizada
                PintarVista(playerPos);
                // Congelar la pantalla hasta que el usuario presione una tecla
                std::cout << "Presiona cualquier tecla para continuar...";
                _getch(); // Espera a que el usuario presione una tecla

                return true;
            }
            return false;
        //}
    }

    void PintarVista(Position playerPos)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(hConsole, &cursorInfo);

        int clampedViewMinX = std::max<int>(0, playerPos.x - RANGO_VISTA_JUGADOR_X);
        int clampedViewMaxX = std::min<int>(limiteMapa_x, playerPos.x + RANGO_VISTA_JUGADOR_X);
        int clampedViewMinY = std::max<int>(0, playerPos.y - RANGO_VISTA_JUGADOR_Y);
        int clampedViewMaxY = std::min<int>(limiteMapa_y, playerPos.y + RANGO_VISTA_JUGADOR_Y);

        for (int i = clampedViewMinY; i <= clampedViewMaxY; i++)
        {
            for (int j = clampedViewMinX; j <= clampedViewMaxX; j++)
            {
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
                case 'P':
                    SetConsoleTextAttribute(hConsole, 13); // Rosa
                    break;
                case 'O':
                    SetConsoleTextAttribute(hConsole, 14); // Amarillo
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

    void PintarTodo()
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(hConsole, &cursorInfo);

        for (int i = 0; i < FILAS; i++)
        {
            for (int j = 0; j < COLUMNAS; j++)
            {
                //CazarPokemon(i, jugadorY, j, jugadorX);

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
                case 'P':
                    SetConsoleTextAttribute(hConsole, 13); // Rosa
                    break;
                case 'O':
                    SetConsoleTextAttribute(hConsole, 14); // Amarillo
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

    void UnlockBosque()
    {
        //aumentar limites de la camara (y el player)
        limiteMapa_x = COLUMNAS - 1;
        limiteMov_X = COLUMNAS - 1;
        //borrar la barrera
        for (int i = 1; i < FILAS / 2; ++i) {
            casillas[i][COLUMNAS / 2] = VACIO;
        }
    }
    void UnlockCueva()
    {
        //aumentar limites de la camara (y el player)
        limiteMapa_x = COLUMNAS - 1;
        limiteMov_X = COLUMNAS - 1;
        limiteMov_Y = FILAS - 1;
        limiteMapa_y = FILAS - 1;
        //borrar barreras
        for (int i = FILAS / 2; i < FILAS - 1; ++i) {
            casillas[i][COLUMNAS / 2] = VACIO;
        }
        for (int i = 1; i < COLUMNAS - 1; ++i) {
            casillas[FILAS / 2][i] = VACIO;
        }
    }
};
