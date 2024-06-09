#include "Pokemons.h"
#include <cstdlib>
#include <chrono>
#include <thread>

void Pokemons::GestionarPokemons(Mapa& mapa, Settings& settings) {
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

    // Mover Pokémons según el tiempo establecido
    MoverPokemons(mapa, settings);
}

void Pokemons::MoverPokemons(Mapa& mapa, const Settings& settings) {
    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = now - lastMoveTime;

    int minTime = settings.MIN_TIME_MOVE_POKEMON;
    int maxTime = settings.MAX_TIME_MOVE_POKEMON;
    int waitTime = rand() % (maxTime - minTime + 1) + minTime;

    if (elapsed_seconds.count() >= waitTime) {
        for (int i = 0; i < mapa.FILAS; ++i) {
            for (int j = 0; j < mapa.COLUMNAS; ++j) {
                if (mapa.casillas[i][j] == mapa.POKEMON) {
                    int direction = rand() % 8;
                    int newX = j, newY = i;

                    switch (direction) {
                    case 0: // Arriba
                        newY -= 1;
                        break;
                    case 1: // Abajo
                        newY += 1;
                        break;
                    case 2: // Izquierda
                        newX -= 1;
                        break;
                    case 3: // Derecha
                        newX += 1;
                        break;
                    case 4: // Arriba-Izquierda
                        newX -= 1;
                        newY -= 1;
                        break;
                    case 5: // Arriba-Derecha
                        newX += 1;
                        newY -= 1;
                        break;
                    case 6: // Abajo-Izquierda
                        newX -= 1;
                        newY += 1;
                        break;
                    case 7: // Abajo-Derecha
                        newX += 1;
                        newY += 1;
                        break;
                    }

                    if (newX >= 0 && newX < mapa.COLUMNAS && newY >= 0 && newY < mapa.FILAS && mapa.casillas[newY][newX] == mapa.VACIO) {
                        mapa.casillas[newY][newX] = mapa.POKEMON;
                        mapa.casillas[i][j] = mapa.VACIO;
                    }
                }
            }
        }
        lastMoveTime = std::chrono::system_clock::now();
    }
}

// Los métodos restantes se mantienen sin cambios

bool Pokemons::GestionarMewtwo(int jugadorX, int jugadorY, const Mapa& mapa, Settings& settings) {
    static bool mewtwoAparecido = false; // Variable estática para controlar si Mewtwo ya apareció
    int mewtwoX = 52;
    int mewtwoY = 37;
    if (!mewtwoAparecido) { // Verificar si Mewtwo no ha aparecido todavía


        mapa.casillas[mewtwoY][mewtwoX] = mapa.MEWTWO;
        settings.MEWTWO_LIFE = settings.MEWTWO_LIFE;
        mewtwoAparecido = true; // Marcar que Mewtwo ha aparecido
        return true; // Mewtwo apareció
    }
    if (GetAsyncKeyState(VK_SPACE)&&((jugadorX == mewtwoX && (jugadorY == mewtwoY - 1 || jugadorY == mewtwoY + 1)) ||
        (jugadorY == mewtwoY && (jugadorX == mewtwoX - 1 || jugadorX == mewtwoX + 1))))
    {

        mapa.casillas[mewtwoY][mewtwoX] = mapa.VACIO;


        

        return true;
    }
    return false;
}
bool Pokemons::CazarPokemon(int jugadorX, int jugadorY, Position playerPos, const Mapa& mapa, Pokemons& pokemons, Ash& ash, Settings& settings) {
    if (GetAsyncKeyState(VK_SPACE) && (mapa.casillas[jugadorY - 1][jugadorX] == mapa.POKEMON || mapa.casillas[jugadorY + 1][jugadorX] == mapa.POKEMON
        || mapa.casillas[jugadorY][jugadorX + 1] == mapa.POKEMON || mapa.casillas[jugadorY][jugadorX - 1] == mapa.POKEMON)) {

        if (mapa.casillas[jugadorY - 1][jugadorX] == mapa.POKEMON)
            mapa.casillas[jugadorY - 1][jugadorX] = mapa.VACIO;
        else if (mapa.casillas[jugadorY + 1][jugadorX] == mapa.POKEMON)
            mapa.casillas[jugadorY + 1][jugadorX] = mapa.VACIO;
        else if (mapa.casillas[jugadorY][jugadorX + 1] == mapa.POKEMON)
            mapa.casillas[jugadorY][jugadorX + 1] = mapa.VACIO;
        else if (mapa.casillas[jugadorY][jugadorX - 1] == mapa.POKEMON)
            mapa.casillas[jugadorY][jugadorX - 1] = mapa.VACIO;

        ash.Pokimon +=1;

        if (GestionarMewtwo(jugadorX, jugadorY, mapa, settings)) {
            return true; // Se interactuó con Mewtwo
        }


        //Erica la parte del combate si la puedes hacer aqui mejor sino cambia esta funcion a tu gusto






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


