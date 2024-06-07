#include "Ash.h"
#include "mapa.h"
#include "Pokeball.h"
#include "Pokemons.h"
#include "FileReader.h"

const int MAX_NUM_FPS = 15;
int main() {
    // Inicializar la semilla de generación aleatoria
    srand(time(NULL));

    Settings settings;
    FileReader::ReadSettings("config.txt", settings);
    Mapa mapa(settings);
    Ash ash;
    PokeBall pokeball;
    Pokemons pokemons;
 

    bool bosqueBloqueado = true;
    bool cuevaBloqueado = true;
    
    while (true) {
        
        //if (!FileReader::ReadSettings("config.txt", settings)) {
          //  return 1; // Salir del programa si no se puede leer la configuración
        //}
        ash.MoveAsh(mapa.limiteMov_X, mapa.limiteMov_Y, mapa, pokemons);
        mapa.casillas[ash.prevPos.y][ash.prevPos.x] = mapa.VACIO;
        mapa.casillas[ash.pos.y][ash.pos.x] = ash.AshLook;

        pokemons.GestionarPokemons(mapa);
        mapa.GestionarPokeBalls();
        //Comprobar si se caza un pokemon
        if (pokemons.CazarPokemon(ash.pos.x, ash.pos.y, ash.pos, mapa, pokemons))
        {
            ash.Pokimon += 1;
        }

        //Comprobar si se consigue una PokeBall
        if (mapa.RecogerPokeball(ash.pos.x, ash.pos.y))
        {
            ash.PokeBall += 1;
        }

        //desbloqueo zona 2
        if (ash.Pokimon >= mapa.FIRST_AREA_MIN_POKE && bosqueBloqueado)
        {
            mapa.UnlockBosque();
            bosqueBloqueado = false;
        }
        
        //desbloqueo zona 3
        if (ash.Pokimon >= mapa.SECOND_AREA_MIN_POKE && cuevaBloqueado)
        {
            mapa.UnlockCueva();
            bosqueBloqueado = false;
        }
         
        //mapa.PintarTodo();
        mapa.PintarVista(ash.pos);

        std::cout << std::endl << std::endl;
        std::cout << ash.pos.x << " " << ash.pos.y;
        std::cout << std::endl;
        std::cout << "Current Pokimons: " << ash.Pokimon;
        std::cout << "Current Pokimons: " << settings.SECOND_AREA_POKE;
        std::cout << std::endl;
        Sleep(1000/MAX_NUM_FPS);
        system("cls");
    }



    return 0;
}