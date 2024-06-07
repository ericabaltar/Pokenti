#include "Pokemons.h"

void Pokemons::GestionarPokemons(Mapa& mapa) {
    // Contar la cantidad de pokémons presentes en la zona 1 del mapa
    int pokemonsPresentesZona1 = 0;
    for (int i = 0; i < mapa.FILAS / 2; ++i) {
        for (int j = 0; j < mapa.COLUMNAS / 2; ++j) {
            if (mapa.casillas[i][j] == mapa.POKEMON) {
                pokemonsPresentesZona1++;
            }
        }
    }

    // Si hay menos de 6 pokémons en la zona 1, generar y colocar uno nuevo
    if (pokemonsPresentesZona1 < mapa.FIRST_AREA_POKE) {
        int nuevoPokemonX, nuevoPokemonY;
        do {
            nuevoPokemonX = rand() % (mapa.COLUMNAS / 2 - 1) + 1;
            nuevoPokemonY = rand() % (mapa.FILAS / 2 - 1) + 1;
        } while (mapa.casillas[nuevoPokemonY][nuevoPokemonX] != mapa.VACIO);

        mapa.casillas[nuevoPokemonY][nuevoPokemonX] = mapa.POKEMON; // Colocar el nuevo Pokémon
    }

    // Contar la cantidad de pokémons presentes en la zona 2 del mapa
    int pokemonsPresentesZona2 = 0;
    for (int i = 0; i < mapa.FILAS / 2; ++i) {
        for (int j = mapa.COLUMNAS / 2; j < mapa.COLUMNAS; ++j) {
            if (mapa.casillas[i][j] == mapa.POKEMON) {
                pokemonsPresentesZona2++;
            }
        }
    }

    // Si hay menos de 18 pokémons en la zona 2, generar y colocar uno nuevo
    if (pokemonsPresentesZona2 < mapa.SECOND_AREA_POKE) {
        int nuevoPokemonX, nuevoPokemonY;
        do {
            nuevoPokemonX = rand() % (mapa.COLUMNAS / 2 - 1) + mapa.COLUMNAS / 2 - 1;
            nuevoPokemonY = rand() % (mapa.FILAS / 2 - 1) + 1;
        } while (mapa.casillas[nuevoPokemonY][nuevoPokemonX] != mapa.VACIO);

        mapa.casillas[nuevoPokemonY][nuevoPokemonX] = mapa.POKEMON; // Colocar el nuevo Pokémon
    }
}

bool Pokemons::CazarPokemon(int jugadorX, int jugadorY, Position playerPos, const Mapa& mapa, Pokemons& pokemons) {
    if (mapa.casillas[jugadorY - 1][jugadorX] == mapa.POKEMON || mapa.casillas[jugadorY + 1][jugadorX] == mapa.POKEMON
        || mapa.casillas[jugadorY][jugadorX + 1] == mapa.POKEMON || mapa.casillas[jugadorY][jugadorX - 1] == mapa.POKEMON) {

        if (mapa.casillas[jugadorY - 1][jugadorX] == mapa.POKEMON)
            mapa.casillas[jugadorY - 1][jugadorX] = mapa.VACIO;
        else if (mapa.casillas[jugadorY + 1][jugadorX] == mapa.POKEMON)
            mapa.casillas[jugadorY + 1][jugadorX] = mapa.VACIO;
        else if (mapa.casillas[jugadorY][jugadorX + 1] == mapa.POKEMON)
            mapa.casillas[jugadorY][jugadorX + 1] = mapa.VACIO;
        else if (mapa.casillas[jugadorY][jugadorX - 1] == mapa.POKEMON)
            mapa.casillas[jugadorY][jugadorX - 1] = mapa.VACIO;

        // Generar una nueva posición aleatoria para un Pokémon
        int nuevoPokemonX, nuevoPokemonY;
        do {
            nuevoPokemonX = rand() % (mapa.limiteMapa_x - 1) + 1;
            nuevoPokemonY = rand() % (mapa.FILAS / 2 - 1) + 1;
        } while (mapa.casillas[nuevoPokemonY][nuevoPokemonX] != mapa.VACIO);

        mapa.casillas[nuevoPokemonY][nuevoPokemonX] = mapa.POKEMON; // Colocar el nuevo Pokémon

        return true;
    }
    return false;
}
