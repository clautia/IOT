#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cb> 
#include <ctime> 
using namepspace 
int main() {
    ofstream outputFile("datos.txt");
    if (outputFile.is_open()) {
    tm currentDate = {};
    time_t now = time(nullptr);
    tm* dateInfo = localtime(&now); //marca de tiempo en una estructura de fecha

    //números aleatorios con una semilla
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 1; i <= 95; ++i) {
    // rango de '2023-01-01' a '2023-12-31'
    ostringstream dateStream;
    dateStream << 2023 << "-" << setw(2) << setfill('0') << 1 + rand() % 12 << "-" << setw(2) << setfill('0') << 1 + rand() % 31;
    string fecha = dateStream.str();

    // Genera datos ficticios entre 10.0 y 100.0
    double datos = 10.0 + (static_cast<double>(rand()) / RAND_MAX) * (100.0 - 10.0);

    int idMicro, idSenAct;
    string unidad;

    switch (i % 5) {
    case 0:
        idMicro = 1;
        idSenAct = 1;
        unidad = "Celsius";
        break;
    case 1:
        idMicro = 2;
        idSenAct = 2;
        unidad = "Kilopascals";
        break;
    case 2:
        idMicro = 3;
        idSenAct = 3;
        unidad = "Voltios";
        break;
    case 3:
        idMicro = 4;
        idSenAct = 4;
        unidad = "Porcentaje";
        break;
    case 4:
        idMicro = 5;
        idSenAct = 5;
        unidad = "Lumenes";
        break;
    }

    outputFile << "(" << idMicro << ", " << idSenAct << ", '" << fecha << "', " << datos << ", '" << unidad << "')," << endl;
    }

    outputFile.close();
    return 0;
}
