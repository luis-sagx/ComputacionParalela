#include <stdio.h>
#include <omp.h>

int main(){
    int iam = 0, np = 1;
    int x= 44;

    omp_set_num_threads(2);

    //printf("Paralelismo Inicio np = %d\n", np);
    printf("Valor inicial de x = %d\n", x);
    #pragma omp parallel sections private (x)
    {
        #pragma omp section
        {
            x=1;
            printf("Seccion 1 ejecutada por thread %d, %d\n", omp_get_thread_num(),x);
        }
        #pragma omp section
        {
            x=2;
            printf("Seccion 2 ejecutada por thread %d, %d\n", omp_get_thread_num(),x);
        }
        #pragma omp section
        {
            x=3;
            printf("Seccion 3 ejecutada por thread %d, %d\n", omp_get_thread_num(),x);
        }
        #pragma omp section
        {
            x=4;
            printf("Seccion 4 ejecutada por thread %d, %d\n", omp_get_thread_num(),x);
        }

        //#if defined(_OPENMP)
           // np = omp_get_num_threads();
           // iam = omp_get_thread_num();
           // printf("Tarea %d de %d\n", iam, np);
           // x = x  + np;
           // printf("Valor modificado de x = %d\n", x);
        //#endif
    }
    //printf("Paralelismo Final np = %d\n", np);
    printf("Valor final de x = %d\n", x);
    return 0;
}


