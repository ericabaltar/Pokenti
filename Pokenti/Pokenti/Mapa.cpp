#include "mapa.h"


Mapa :: Mapa(const Settings& settings) {
    // Inicializar la semilla de números aleatorios
    srand(time(0));
    FILAS = settings.FILAS;
    COLUMNAS = settings.COLUMNAS;
    FIRST_AREA_POKE = settings.FIRST_AREA_POKE;
    FIRST_AREA_MIN_POKE = settings.FIRST_AREA_MIN_POKE;
    SECOND_AREA_POKE = settings.SECOND_AREA_POKE;
    SECOND_AREA_MIN_POKE = settings.SECOND_AREA_MIN_POKE;
    ERICACHU_DAMAGE = settings.ERICACHU_DAMAGE;
    POKEMON_LIFE = settings.POKEMON_LIFE;
    MEWTWO_LIFE = settings.MEWTWO_LIFE;
    MIN_TIME_MOVE_POKEMON = settings.MIN_TIME_MOVE_POKEMON;
    MAX_TIME_MOVE_POKEMON = settings.MAX_TIME_MOVE_POKEMON;

    limiteMapa_x = settings.COLUMNAS;
    limiteMapa_y = settings.FILAS;
    limiteMov_X = settings.COLUMNAS / 2 + 1;
    limiteMov_Y = settings.FILAS / 2 + 1;

   
    int mitadFilas = settings.FILAS / 2;
    int mitadColumnas = settings.COLUMNAS / 2;
   
    casillas = new char* [FILAS];
    for (int i = 0; i < FILAS; ++i) {
        casillas[i] = new char[COLUMNAS];

        for (int j = 0; j < COLUMNAS; ++j) {
            casillas[i][j] = this->VACIO;

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
    for (int i = 0; i < FIRST_AREA_POKE; i++) {
        // Verificar si la casilla está vacía antes de colocar el pokémon
        int nuevoPokemonX, nuevoPokemonY;
        do {
            nuevoPokemonX = rand() % (mitadColumnas / 2 - 1) + 1;
            nuevoPokemonY = rand() % (mitadFilas / 2 - 1) + 1;
        } while (casillas[nuevoPokemonY][nuevoPokemonX] != VACIO);

        casillas[nuevoPokemonY][nuevoPokemonX] = POKEMON; // Colocar el nuevo Pokémon
    }

    for (int i = 0; i < SECOND_AREA_POKE-3; i++) {
        int nuevoPokemonX, nuevoPokemonY;
        do {
            nuevoPokemonX = rand() % (COLUMNAS / 2 - 1) + COLUMNAS / 2 - 1;
            nuevoPokemonY = rand() % (FILAS / 2 - 1) + 1;
        } while (casillas[nuevoPokemonY][nuevoPokemonX] != VACIO);

        casillas[nuevoPokemonY][nuevoPokemonX] = POKEMON; // Colocar el nuevo Pokémon
    }
}

Mapa ::~Mapa()
{
    for (int i = 0; i < FILAS; ++i) {
        delete[] casillas[i];
    }
    delete[] casillas;
}

void Mapa::PintarVista(Position playerPos)
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
                SetConsoleTextAttribute(hConsole, 10); // Rosa
                break;
            case 'O':
                SetConsoleTextAttribute(hConsole, 14); // Amarillo
                break;
            case 'M':
                SetConsoleTextAttribute(hConsole, 13); // Amarillo
                break;
            default:
                SetConsoleTextAttribute(hConsole, 15); // Blanco
                break;
            }
           std:: cout << casillas[i][j];
            SetConsoleTextAttribute(hConsole, 15); // Blanco
        }
        std::cout << std::endl;
    }
}

void Mapa::PintarTodo()
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
            std::cout << casillas[i][j];
            SetConsoleTextAttribute(hConsole, 15); // Blanco
        }
        std::cout << std::endl;
    }
}

void Mapa::UnlockBosque()
{
    //aumentar limites de la camara (y el player)
    limiteMapa_x = COLUMNAS - 1;
    limiteMov_X = COLUMNAS - 1;
    limiteMapa_y = FILAS - 1;
    //borrar la barrera
    for (int i = 1; i < FILAS / 2; ++i) {
        casillas[i][COLUMNAS / 2] = VACIO;
    }
}
void Mapa::UnlockCueva()
{
    //aumentar limites de la camara (y el player)
    limiteMapa_x = COLUMNAS - 1;
    limiteMov_X = COLUMNAS - 1;
    limiteMov_Y = FILAS - 1;
    limiteMapa_y = FILAS - 1;
    // Borrar barreras
    for (int i = COLUMNAS / 2; i < COLUMNAS - 1; ++i) {
        casillas[FILAS / 2][i] = VACIO;
    }
}