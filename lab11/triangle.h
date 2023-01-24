#ifndef TRIANGLE
#define TRIANGLE
typedef struct Point {
    int x;
    int y;
} Point;

typedef struct Triangle {
    Point p1;
    Point p2;
    Point p3;
    double e1, e2, e3;
    double area;
    double perimeter;
} Triangle;

void Length(Triangle *t);

void Area(Triangle *t);

void Perimeter(Triangle *t);



#endif