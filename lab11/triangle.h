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
    double area;
    double perimeter;
} Triangle;

double Area(Triangle t);

double Perimeter(Triangle t);

#endif