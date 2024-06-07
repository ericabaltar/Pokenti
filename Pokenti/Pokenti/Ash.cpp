#include "Ash.h"
#include "mapa.h"
#include "Pokemons.h"

Ash::Ash() {
    Pokimon = 14;
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

void Ash::MoveAsh(int mapBorderX, int mapBorderY, Mapa& mapa, Pokemons& pokemons) {
    if (GetAsyncKeyState(VK_SPACE))
        pokemons.CazarPokemon(pos.x, pos.y, pos, mapa, pokemons);
    else if (GetAsyncKeyState(VK_UP))
        currentMove = AshMovement::UP;
    else if (GetAsyncKeyState(VK_DOWN))
        currentMove = AshMovement::DOWN;
    else if (GetAsyncKeyState(VK_LEFT))
        currentMove = AshMovement::LEFT;
    else if (GetAsyncKeyState(VK_RIGHT))
        currentMove = AshMovement::RIGHT;

    SetAshPos(mapBorderX, mapBorderY);
}

