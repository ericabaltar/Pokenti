#pragma once
#include<iostream>
#include "windows.h"

struct AshPosition {
    int x;
    int y;
};



struct Ash {
    int Pokimon;
    enum AshMovement { UP, DOWN, LEFT, RIGHT, NONE };
    AshMovement currentMove;
    AshPosition pos;
    AshPosition prevPos;
    char AshLook;
    Ash() {
        this->Pokimon = 0;
        this->pos.x = this->prevPos.x = 2;
        this->pos.y = this->prevPos.y = 2;
        this->AshLook = '^';
        this->currentMove = NONE;
    }

    void setAshPos() {
        prevPos = pos;
        switch (currentMove) {
        case UP:
            pos.y--;
            AshLook = '^';
            break;
        case DOWN:
            pos.y++;
            AshLook = 'v';
            break;
        case LEFT:
            pos.x--;
            AshLook = '<';
            break;
        case RIGHT:
            pos.x++;
            AshLook = '>';
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
};



bool IsKeyPressed(int Key) {
    return GetAsyncKeyState(Key) & 0x8000;
}



