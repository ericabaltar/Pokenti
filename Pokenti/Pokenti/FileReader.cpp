#include "FileReader.h"

bool FileReader::ReadSettings(const std::string& filename, Settings& settings) {
    
        std::fstream myFile(filename);
        if (!myFile.is_open()) {
            ComprobarFichero();
            exit(1);
        }
        char aux;
        myFile >> settings.FILAS >> aux >> settings.COLUMNAS >> aux;
        myFile >> settings.FIRST_AREA_POKE >> aux >> settings.FIRST_AREA_MIN_POKE >> aux;
        myFile >> settings.SECOND_AREA_POKE >> aux >> settings.SECOND_AREA_MIN_POKE >> aux;
        myFile >> settings.ERICACHU_DAMAGE >> aux;
        myFile >> settings.POKEMON_LIFE >> aux >> settings.MEWTWO_LIFE >> aux;
        myFile >> settings.MIN_TIME_MOVE_POKEMON >> aux >> settings.MAX_TIME_MOVE_POKEMON >> aux;

        myFile.close();
   
    return true;
}

void FileReader::ComprobarFichero() {
    std::cout << "Lamentablemente, ha surgido un inconveniente al intentar abrir el archivo 'config.txt'.\n";
    std::cout << "Por favor, tómese un momento para verificar que el archivo exista y contenga los datos necesarios.\n";
    std::cout << "Si el problema persiste, no dude en comunicarse con el administrador del sistema para recibir asistencia adicional.\n";
    std::cout << "ˇGracias por su comprensión y colaboración!\n";
}
