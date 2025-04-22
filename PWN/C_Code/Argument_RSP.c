#include <stdio.h>

int foo(){
    return 0;
}

int foo2(int a, int b){
    return a + b;
}

int foo3(int a,int b,int c,int d,int e,int f,int g,int h){
    return a + b + c+ d+ e+ f + g + h;
}

int main(){
    foo3(1,2,3,4,5,6,7,8);
    return 0;
}