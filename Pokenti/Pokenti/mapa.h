#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <algorithm>
#include "Types.h"
#include "Ash.h"
#include "FileReader.h"
#include "Pokeball.h"

enum class Casilla {
    VACIO = ' ',

    PARED = 'X',

    SEPARADOR = 'x',

    POKEMON = 'P',

    POKEBALL = 'O',

    MEWTWO = 'M',

    DIRECCION_IZQUIERDA = '<',

    DIRECCION_DERECHA = '>',

    DIRECCION_ABAJO = 'v',

    DIRECCION_ARRIBA = '^'
};

struct Mapa{
public:

    Mapa(const Settings& settings);

    ~Mapa();

    void PintarVista(Position playerPos);
    void PintarTodo();
    void UnlockBosque();
    void UnlockCueva();

    int limiteMov_X;
    int limiteMov_Y;




    Casilla** casillas;


private:

    int FILAS;
    int COLUMNAS;
    int FIRST_AREA_POKE;
    int FIRST_AREA_MIN_POKE;
    int SECOND_AREA_POKE;
    int SECOND_AREA_MIN_POKE;

    int limiteMapa_x;
    int limiteMapa_y;

    const int RANGO_VISTA_JUGADOR_X = 22;
    const int RANGO_VISTA_JUGADOR_Y = 12;

};
