#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    int numHilos = 4, idHilo = 0;
    omp_set_num_threads(numHilos);

    long numItera;
    double respuesta;

    double SumParciales[numHilos];

    cout << "Programa con las series de Leibniz Paralelo\n\n";
    cout << "Ingrese el numero de iteraciones: ";
    cin >> numItera;

    #pragma omp parallel private(idHilo) shared(SumParciales)
    {
        idHilo = omp_get_thread_num();
        SumParciales[idHilo] = 0.0;
        for (long indice = idHilo; indice <= numItera; indice += numHilos) {
            if (indice % 2 == 0) {
                SumParciales[idHilo] += 4.0 / (2.0 * indice + 1.0);  // Serie Leibniz
            } else {
                SumParciales[idHilo] -= 4.0 / (2.0 * indice + 1.0);  // Serie Leibniz
            }
            printf("Hilo %d, %f\n", idHilo, SumParciales[idHilo]);
        }
    }

    respuesta = 0.0;
    for (int i = 0; i < numHilos; i++) {
        respuesta += SumParciales[i];
    }

    cout << "El valor aproximado de pi es: " << respuesta << endl;
    return 0;
}
