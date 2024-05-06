#pragma once
#include<iostream>
#include <Windows.h>
#include "Types.h"


struct Ash {
    int Pokimon;
    enum AshMovement { UP, DOWN, LEFT, RIGHT, NONE };
    AshMovement currentMove;
    Position pos;
    Position prevPos;
    char AshLook;
    Ash() {
        this->Pokimon = 0;
        this->pos.x = this->prevPos.x = 2;
        this->pos.y = this->prevPos.y = 2;
        this->AshLook = '^';
        this->currentMove = NONE;
    }

    void setAshPos(int mapBorderX, int mapBorderY) {
        prevPos = pos;
        switch (currentMove) {
 
        case UP: {
            AshLook = '^';
            if (pos.y - 1 <= 0)
            {
                //no puedo hacer el movimiento
                currentMove = NONE;
                return;
            }
            pos.y--;
        }
            break;
        case DOWN: {
            AshLook = 'v';
            if (pos.y + 1 > mapBorderY-2)
            {
                //no puedo hacer el movimiento
                currentMove = NONE;
                return;
            }
            pos.y++;
        }
            break;
        case LEFT: {
            AshLook = '<';
            if (pos.x - 1 <= 0)
            {
                //no puedo hacer el movimiento
                currentMove = NONE;
                return;
            }
            pos.x--;
        }
            break;
        case RIGHT: {
            AshLook = '>';
            if (pos.x + 1 > mapBorderX-2)
            {
                //no puedo hacer el movimiento
                currentMove = NONE;
                return;
            }
            pos.x++;
        }
            break;
        default:
            break;
        }
        currentMove = NONE;
    }
    void printAsh()
    {
        std::cout << AshLook << std::endl;
    }
    void MoveAsh(int mapBorderX, int mapBorderY) {
        if (GetAsyncKeyState(VK_UP))
            currentMove = AshMovement::UP;
        else if (GetAsyncKeyState(VK_DOWN))
            currentMove = AshMovement::DOWN;
        else if (GetAsyncKeyState(VK_LEFT))
            currentMove = AshMovement::LEFT;
        else if (GetAsyncKeyState(VK_RIGHT))
            currentMove = AshMovement::RIGHT;

        setAshPos(mapBorderX, mapBorderY);
    }
};



bool IsKeyPressed(int Key) {
    return GetAsyncKeyState(Key) & 0x8000;
}



