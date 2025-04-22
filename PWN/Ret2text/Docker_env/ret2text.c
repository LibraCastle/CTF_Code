#include <stdio.h>
#include <stdlib.h>

void backdoor(){
    system("/bin/sh");
}

int main(){
    char name[0x10];
    puts("Please input your name: ");
    scanf("%s",name);
    printf("Hello, %s\n", name);
    return 0;
}
