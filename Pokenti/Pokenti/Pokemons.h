#pragma once
#include "mapa.h"
class Mapa;
class Pokemons {
public:
    void GestionarPokemons(Mapa& mapa);
    bool CazarPokemon(int jugadorX, int jugadorY, Position playerPos, const Mapa& mapa, Pokemons& pokemons);
};
