#include "Ash.h"
#include "mapa.h"
#include "Pokeball.h"
#include "Pokemons.h"
#include "FileReader.h"

const int MAX_NUM_FPS = 15;
int main() {
    // Inicializar la semilla de generaci�n aleatoria
    srand(time(NULL));

    enum class GameScene
    {
        SPLASHSCREEN,
        MAINMENU,
        GAMEPLAY,
        GAMEOVER
    } currentScene;
    currentScene = GameScene::SPLASHSCREEN;

    Settings settings;
    FileReader::ReadSettings("config.txt", settings);
    Mapa mapa(settings);
    Ash ash;
    PokeBall pokeball;
    Pokemons pokemons;
 
    bool gameIsOver = false;
    float splashScreenTimer = 0.f;

    bool bosqueBloqueado = true;
    bool cuevaBloqueado = true;
    
    while (!gameIsOver) {

        switch (currentScene)
        {
        case GameScene::SPLASHSCREEN:
        {
            system("cls");
            std::cout << "la splash screen xd";
            splashScreenTimer += 5000000 / MAX_NUM_FPS;
            if (splashScreenTimer >= 54000000)
                currentScene = GameScene::GAMEPLAY;
        }
            break;
        case GameScene::MAINMENU:
        {
            //El menu
        }
            break;
        case GameScene::GAMEPLAY:
        {
            ash.MoveAsh(mapa.limiteMov_X, mapa.limiteMov_Y, mapa, pokemons, ash, settings);
            mapa.casillas[ash.prevPos.y][ash.prevPos.x] = mapa.VACIO;
            mapa.casillas[ash.pos.y][ash.pos.x] = ash.AshLook;

            pokemons.GestionarPokemons(mapa);
            pokeball.GestionarPokeBalls(mapa);
            pokeball.VerificarPokeball(ash.pos.x, ash.pos.y, mapa, ash.pos, ash);
            pokemons.GestionarMewtwo(ash.pos.x, ash.pos.y, mapa, settings);
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
            std::cout << "Current Pokimons: " << ash.PokeBall;
            std::cout << std::endl;
            Sleep(1000 / MAX_NUM_FPS);
            system("cls");
        }
            break;
        case GameScene::GAMEOVER:
        {

        }
            break;
        default:
            break;
        }

        
    }



    return 0;
}