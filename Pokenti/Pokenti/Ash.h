#pragma once
#include <iostream>
#include <Windows.h>
#include "Types.h"
#include "mapa.h"
#include "Pokemons.h"

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
    int Pokimon;
    int PokeBall;
    Position pos;
    Position prevPos;
    char AshLook;
    AshMovement currentMove;

    Ash();
    void SetAshPos(int mapBorderX, int mapBorderY);
    void MoveAsh(int mapBorderX, int mapBorderY, Mapa& mapa, Pokemons& pokemons);

};

