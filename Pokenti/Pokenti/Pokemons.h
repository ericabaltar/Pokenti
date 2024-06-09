#pragma once
#include "mapa.h"
#include "Ash.h"
#include "FileReader.h"
#include <ctime>
#include <chrono>

class Ash;
class Mapa;
class Pokemons {
public:
    Pokemons() {
        lastMoveTime = std::chrono::system_clock::now();
    }

    void GestionarPokemons(Mapa& mapa, Settings& settings);
    bool CazarPokemon(int jugadorX, int jugadorY, Position playerPos, const Mapa& mapa, Pokemons& pokemons, Ash& ash, Settings& settings);
    bool GestionarMewtwo(int jugadorX, int jugadorY, const Mapa& mapa, Settings& settings);
    void MoverPokemons(Mapa& mapa, const Settings& settings);

private:
    std::chrono::time_point<std::chrono::system_clock> lastMoveTime;
};
