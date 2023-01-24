#include <stdio.h>
#include <math.h>
#include "triangle.h"

void Length(Triangle *t){
    t->e1 = sqrt(pow(t->p1.x - t->p2.x, 2) + pow(t->p1.y - t->p2.y, 2));
    t->e2 = sqrt(pow(t->p2.x - t->p3.x, 2) + pow(t->p2.y - t->p3.y, 2));
    t->e3 = sqrt(pow(t->p3.x - t->p1.x, 2) + pow(t->p3.y - t->p1.y, 2));
}

void Area(Triangle *t){
    double p = (t->e1 + t->e2 + t->e3) / 2;
    t->area = sqrt(p * (p - t->e1) * (p - t->e2) * (p - t->e3));
}

void Perimeter(Triangle *t){
    t->perimeter = t->e1 + t->e2 + t->e3;
}