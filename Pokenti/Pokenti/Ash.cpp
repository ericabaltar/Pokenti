#include "Ash.h"


Ash::Ash() {
    Pokimon = 0;
    PokeBall = 0;
    pos.x = this->prevPos.x = 2;
    pos.y = this->prevPos.y = 2;
    AshLook = '^';
    currentMove = AshMovement::NONE;
}

void Ash::SetAshPos(int mapBorderX, int mapBorderY) {
    prevPos = pos;
    switch (currentMove) {
    case AshMovement::UP: {
        AshLook = '^';
        if (pos.y - 1 <= 0) {
            currentMove = AshMovement::NONE;
            return;
        }
        pos.y--;
    } break;
    case AshMovement::DOWN: {
        AshLook = 'v';
        if (pos.y + 1 > mapBorderY - 2) {
            currentMove = AshMovement::NONE;
            return;
        }
        pos.y++;
    } break;
    case AshMovement::LEFT: {
        AshLook = '<';
        if (pos.x - 1 <= 0) {
            currentMove = AshMovement::NONE;
            return;
        }
        pos.x--;
    } break;
    case AshMovement::RIGHT: {
        AshLook = '>';
        if (pos.x + 1 > mapBorderX - 2) {
            currentMove = AshMovement::NONE;
            return;
        }
        pos.x++;
    } break;
    default:
        break;
    }
    currentMove = AshMovement::NONE;
}

void Ash::MoveAsh(int mapBorderX, int mapBorderY, Mapa& mapa, Pokemons& pokemons, Ash& ash, Settings& settings) {
    if (GetAsyncKeyState(VK_SPACE))
        pokemons.CazarPokemon(pos.x, pos.y, pos, mapa, pokemons, ash, settings);
    else if (GetAsyncKeyState(VK_UP) && (mapa.casillas[pos.y - 1][pos.x] != Casilla::POKEMON && mapa.casillas[pos.y - 1][pos.x] != Casilla::MEWTWO && mapa.casillas[pos.y - 1][pos.x] != Casilla::SEPARADOR))
        currentMove = AshMovement::UP;
    else if (GetAsyncKeyState(VK_DOWN) && (mapa.casillas[pos.y + 1][pos.x] != Casilla::POKEMON && mapa.casillas[pos.y + 1][pos.x] != Casilla::MEWTWO && mapa.casillas[pos.y + 1][pos.x] != Casilla::SEPARADOR))
        currentMove = AshMovement::DOWN;
    else if (GetAsyncKeyState(VK_LEFT) && (mapa.casillas[pos.y][pos.x - 1] != Casilla::POKEMON && mapa.casillas[pos.y][pos.x - 1] != Casilla::MEWTWO && mapa.casillas[pos.y][pos.x - 1] != Casilla::SEPARADOR))
        currentMove = AshMovement::LEFT;
    else if (GetAsyncKeyState(VK_RIGHT) && (mapa.casillas[pos.y][pos.x + 1] != Casilla::POKEMON && mapa.casillas[pos.y][pos.x + 1] != Casilla::MEWTWO && mapa.casillas[pos.y][pos.x + 1] != Casilla::SEPARADOR))
        currentMove = AshMovement::RIGHT;

    SetAshPos(mapBorderX, mapBorderY);
}




