#include <stdio.h>
#include <math.h>
#include "triangle.h"

double Area(Triangle t){
    double e1 = sqrt(pow(t.p1.x - t.p2.x, 2) + pow(t.p1.y - t.p2.y, 2));
    double e2 = sqrt(pow(t.p2.x - t.p3.x, 2) + pow(t.p2.y - t.p3.y, 2));
    double e3 = sqrt(pow(t.p3.x - t.p1.x, 2) + pow(t.p3.y - t.p1.y, 2));
    double p = (e1 + e2 + e3) / 2;
    return sqrt(p * (p - e1) * (p - e2) * (p - e3));
}

double Perimeter(Triangle t){
    double e1 = sqrt(pow(t.p1.x - t.p2.x, 2) + pow(t.p1.y - t.p2.y, 2));
    double e2 = sqrt(pow(t.p2.x - t.p3.x, 2) + pow(t.p2.y - t.p3.y, 2));
    double e3 = sqrt(pow(t.p3.x - t.p1.x, 2) + pow(t.p3.y - t.p1.y, 2));
    return e1 + e2 + e3;
}