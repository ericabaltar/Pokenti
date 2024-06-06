#include "Ash.h"
#include "mapa.h"

int main() {
    // Inicializar la semilla de generación aleatoria
    srand(time(NULL));

    Mapa mapa;
    Ash ash;

    bool bosqueBloqueado = true;
    bool cuevaBloqueado = true;

    while (true) {
        ash.MoveAsh(mapa.limiteMov_X, mapa.limiteMov_Y, mapa);
        mapa.casillas[ash.prevPos.y][ash.prevPos.x] = mapa.VACIO;
        mapa.casillas[ash.pos.y][ash.pos.x] = ash.AshLook;

        mapa.GestionarPokemons();
        mapa.GestionarPokeBalls();
        //Comprobar si se caza un pokemon
        if (mapa.CazarPokemon(ash.pos.x, ash.pos.y,ash.pos))
        {
            ash.Pokimon += 1;
        }

        //Comprobar si se consigue una PokeBall
        if (mapa.RecogerPokeball(ash.pos.x, ash.pos.y))
        {
            ash.PokeBall += 1;
        }

        //desbloqueo zona 2
        if (ash.Pokimon >= mapa.FIRST_AREA_MIN_POK && bosqueBloqueado)
        {
            mapa.UnlockBosque();
            bosqueBloqueado = false;
        }
        
        //desbloqueo zona 3
        if (ash.Pokimon >= mapa.SECOND_AREA_MIN_POK && cuevaBloqueado)
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
        std::cout << std::endl;
        Sleep(30);
        system("cls");
    }



    return 0;
}