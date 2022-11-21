#include <stdio.h>
#include <malloc.h>

int main(){

    //Task 1
    double arr1[4];
    double *p = arr1;
    *p = -3.4;
    *(p + 1) = 4.5;
    *(p + 2) = -5.6;
    *(p + 3) = 6.7;

    for (int i = 0; i < 4; i++){
        printf("%f ", *(p + i));
    }
    printf("\n");

    // Task 2
    double *arr2 = (double*)malloc(4 * sizeof(double));
    arr2[0] = -3.4;
    arr2[1] = 4.5;
    arr2[2] = -5.6;
    arr2[3] = 6.7;
    for (int i = 0; i < 4; i++){
        printf("%f ", arr2[i]);
    }
    printf("\n");
    free(arr2);
    return 0;
}