#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", (n >= 76 && n <= 78));

    int m;
    scanf("%d", &m);
    printf("%d\n", (m >> (6-1)) & 1);
    return 0;
}