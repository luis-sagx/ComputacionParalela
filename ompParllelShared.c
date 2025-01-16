#include <stdio.h>
#include <omp.h>

int tid, x = -1, y = -1, z = -1;

int main(){
    x = 2; y = 1;
    printf("Valores antes: x -> %d,   y -> %d,   z -> %d\n", x,y,z);
    #pragma omp parallel shared(y) firstprivate(x) private (z)
    {
        tid = omp_get_thread_num();
        //printf("P(%d)\n", tid);
        //if(tid == 0)
        printf(" Dentro_1(%d) x -> %d, y -> %d, z -> %d\n", tid, x,y,z);
        z = x*x + 3;
        x = y*3 + z;
        if(tid == 0)
            y = x;
        printf(" Dentro_1(%d) x -> %d, y -> %d, z -> %d\n", tid, x,y,z);
    }
    printf("Valores despues: x -> %d,   y -> %d,   z -> %d", x,y,z);
    return 0;
}
