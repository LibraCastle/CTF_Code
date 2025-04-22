#include <stdio.h>

struct Point{
    int x;
    int y;
    int z;
}Point;

int main(){
    struct Point points[5]={
        {1,2,3},
        {4,5,6},
        {7,8,9},
        {10,11,12},
        {13,14,15}
    };
    int x = points[3].x;
    int y = points[3].y;
    int * zptr = &points[3].z;
    printf("x: %d, y: %d\n", x, y);
    printf("z's value: %d\n", *zptr);
    printf("z's address: %d\n", zptr);
    return 0;

}