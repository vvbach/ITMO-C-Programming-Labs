#include<stdio.h>
#include<math.h>

int main(){
    double a;
    printf("a = ");
    scanf("%lf", &a);
   // a = a * M_PI / 180;
    double z1 = cos(a) + cos(2*a) + cos(6*a) + cos(8*a);
    double z2 = 4 * cos(a / 2) * cos(5 * a / 2) * cos(4*a);
    printf("z1 = %lf\n", z1);
    printf("z2 = %lf", z2);
    return 0;
}