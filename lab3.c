#include <stdio.h>

int main(){
    int n;
    scanf("%x", &n);
    printf("%d\n", n);
    printf("%x %x\n",n , n >> 2);
    printf("%x %x\n",n , ~n);
    int m;
    scanf("%x", &m);
    printf("%x\n",n | m);
    return 0;
}