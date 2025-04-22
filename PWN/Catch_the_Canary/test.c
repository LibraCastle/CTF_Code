#include <stdio.h>
#include <stdlib.h>
#define u_int unsigned int
#define __int64 long long

int geussTheV6(){
    u_int v3 = arc4random();
    u_int v4 = v3 - 0xFEFFFFFFFFFFFFLL * ((__int64)((0x4040404040404081LL * (unsigned __int128)v3) >> 64) >> 54);
    u_int i;
    u_int v6;
    unsigned int v8 = arc4random() % 0x2345 + 16768186;   // 0x2345 = 9027
    printf("v8 = %u\n", v8);
    scanf("%u", &v6);
    printf("v6 = %u\n", v6);
    printf("v8 = %u\n", v8);
    if (v6 == v8){
        printf("v6 = %u\n", v6);
        return 0;
    }
    else{
        printf("v6 = %u\n", v6);
        return 1;
    }
}

int main(){
    int a = 999 ;
    // while(1){
    //     geussTheV6();
    // }

    // printf("retv = %u\n", retv);

    printf("Please enter a number: ");
    scanf("%d", &a);
    if (a !=999){
        printf("You changed the value of a\n");
        exit(-1);
    }else{
        printf("You didn't change the value of a.How do you know that?\n");
        exit(0);
    }

    return 0;
}