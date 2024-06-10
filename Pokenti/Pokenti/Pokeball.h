#pragma once
#include "Mapa.h"
#include "Ash.h"
#include "FileReader.h"

struct Ash;
struct Mapa;

class PokeBall {
public:

    PokeBall();

     void GestionarPokeBalls(Mapa& mapa, Settings& settings);
     bool VerificarPokeball(int jugadorX, int jugadorY, Mapa& mapa, Position ashPos, Ash& ash, Settings& settings);

private:

    int PokeBallsPresentesZona1;
    int PokeBallsPresentesZona2;
    int nuevaPokeBallX;
    int nuevaPokeBallY;

    //Hay que arreglar la cogida de la PokeBall

};
