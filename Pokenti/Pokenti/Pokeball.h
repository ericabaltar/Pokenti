#pragma once
#include "mapa.h"

class PokeBall {
public:
    PokeBall(); // Constructor
    bool RecogerPokeball(int limiteMapa_x, int limiteMapa_y, char** casillas);
};
