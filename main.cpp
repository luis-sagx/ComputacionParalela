#include <stdio.h>
#include <omp.h>

int tid, x = -1, y = -1, z = -1;

int main(){
    x = 2; y = 1;
    printf("Valores antes: x -> %d, y -> %d, z -> %d", x,y,z);
    #pragma omp parallel shared(y)
    {
        tid = omp_get_thread_num();
        printf("%d\n", tid);
    }
    printf("Valores despues: x -> %d, y -> %d, z -> %d", x,y,z);
}