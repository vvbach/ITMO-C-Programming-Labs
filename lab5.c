#include <stdio.h>

int main(){
    // Task 1
    int arr1[6] = {34, 45, 56, 67, 78, 89}; 
    for (int i = 0; i < 6; i++){
        printf("%d ", arr1[i]);
    }
    printf("\n");


    // Task 2
    int mat1[2][2] = {{1, 1}, {0, 1}};
    int mat2[2][2] = {{2, 0}, {3, 0}};
    int res[2][2] = {{0, 0}, {0, 0}};
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            for (int k = 0; k < 2; k++){
                res[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            printf("%d ", res[i][j]);
        }
        printf("\n");
    }
    return 0;
}