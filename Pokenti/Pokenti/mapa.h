#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <algorithm>
#include "Types.h"
#include "Ash.h"
#include "FileReader.h"



enum class Direction
{
    UP,

    DOWN, 

    LEFT, 

    RIGHT 
};

struct Mapa
{
    int FILAS;
    int COLUMNAS;
    int FIRST_AREA_POKE;
    int FIRST_AREA_MIN_POKE;
    int SECOND_AREA_POKE;
    int SECOND_AREA_MIN_POKE;
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

    Mapa( const Settings& settings);
    ~Mapa();
    void GestionarPokeBalls();
    bool RecogerPokeball(int jugadorX, int jugadorY);
    void GestionarPokemons();
    bool CazarPokemon(int jugadorX, int jugadorY, Position playerPos);
    void PintarVista(Position playerPos);
    void PintarTodo();
    void UnlockBosque();
    void UnlockCueva();
};
