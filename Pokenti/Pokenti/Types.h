#pragma once

struct Position {
    int x;
    int y;
};

//int clamp(int min, int max, int value)
//{
//    if (max < min)
//    {
//        int aux = max;
//        max = min;
//        min = aux;
//    }
//
//    if (value >= min && value <= max)
//        return value;
//    else if (value < min)
//        return min;
//    else if (value > max)
//        return max;
//}