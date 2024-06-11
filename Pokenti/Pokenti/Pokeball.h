#pragma once
#include "Mapa.h"
#include "Ash.h"
#include "FileReader.h"

class Ash;
class Mapa;

class PokeBall {
public:

    PokeBall();


     void GestionarPokeBalls(int jugadorX, int jugadorY, Mapa& mapa, Ash& ash, Settings& settings);
     bool VerificarPokeball(int jugadorX, int jugadorY, Mapa& mapa, Position ashPos, Ash& ash, Settings& settings);

private:

    int iteracion;
    int iteracionZona2;
    int PokeBallsPresentesZona1;
    int PokeBallsPresentesZona2;
    int nuevaPokeBallX;
    int nuevaPokeBallY;

    //Hay que arreglar la cogida de la PokeBall

};
