#include "Pokemons.h"
#include <thread>

bool Pokemons::mewtwoAparecido = false;

void Pokemons::GestionarPokemons(Mapa& mapa, Settings& settings)
{
    int pokemonsPresentesZona1 = 0;
    for (int i = 0; i < settings.FILAS / 2; ++i) {
        for (int j = 0; j < settings.COLUMNAS / 2; ++j) {
            if (mapa.casillas[i][j] == Casilla::POKEMON) {
                pokemonsPresentesZona1++;
            }
        }
    }

    if (pokemonsPresentesZona1 < settings.FIRST_AREA_POKE) {
        int nuevoPokemonX, nuevoPokemonY;
        do {
            nuevoPokemonX = rand() % (settings.COLUMNAS / 2 - 1) + 1;
            nuevoPokemonY = rand() % (settings.FILAS / 2 - 1) + 1;
        } while (mapa.casillas[nuevoPokemonY][nuevoPokemonX] != Casilla::VACIO);

        mapa.casillas[nuevoPokemonY][nuevoPokemonX] = Casilla::POKEMON;
    }

    int pokemonsPresentesZona2 = 0;
    for (int i = 0; i < settings.FILAS / 2; ++i) {
        for (int j = settings.COLUMNAS / 2; j < settings.COLUMNAS; ++j) {
            if (mapa.casillas[i][j] == Casilla::POKEMON) {
                pokemonsPresentesZona2++;
            }
        }
    }

    if (pokemonsPresentesZona2 < settings.SECOND_AREA_POKE) {
        int nuevoPokemonX, nuevoPokemonY;
        do {
            nuevoPokemonX = rand() % (settings.COLUMNAS / 2 - 1) + settings.COLUMNAS / 2 - 1;
            nuevoPokemonY = rand() % (settings.FILAS / 2 - 1) + 1;
        } while (mapa.casillas[nuevoPokemonY][nuevoPokemonX] != Casilla::VACIO);

        mapa.casillas[nuevoPokemonY][nuevoPokemonX] = Casilla::POKEMON;
    }

    MoverPokemons(mapa, settings);
}

void Pokemons::MoverPokemons(Mapa& mapa, Settings& settings)
{
    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = now - lastMoveTime;

    int minTime = settings.MIN_TIME_MOVE_POKEMON;
    int maxTime = settings.MAX_TIME_MOVE_POKEMON;
    int waitTime = rand() % (maxTime - minTime + 1) + minTime;

    if (elapsed_seconds.count() >= waitTime) {
        for (int i = 0; i < settings.FILAS; ++i) {
            for (int j = 0; j < settings.COLUMNAS; ++j) {
                if (mapa.casillas[i][j] == Casilla::POKEMON) {
                    int direction = rand() % 8;
                    int newX = j, newY = i;

                    switch (direction) {
                    case 0:
                        newY -= 1;
                        break;
                    case 1:
                        newY += 1;
                        break;
                    case 2:
                        newX -= 1;
                        break;
                    case 3:
                        newX += 1;
                        break;
                    case 4:
                        newX -= 1;
                        newY -= 1;
                        break;
                    case 5:
                        newX += 1;
                        newY -= 1;
                        break;
                    case 6:
                        newX -= 1;
                        newY += 1;
                        break;
                    case 7:
                        newX += 1;
                        newY += 1;
                        break;
                    }

                    if (i < settings.FILAS / 2 && j < settings.COLUMNAS / 2) {
                        if (newX >= 0 && newX < settings.COLUMNAS / 2 && newY >= 0 && newY < settings.FILAS / 2 && mapa.casillas[newY][newX] == Casilla::VACIO) {
                            mapa.casillas[newY][newX] = Casilla::POKEMON;
                            mapa.casillas[i][j] = Casilla::VACIO;
                        }
                    }
                    else if (i < settings.FILAS / 2 && j >= settings.COLUMNAS / 2) {

                        if (newX >= settings.COLUMNAS / 2 && newX < settings.COLUMNAS && newY >= 0 && newY < settings.FILAS / 2 && mapa.casillas[newY][newX] == Casilla::VACIO) {
                            mapa.casillas[newY][newX] = Casilla::POKEMON;
                            mapa.casillas[i][j] = Casilla::VACIO;
                        }
                    }
                }
            }
        }
        lastMoveTime = std::chrono::system_clock::now();
    }
}

bool Pokemons::GestionarMewtwo(int jugadorX, int jugadorY, const Mapa& mapa, Settings& settings)
{
    static bool mewtwoAparecido = false;
    int mewtwoX = 52;
    int mewtwoY = 37;
    if (!mewtwoAparecido) {

        mapa.casillas[mewtwoY][mewtwoX] = Casilla::MEWTWO; 
        mewtwoAparecido = true;
        return true;
    }

    return false;
}

bool Pokemons::EsMewtwo(int jugadorX, int jugadorY, const Mapa& mapa)
{
    return (mapa.casillas[jugadorY][jugadorX] == Casilla::MEWTWO ||
        (jugadorX == mewtwoX && (jugadorY == mewtwoY - 1 || jugadorY == mewtwoY + 1)) ||
        (jugadorY == mewtwoY && (jugadorX == mewtwoX - 1 || jugadorX == mewtwoX + 1)));
}

bool Pokemons::CazarPokemon(int jugadorX, int jugadorY, Position playerPos, const Mapa& mapa, Pokemons& pokemons, Ash& ash, Settings& settings)
{
    if (GetAsyncKeyState(VK_SPACE) &&
        (mapa.casillas[jugadorY - 1][jugadorX] == Casilla::POKEMON || mapa.casillas[jugadorY + 1][jugadorX] == Casilla::POKEMON ||
            mapa.casillas[jugadorY][jugadorX + 1] == Casilla::POKEMON || mapa.casillas[jugadorY][jugadorX - 1] == Casilla::POKEMON ||
            EsMewtwo(jugadorX, jugadorY, mapa))) {
        return true;
    }
    return false;
}

bool Pokemons::CapturarPokemon(int jugadorX, int jugadorY, const Mapa& mapa, Pokemons& pokemons, Ash& ash, Settings& settings)
{
    std::string mensaje;
    if (ash.PokeBall > 0) {
        ash.PokeBall--;
        const int probabilidad = 100 - settings.POKEMON_LIFE;
        const int probabilidadLegendaria = 100 - settings.MEWTWO_LIFE;
        const int randNum = rand() % 100;
        if (randNum < probabilidad) {
            std::cout << std::endl;
            std::cout << "Has capturado el Pokémon!\n";
            if (mapa.casillas[jugadorY - 1][jugadorX] == Casilla::POKEMON)
                mapa.casillas[jugadorY - 1][jugadorX] = Casilla::VACIO;
            else if (mapa.casillas[jugadorY + 1][jugadorX] == Casilla::POKEMON)
                mapa.casillas[jugadorY + 1][jugadorX] = Casilla::VACIO;
            else if (mapa.casillas[jugadorY][jugadorX + 1] == Casilla::POKEMON)
                mapa.casillas[jugadorY][jugadorX + 1] = Casilla::VACIO;
            else if (mapa.casillas[jugadorY][jugadorX - 1] == Casilla::POKEMON)
                mapa.casillas[jugadorY][jugadorX - 1] = Casilla::VACIO;

            ash.Pokimon += 1;

            int nuevoPokemonX, nuevoPokemonY;
            do {
                nuevoPokemonX = rand() % (settings.COLUMNAS - 1) + 1;
                nuevoPokemonY = rand() % (settings.FILAS / 2 - 1) + 1;
            } while (mapa.casillas[nuevoPokemonY][nuevoPokemonX] != Casilla::VACIO);

            mapa.casillas[nuevoPokemonY][nuevoPokemonX] = Casilla::POKEMON;

            return true;
        }
        else if(randNum < probabilidadLegendaria && EsMewtwo(jugadorX, jugadorY, mapa)) {
                std::cout << std::endl;
                std::cout << "Has capturado a Mewtwo!!!\n";

                mapa.casillas[mewtwoY][mewtwoX] = Casilla::VACIO;

            return true;
        }
             else {
            std::cout << std::endl;
            std::cout << "El Pokémon no fue capturado!\n";
            if (((jugadorX == mewtwoX && (jugadorY == mewtwoY - 1 || jugadorY == mewtwoY + 1)) ||
                (jugadorY == mewtwoY && (jugadorX == mewtwoX - 1 || jugadorX == mewtwoX + 1)))) {
                mapa.casillas[mewtwoY][mewtwoX] = Casilla::VACIO;
            }
            
        }
    }
    else {
        std::cout << std::endl;
        std::cout << "No tienes Pokeballs!" << std::endl;
        if (((jugadorX == mewtwoX && (jugadorY == mewtwoY - 1 || jugadorY == mewtwoY + 1)) ||
            (jugadorY == mewtwoY && (jugadorX == mewtwoX - 1 || jugadorX == mewtwoX + 1)))) {
            mapa.casillas[mewtwoY][mewtwoX] = Casilla::VACIO;
            return true;
        }
        
    }
    MostrarMensajeConRetardo(mensaje);
    return false;
}

bool Pokemons::AtacarPokemon(int jugadorX, int jugadorY, const Mapa& mapa, Pokemons& pokemons, Ash& ash, Settings& settings)
{
    std::string mensaje;
    
    if ((mapa.casillas[jugadorY - 1][jugadorX] == Casilla::POKEMON || mapa.casillas[jugadorY + 1][jugadorX] == Casilla::POKEMON
        || mapa.casillas[jugadorY][jugadorX + 1] == Casilla::POKEMON || mapa.casillas[jugadorY][jugadorX - 1] == Casilla::POKEMON)) {

        settings.POKEMON_LIFE -= settings.PICACHU_DAMAGE;
        std::cout << std::endl;
        std::cout << "Buen golpe, ahora tiene: " << settings.POKEMON_LIFE << "\n";
        std::cout << std::endl;
        std::cout << "Dano de Pikachu: " << settings.PICACHU_DAMAGE << "\n";

        if (settings.POKEMON_LIFE <= 0) {
            if (mapa.casillas[jugadorY - 1][jugadorX] == Casilla::POKEMON)
                mapa.casillas[jugadorY - 1][jugadorX] = Casilla::VACIO;
            else if (mapa.casillas[jugadorY + 1][jugadorX] == Casilla::POKEMON)
                mapa.casillas[jugadorY + 1][jugadorX] = Casilla::VACIO;
            else if (mapa.casillas[jugadorY][jugadorX + 1] == Casilla::POKEMON)
                mapa.casillas[jugadorY][jugadorX + 1] = Casilla::VACIO;
            else if (mapa.casillas[jugadorY][jugadorX - 1] == Casilla::POKEMON)
                mapa.casillas[jugadorY][jugadorX - 1] = Casilla::VACIO;

            int nuevoPokemonX, nuevoPokemonY;
            do {
                nuevoPokemonX = rand() % (settings.COLUMNAS - 1) + 1;
                nuevoPokemonY = rand() % (settings.FILAS / 2 - 1) + 1;
            } while (mapa.casillas[nuevoPokemonY][nuevoPokemonX] != Casilla::VACIO);

            mapa.casillas[nuevoPokemonY][nuevoPokemonX] = Casilla::POKEMON;

            return true;
        }
    }
    else if (EsMewtwo(jugadorX, jugadorY, mapa)) {

            settings.MEWTWO_LIFE -= settings.PICACHU_DAMAGE;
            std::cout << std::endl;
            std::cout << "Buen golpe, ahora tiene: " << settings.MEWTWO_LIFE << "\n";
            std::cout << std::endl;
            std::cout << "Dano de Pikachu: " << settings.PICACHU_DAMAGE << "\n";
            if (settings.MEWTWO_LIFE <= 0) {

                mapa.casillas[mewtwoY][mewtwoX] = Casilla::VACIO;

                 return true;
            }

         }
    MostrarMensajeConRetardo(mensaje);
    return false;
}

bool Pokemons::Huir(int jugadorX, int jugadorY, const Mapa& mapa)
{
    std::cout << std::endl;
    std::string mensaje = "Has huido!";
    MostrarMensajeConRetardo(mensaje);

    if(((jugadorX == mewtwoX && (jugadorY == mewtwoY - 1 || jugadorY == mewtwoY + 1)) ||
        (jugadorY == mewtwoY && (jugadorX == mewtwoX - 1 || jugadorX == mewtwoX + 1))))
        mapa.casillas[mewtwoY][mewtwoX] = Casilla::VACIO;

    return true;
}

std::string Pokemons::GetPokemonName(int jugadorX, int jugadorY, const Mapa& mapa)
{
    if (EsMewtwo(jugadorX, jugadorY, mapa)) {
        return "Mewtwo";
    }
    return GetRandomPokemonName();
}

std::string Pokemons::GetRandomPokemonName() {
    static bool initialized = false;
    if (!initialized) {
        srand(static_cast<unsigned int>(time(nullptr)));
        initialized = true;
    }

    std::vector<std::string> pokemonNames = {
        "Bulbasaur",
        "Charmander",
        "Squirtle",
        "Psyduck",
        "Jigglypuff",
        "Eevee"
    };

    int randomIndex = rand() % pokemonNames.size();
    return pokemonNames[randomIndex];
}

void Pokemons::MostrarMensajeConRetardo(const std::string& mensaje) {
    std::cout << mensaje << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "\033[2J\033[1;1H"; 
}

