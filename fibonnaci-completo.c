#include <omp.h>
#include <sys/time.h>
#include <stdio.h>
#include <math.h>

double TR, TP, TS;
unsigned long int Pfibonacci(unsigned long int numero);
unsigned long int Rfibonacci(unsigned long int numero);
unsigned long int Sfibonacci(unsigned long posicion, int imprimir);

int main() {
    unsigned long int numero;
    struct timeval t0, t1;
    double tiempoP = 0;

    printf("Programa Fibonacci (Simple / Recursivo / Paralelo)\n\n");
    printf("Ingrese un numero: ");
    scanf("%ld", &numero);

    // Proceso simple
    gettimeofday(&t0, 0);
    printf("(S) El numero %ld de la sucesion de Fibonacci es %ld\n", numero, Sfibonacci(numero, 0));
    gettimeofday(&t1, 0);
    tiempoP = (t1.tv_sec - t0.tv_sec) * 1.0f + (t1.tv_usec - t0.tv_usec) / 1000000.0f;
    TS = tiempoP;
    printf("\tTiempo de ejecucion   (simple): %.3lf ms\n", TS * 1000);

    // Proceso recursivo
    gettimeofday(&t0, 0);
    printf("(R) El numero %ld de la sucesion de Fibonacci es %ld\n", numero, Rfibonacci(numero));
    gettimeofday(&t1, 0);
    tiempoP = (t1.tv_sec - t0.tv_sec) * 1.0f + (t1.tv_usec - t0.tv_usec) / 1000000.0f;
    TR = tiempoP;
    printf("\tTiempo de ejecucion (recursivo): %.3lf ms\n", TR * 1000);

    // Proceso paralelo
    gettimeofday(&t0, 0);
    printf("(P) El numero %ld de la sucesion de Fibonacci es %ld\n", numero, Pfibonacci(numero));
    gettimeofday(&t1, 0);
    tiempoP = (t1.tv_sec - t0.tv_sec) * 1.0f + (t1.tv_usec - t0.tv_usec) / 1000000.0f;
    TP = tiempoP;
    printf("\tTiempo de ejecucion (paralelo): %.3lf ms\n", TP * 1000);

    return 0;
}

unsigned long Sfibonacci(unsigned long posicion, int imprimir) {
    unsigned long siguiente = 1, actual = 0, temporal = 0;
    for (unsigned long x = 1; x <= posicion; x++) {
        if (imprimir)
            printf("%ld, ", actual);
        temporal = actual;
        actual = siguiente;
        siguiente = siguiente + temporal;
    }
    if (imprimir)
        printf("%ld", actual);
    return actual;
}

// Función recursiva de Fibonacci
unsigned long Rfibonacci(unsigned long int numero) {
    if (numero == 1 || numero == 2){
        return 1;
    } else{
        return Rfibonacci(numero - 1) + Rfibonacci(numero - 2);
    }
}

// Función paralela de Fibonacci
unsigned long Pfibonacci(unsigned long numero) {
    int numeroHilos = 5;
    unsigned long respuesta = 0;
    omp_set_num_threads(numeroHilos);

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            long subrespuesta = Rfibonacci(numero - 2);
            printf("\tEl hilo %d descubrio que Fibonacci(%ld) = %ld\n", omp_get_thread_num(), numero - 2, subrespuesta);
            #pragma omp atomic
                respuesta += subrespuesta;
        }

        #pragma omp section
        {
            long subrespuesta = Rfibonacci(numero - 1);
            printf("\tEl hilo %d descubrio que Fibonacci(%ld) = %ld\n", omp_get_thread_num(), numero - 1, subrespuesta);
            #pragma omp atomic
                respuesta += subrespuesta;
        }
    }

    return respuesta;
}
