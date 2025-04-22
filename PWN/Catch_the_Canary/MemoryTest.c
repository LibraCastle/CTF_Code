#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(){
    
    int v6= arc4random() % 0x2345 + 16768186; // v6获得高地址，v8获得低地址，从而尝试用v8覆盖v6
    int v8;
    printf("Please enter the value of v8: \n");
    scanf("%d", &v8);

    if(v6 == v8){
        printf("v6 = %d\nv8 = %d\n", v6,v8);
        printf("You guessed the value correctly!\n");
    } else {
        printf("v6 = %d\nv8 = %d\n", v6,v8);
        printf("You guessed the value incorrectly.\n");
    }


    // 使用 字符串进行溢出
    
    // char s1 [8]= "88887888";
    // char s2 [8]; 

    // printf("Please enter the value of s2: \n");
    // scanf("%s", &s2);

    // if(strcmp(s1, s2) == 0){
    //     printf("s1 = %s\ns2 = %s\n", s1,s2);
    //     printf("You guessed the value correctly!\n");
    // } else {
    //     printf("s1 = %s\ns2 = %s\n", s1,s2);
    //     printf("You guessed the value incorrectly.\n");
    // }
    return 0;
}