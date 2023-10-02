#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstdlib> 
#include <ctime> 

int main() {
    std::ofstream outputFile("datos.txt");
    if (outputFile.is_open()) {
        std::tm currentDate = {};
        std::time_t now = std::time(nullptr);
        std::tm* dateInfo = std::localtime(&now); // Convierte la marca de tiempo en una estructura de fecha

        // Inicializa el generador de números aleatorios con una semilla
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        for (int i = 1; i <= 95; ++i) {
            // Genera una fecha aleatoria en el rango de '2023-01-01' a '2023-12-31'
            std::ostringstream dateStream;
            dateStream << 2023 << "-" << std::setw(2) << std::setfill('0') << 1 + rand() % 12 << "-" << std::setw(2) << std::setfill('0') << 1 + rand() % 31;
            std::string fecha = dateStream.str();

            // Genera datos ficticios entre 10.0 y 100.0
            double datos = 10.0 + (static_cast<double>(std::rand()) / RAND_MAX) * (100.0 - 10.0);

            int idMicro, idSenAct;
            std::string unidad;

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

            outputFile << "(" << idMicro << ", " << idSenAct << ", '" << fecha << "', " << datos << ", '" << unidad << "')," << std::endl;
        }

        outputFile.close();
        std::cout << "Datos generados y guardados en 'datos.txt'" << std::endl;
    } else {
        std::cerr << "No se pudo abrir el archivo 'datos.txt'" << std::endl;
    }

    return 0;
}
