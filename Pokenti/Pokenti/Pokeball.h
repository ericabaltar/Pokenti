#pragma once
#include "mapa.h"
#include "Ash.h"

class Ash;
class Mapa;

class PokeBall {
public:
    PokeBall(); // Constructor
     void GestionarPokeBalls(Mapa& mapa);
     bool VerificarPokeball(int jugadorX, int jugadorY, Mapa& mapa, Position ashPos, Ash& ash);
};
