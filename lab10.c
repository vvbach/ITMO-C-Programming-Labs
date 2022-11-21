#include <stdio.h>
#include <malloc.h>

int GCD(int n, int m){
    while (n != m){
        if (n > m){
            n = n - m;
        }
        else {
            m = m - n;
        }
    }
    return n;
}

int LCM(int n, int m){
    return n * m / GCD(n, m);
}

int* array(int n, int *s){
    int temp = n;
    int size = 0;
    while (temp > 0){
        size++;
        temp /= 10;
    }
    int *arr = (int*)malloc(size * sizeof(int));
    int i;
    for (i = size - 1; i >= 0; i--){
        arr[i] = n % 10;
        n /= 10;
    }
    *s = size;
    return arr;
}

int main(){
    //Task 1
    int a, b;
    printf("Enter 2 numbers: ");
    scanf("%d %d", &a, &b);
    printf("GCD: %d | LCM: %d\n", GCD(a, b), LCM(a, b));

    //Task 3
    int n;
    int size;
    printf("Enter number: ");
    scanf("%d", &n);
    int *arr = array(n, &size);
    
    printf("Array: ");
    for (int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
}