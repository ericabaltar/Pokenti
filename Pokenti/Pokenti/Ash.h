#pragma once
#include<iostream>
#include "windows.h"

struct AshPosition {
    int x;
    int y;
};
enum AshMovement { UP, DOWN, LEFT, RIGHT };
AshMovement currentMove;



struct Ash {
    int Pokimon;
    AshPosition pos;
    char AshLook;
    Ash() {
        this->Pokimon = 0;
        this->pos.x = 2;
        this->pos.y = 2;
        this->AshLook = '^';
    }
};

Ash ash;

void setAshPos() {
    switch (currentMove) {
    case UP:
        ash.pos.y--;
        ash.AshLook = '^';
        std::cout << "^" << std::endl;
        break;
    case DOWN:
        ash.pos.y++;
        ash.AshLook = 'v';
        std::cout << "v" << std::endl;
        break;
    case LEFT:
        ash.pos.x--;
        ash.AshLook = '<';
        std::cout << "<" << std::endl;
        break;
    case RIGHT:
        ash.pos.x++;
        ash.AshLook = '>';
        std::cout << ">" << std::endl;
        break;
    default:
        break;
    }
}

bool IsKeyPressed(int Key) {
    return GetAsyncKeyState(Key) & 0x8000;
}

void MoveAsh() {
    if (GetAsyncKeyState(VK_UP))
        currentMove = AshMovement::UP;
    else if (GetAsyncKeyState(VK_DOWN))
        currentMove = AshMovement::DOWN;
    else if (GetAsyncKeyState(VK_LEFT))
        currentMove = AshMovement::LEFT;
    else if (GetAsyncKeyState(VK_RIGHT))
        currentMove = AshMovement::RIGHT;

    setAshPos();
}


int main() {
    MoveAsh();
    bool IskeyPressed(int Key);


    return 0;
}