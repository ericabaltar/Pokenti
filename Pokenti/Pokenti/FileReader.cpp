#include "FileReader.h"

bool FileReader::ReadSettings(const std::string& filename, Settings& settings) {
    std::fstream myFile(filename);
    if (!myFile.is_open()) {
        ComprobarFichero();
        exit(1);
    }

    char aux;
    myFile >> settings.FILAS >> aux >> settings.COLUMNAS >> aux
        >> settings.FIRST_AREA_POKE >> aux >> settings.FIRST_AREA_MIN_POKE >> aux
        >> settings.SECOND_AREA_POKE >> aux >> settings.SECOND_AREA_MIN_POKE >> aux
        >> settings.PICACHU_DAMAGE >> aux
        >> settings.POKEMON_LIFE >> aux >> settings.MEWTWO_LIFE >> aux
        >> settings.MIN_TIME_MOVE_POKEMON >> aux >> settings.MAX_TIME_MOVE_POKEMON >> aux;

    myFile.close();
    return true;
}

void FileReader::ComprobarFichero() {
    std::cout << "Lamentablemente, ha surgido un inconveniente al intentar abrir el archivo 'config.txt'.\n"
        << "Por favor, tómese un momento para verificar que el archivo exista y contenga los datos necesarios.\n"
        << "Si el problema persiste, no dude en comunicarse con el administrador del sistema para recibir asistencia adicional.\n"
        << "¡Gracias por su comprensión y colaboración!\n";
}
