#include <stdio.h>
#include <omp.h>


int main() {
    int i, TID, n = 3, vlen = 9;
    int a[9];
    int indx = 2;


    for (i = 0; i < vlen; i++)
        a[i] = -i - 1;


    #pragma omp parallel default(none) firstprivate(indx) private(i, TID) shared(n, a)
    {
        TID = omp_get_thread_num();
        indx += n * TID;


        printf("Thread %d starts with indx = %d\n", TID, indx);


        for (i = indx; i < indx + n && i < vlen; i++) {
            a[i] = TID + 1;
            printf("Thread %d sets a[%d] = %d\n", TID, i, a[i]);
        }
    }


    printf("\nAfter the parallel region:\n");
    for (i = 0; i < vlen; i++)
        printf("a[%d] = %d\n", i, a[i]);


    return 0;
}
