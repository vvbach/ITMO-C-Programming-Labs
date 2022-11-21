#include <stdio.h>
#include <math.h>

enum Publication {
    book,
    newspaper,
    magazine,
    almanac
} p;

struct Point {
    int x;
    int y;
};

struct Line{
    struct Point p1;
    struct Point p2;
    double length;
};

struct Rectangle {
    struct Line l1;
    struct Line l2;
    double area;
} r2;


union MP3{
    struct State
    {
        unsigned int play : 1;
        unsigned int pause : 1;
        unsigned int record : 1;
    } state;
    int values;  
} m;


int main(){
    // Task 1
    p = newspaper;
    printf("%d\n", p);

    // Task 2
    printf("L1 :\n");
    printf("x1 = ");
    scanf("%d", &r2.l1.p1.x);
    printf("y1 = ");
    scanf("%d", &r2.l1.p1.y);
    printf("x2 = ");
    scanf("%d", &r2.l1.p2.x);
    printf("y2 = ");
    scanf("%d", &r2.l1.p2.y);
    r2.l1.length = sqrt(pow(r2.l1.p1.x - r2.l1.p2.x, 2) + pow(r2.l1.p1.y - r2.l1.p2.y, 2));

    r2.l2.p1.x = r2.l1.p1.x;
    r2.l2.p1.y = r2.l1.p1.y;
    printf("L2 :\n");
    printf("x2 = ");
    scanf("%d", &r2.l2.p2.x);
    printf("y2 = ");
    scanf("%d", &r2.l1.p2.y);
    r2.l2.length = sqrt(pow(r2.l2.p1.x - r2.l2.p2.x, 2) + pow(r2.l2.p1.y - r2.l2.p2.y, 2));

    if ((r2.l1.p1.x - r2.l1.p2.x)*(r2.l2.p1.x - r2.l2.p2.x) + (r2.l1.p1.y - r2.l1.p2.y)*(r2.l2.p1.y - r2.l1.p2.y) == 0){
        r2.area = r2.l1.length * r2.l2.length;
        printf("S = %.2f\n", r2.area);
    }
    else {
        printf("NOT A REC\n");
    }

    // Task 3
    printf("Enter number: ");
    scanf("%x", &m.values);
    printf("PLAY: %s | PAUSE: %s | RECORD: %s", (m.state.play == 1) ? "ON" : "OFF", (m.state.pause == 1) ? "ON" : "OFF", 
        (m.state.record == 1) ? "ON" : "OFF");
    return 0;
}