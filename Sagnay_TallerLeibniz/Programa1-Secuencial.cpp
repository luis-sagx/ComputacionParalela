#include <iostream>
using namespace std;

int main() {
    int numItera;
    double respuesta = 0.0;

    cout << "Programa con la Serie de Leibniz Secuencial\n\n";
    cout << "Ingrese el numero de iteraciones para aproximacion: ";
    cin >> numItera;

    bool esIndicePar = true;

    for (long indice = 0; indice < numItera; indice++) {
        if (esIndicePar) {
            respuesta += 4.0 / (2.0 * indice + 1.0);
        } else {
            respuesta -= 4.0 / (2.0 * indice + 1.0);
        }
        esIndicePar = !esIndicePar;  // Alterna entre verdadero y falso
    }

    cout << "El valor de PI aproximado es: " << respuesta << endl;

    return 0;
}
