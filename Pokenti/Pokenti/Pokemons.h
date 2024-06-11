#pragma once
#include "Mapa.h"
#include "Ash.h"
#include "FileReader.h"
#include <ctime>
#include <chrono>
#include <conio.h>
#include <vector>

class Ash;
class Mapa;

enum class PokemonNames
{
    BULBASAUR,
    CHARMANDER,
    SQUIRTLE,
    PSYDUCK,
    JIGGLYPUFF,
    EEVEE,
};

class Pokemons {
public:

    void GestionarPokemons(Mapa& mapa, Settings& settings);
    bool CazarPokemon(int jugadorX, int jugadorY, Position playerPos, const Mapa& mapa, Pokemons& pokemons, Ash& ash, Settings& settings);
    bool GestionarMewtwo(int jugadorX, int jugadorY, const Mapa& mapa,Settings& settings);
    bool CapturarPokemon(int jugadorX, int jugadorY, const Mapa& mapa, Pokemons& pokemons, Ash& ash, Settings& settings);
    bool AtacarPokemon(int jugadorX, int jugadorY, const Mapa& mapa, Pokemons& pokemons, Ash& ash, Settings& settings);
    bool Huir(int jugadorX, int jugadorY, const Mapa& mapa);
    static std::string GetRandomPokemonName();
    std::string GetPokemonName(int jugadorX, int jugadorY, const Mapa& mapa);
    void MostrarMensajeConRetardo(const std::string& mensaje);
    bool EsMewtwo(int jugadorX, int jugadorY, const Mapa& mapa);

private:

    void MoverPokemons(Mapa& mapa, Settings& settings);

    bool pokemonsMoviendose = true;

    int pokemonsPresentesZona1;
    int pokemonsPresentesZona2;
    int nuevoPokemonX;
    int nuevoPokemonY;

    int minTime;
    int maxTime;
    int waitTime;
    std::chrono::time_point<std::chrono::system_clock> now;
    std::chrono::duration<double> elapsed_seconds;
    std::chrono::time_point<std::chrono::system_clock> lastMoveTime;

    static bool mewtwoAparecido;
    int mewtwoX = 52;
    int mewtwoY = 37;

    int probabilidad;
    int probabilidadLegendario;
    int randNum;

    std::vector<PokemonNames> nombresPokemon = {
        PokemonNames::BULBASAUR,
        PokemonNames::CHARMANDER,
        PokemonNames::SQUIRTLE,
        PokemonNames::PSYDUCK,
        PokemonNames::JIGGLYPUFF,
        PokemonNames::EEVEE

    };

};

