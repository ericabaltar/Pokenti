#pragma once
#include <iostream>
#include <fstream>

struct Settings {
//private:
    int FILAS;
    int COLUMNAS;
    int FIRST_AREA_POKE;
    int FIRST_AREA_MIN_POKE;
    int SECOND_AREA_POKE;
    int SECOND_AREA_MIN_POKE;
    int ERICACHU_DAMAGE;
    int POKEMON_LIFE;
    int MEWTWO_LIFE;
    int MIN_TIME_MOVE_POKEMON;
    int MAX_TIME_MOVE_POKEMON;

};

class FileReader {
public:

    static bool ReadSettings(const std::string& filename, Settings& settings);

private:

    static void ComprobarFichero();

};
