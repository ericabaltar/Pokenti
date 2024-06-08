#pragma once
#include "mapa.h"
#include "Ash.h"
#include "FileReader.h"

class Ash;
class Mapa;
class Pokemons {
public:

    void GestionarPokemons(Mapa& mapa);
    bool CazarPokemon(int jugadorX, int jugadorY, Position playerPos, const Mapa& mapa, Pokemons& pokemons, Ash& ash, Settings& settings);
    bool GestionarMewtwo(int jugadorX, int jugadorY, const Mapa& mapa, Settings& settings);
};
