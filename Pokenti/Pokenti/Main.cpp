#include "Ash.h"
#include "Mapa.h"
#include "Pokeball.h"
#include "Pokemons.h"
#include "FileReader.h"
#include <conio.h>


const int MAX_NUM_FPS = 15;

enum class GameScene
{
    SPLASHSCREEN,

    MAINMENU,

    GAMEPLAY,

    GAMEOVER
};

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void DrawStaticInterface()
{
    system("cls");
    
    gotoxy(0, 0);
    std::cout << "Pokemons capturados: [N]   Pokeballs: [N]";
    gotoxy(0, 1);
    std::cout << "[Nombre Ciudad]";
    gotoxy(0, 23); 
    std::cout << "[Nombre de enemigo] [Nivel de salud]";
    gotoxy(0, 24);
    std::cout << "ATACAR   CAPTURAR   HUIR";
}

void UpdateGameStats(const Ash& ash)
{
    // Update the stats at the top
    gotoxy(0, 0); // Position to update Pokemons count
    std::cout <<" Pokemons capturados: "<< ash.Pokimon; 
    

    gotoxy(40, 0);
    std::cout <<"Pokeballs: " << ash.PokeBall;
}

void ShowMainMenu(GameScene& currentScene) {
    int selectedOption = 0;
    bool selectionMade = false;

    while (!selectionMade) {
        system("cls");
        std::cout << R"(
___  ___      _        ___  ___                 
|  \/  |     (_)       |  \/  |                 
| .  . | __ _ _ _ __   | .  . | ___ _ __  _   _ 
| |\/| |/ _` | | '_ \  | |\/| |/ _ \ '_ \| | | |
| |  | | (_| | | | | | | |  | |  __/ | | | |_| |
\_|  |_/\__,_|_|_| |_| \_|  |_/\___|_| |_|\__,_|
                                                                                                                                                     
)";

        std::cout << (selectedOption == 0 ? "> " : "  ") << "1. Play\n";
        std::cout << (selectedOption == 1 ? "> " : "  ") << "2. Exit\n";
        std::cout << "\033[36m";
        std::cout << R"(
                                                                     `;,;.;,;.;.'
                                                                      ..:;:;::;: 
                                                                ..--''' '' ' ' '''--.  
                                                              /' .   .'        '.   .`\
                                                             | /    /            \   '.|
                                                             | |   :             :    :|
                                                           .'| |   :             :    :|
                                                         ,: /\ \.._\ __..===..__/_../ /`.
                                                        |'' |  :.|  `'          `'  |.'  ::.
                                                        |   |  ''|    :'';          | ,  `''\
                                                        |.:  \/  | /'-.`'   ':'.-'\ |  \,   |
                                                        | '  /  /  | / |...   | \ |  |  |';'|
                                                         \ _ |:.|  |_\_|`.'   |_/_|  |.:| _ |
                                                        /,.,.|' \__       . .      __/ '|.,.,\
                                                             | ':`.`----._____.---'.'   |
                                                               \   `:"""-------'""' |   |
                                                               ',-,-',             .'-=,=,)";
        std::cout << "\033[0m";
        switch (_getch()) {
        case 72:
            selectedOption = (selectedOption - 1 + 2) % 2;
            break;
        case 80:
            selectedOption = (selectedOption + 1) % 2;
            break;
        case 13:
            if (selectedOption == 0) {
                currentScene = GameScene::GAMEPLAY;
            }
            else {
                exit(0);
            }
            selectionMade = true;
            break;
        }
    }
}
int main() {

    srand(time(NULL));

    GameScene currentScene = GameScene::SPLASHSCREEN;

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

    DrawStaticInterface();
    
    while (!gameIsOver) {

        switch (currentScene)
        {
        case GameScene::SPLASHSCREEN:
        {
            system("cls");
           std::cout << "\033[38;5;208m";
           std::cout << R"(                    
                                ___.
                              L._, \
               _.,              <  <\                _
             ,' '             `.   | \            ( `
          ../, `.            `  |    .\`.           \ \_
         ,' ,..  .           _.,'    ||\l            )  '".
        , ,'   \           ,'.-.`-._,'  |           .  _._`.
      ,' /      \ \        `' ' `--/   | \          / /   ..\
    .'  /        \ .         |\__ - _ ,'` `        / /     `.`.
    |  '          ..         `-...-"  |  `-'      / /        . `.
    | /           |L__           |    |          / /          `. `.
   , /            .   .          |    |         / /             ` `
  / /          ,. ,`._ `-_       |    |  _   ,-' /               ` \
 / .           \"`_/. `-_ \_,.  ,'    +-' `-'  _,        ..,-.    \`.
.  '         .-f    ,'   `    '.       \__.---'     _   .'   '     \ \
' /          `.'    l     .' /          \..      ,_|/   `.  ,'`     L`
|'      _.-""` `.    \ _,'  `            \ `.___`.'"`-.  , |   |    | \
||    ,'      `. `.   '       _,...._        `  |    `/ '  |   '     .|
||  ,'          `. ;.,.---' ,'       `.   `.. `-'  .-' /_ .'    ;_   ||
|| '              V      / /           `   | `   ,'   ,' '.    !  `. ||
||/            _,-------7 '              . |  `-'    l         /    `||
. |          ,' .-   ,' ||               | .-.        `.      .'     ||
 `'        ,'    `".'    |               |    `.        '. -.'       `' 
          /      ,'      |               |,'    \-.._,.'/'
          .     /        .               .       \    .''                                                               
        .`.    |         `.             /         :_,'.'
          \ `...\   _     ,'-.        .'         /_.-'
           `-.__ `,  `'   .  _.>----''.  _  __  /
                .'        /"'          |  "'   '_
               /_|.-'\ ,".             '.'`__'-( \
                 / ,"'"\,'               `/  `-.|"                       
                                                                         )";
           std::cout << "\033[0m";
           std::cout << R"(
                                                              ____       _    _____       _   _ 
                                                             |  _ \ ___ | | _| ____|_ __ | |_(_)
                                                             | |_) / _ \| |/ /  _| | '_ \| __| |
                                                             |  __/ (_) |   <| |___| | | | |_| |
                                                             |_|   \___/|_|\_\_____|_| |_|\__|_|
                                    
)";



            Sleep(3000); 
            currentScene = GameScene::MAINMENU;
        }
            break;
        case GameScene::MAINMENU:
        {
            ShowMainMenu(currentScene);
        }
            break;
        case GameScene::GAMEPLAY:
        {
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            ash.MoveAsh(mapa.limiteMov_X, mapa.limiteMov_Y, mapa, pokemons, ash, settings);
            mapa.casillas[ash.prevPos.y][ash.prevPos.x] = static_cast<Casilla>(Casilla::VACIO);
            mapa.casillas[ash.pos.y][ash.pos.x] = static_cast<Casilla>(ash.AshLook);

            pokemons.GestionarPokemons(mapa, settings);
            pokeball.GestionarPokeBalls(mapa, settings);
            pokeball.VerificarPokeball(ash.pos.x, ash.pos.y, mapa, ash.pos, ash, settings);
            pokemons.GestionarMewtwo(ash.pos.x, ash.pos.y, mapa, settings);

            if (ash.Pokimon >= settings.FIRST_AREA_MIN_POKE && bosqueBloqueado)
            {
                mapa.UnlockBosque();
                bosqueBloqueado = false;
            }


           if (ash.Pokimon >= settings.SECOND_AREA_MIN_POKE && cuevaBloqueado)
           {
              mapa.UnlockCueva();
              bosqueBloqueado = false;
           }

            //mapa.PintarTodo();
            mapa.PintarVista(ash.pos);
            UpdateGameStats(ash);


            Sleep(1000 / MAX_NUM_FPS);
            system("cls");
        }
            break;
        case GameScene::GAMEOVER:
        {
            std::cout << "\033[38;5;153m";
            std::cout << R"(             
               _,........__                                          
            ,-'            "`-.                                      
          ,'                   `-.                                   
        ,'                        \                                  
      ,'                           .                                 
      .'\               ,"".       `                                 
     ._.'|             / |  `       \                                
     |   |            `-.'  ||       `.                              
     |   |            '-._,'||       | \                             
     .`.,'             `..,'.'       , |`-.                          
     l                       .'`.  _/  |   `.                        
     `-.._'-   ,          _ _'   -" \  .     `                       
`."""""'-.`-...,---------','         `. `....__.                     
.'        `"-..___      __,'\          \  \     \                    
\_ .          |   `""""'    `.           . \     \                   
  `.          |              `.          |  .     L                  
    `.        |`--...________.'.        j   |     |                  
      `._    .'      |          `.     .|   ,     |                  
         `--,\       .            `7""' |  ,      |                  
            ` `      `            /     |  |      |    _,-'"""`-.    
             \ `.     .          /      |  '      |  ,'          `.  
              \  v.__  .        '       .   \    /| /              \ 
               \/    `""\"""""""`.       \   \  /.''                |
                `        .        `._ ___,j.  `/ .-       ,---.     |
                ,`-.      \         ."     `.  |/        j     `    |
               /    `.     \       /         \ /         |     /    j
              |       `-.   7-.._ .          |"          '         / 
              |          `./_    `|          |            .     _,'  
              `.           / `----|          |-............`---'     
                \          \      |          |                       
               ,'           )     `.         |                       
                7____,,..--'      /          |                       
                                  `---.__,--.'                     )";
            std::cout << "\033[0m";
            std::cout << R"(
                                                       _____                       ____                 
                                                      / ____|                     / __ \                
                                                     | |  __  __ _ _ __ ___   ___| |  | |_   _____ _ __ 
                                                     | | |_ |/ _` | '_ ` _ \ / _ \ |  | \ \ / / _ \ '__|
                                                     | |__| | (_| | | | | | |  __/ |__| |\ V /  __/ |   
                                                      \_____|\__,_|_| |_| |_|\___|\____/  \_/ \___|_|   
                                                    
                                                    
)";
            Sleep(5000); 
            currentScene = GameScene::MAINMENU;
        }
            break;
        default:
            break;
        }

        
    }



    return 0;
}