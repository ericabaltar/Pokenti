#include "mapa.h"
#include "Ash.h"

int main() {
    Mapa mapa;
    Ash ash;
    
    while (true) {
        ash.MoveAsh(mapa.COLUMNAS/2 + 1, mapa.FILAS/2 + 1);
        std::cout << ash.pos.x << " " << ash.pos.y;
        std::cout << std::endl;
        mapa.casillas[ash.prevPos.y][ash.prevPos.x] = mapa.VACIO;
        mapa.casillas[ash.pos.y][ash.pos.x] = ash.AshLook;
        mapa.PintarVista(ash.pos,mapa.COLUMNAS/2, mapa.FILAS/2);

        Sleep(150);
        system("cls");
    }

    

    return 0;
}