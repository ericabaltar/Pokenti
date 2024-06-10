#pragma once
#include <iostream>
#include <Windows.h>
#include "Types.h"
#include "Mapa.h"
#include "Pokemons.h"
#include "FileReader.h"

class Mapa;
class Pokemons;

enum class AshMovement
{
    UP,

    DOWN,

    LEFT,

    RIGHT,

    NONE
};


struct Ash
{
    public:
    int Pokimon;
    int PokeBall;
    Position pos;
    Position prevPos;
    char AshLook;
    AshMovement currentMove;

    Ash();
    void SetAshPos(int mapBorderX, int mapBorderY);
    void MoveAsh(int mapBorderX, int mapBorderY, Mapa& mapa, Pokemons& pokemons, Ash& ash, Settings& settings);
};

