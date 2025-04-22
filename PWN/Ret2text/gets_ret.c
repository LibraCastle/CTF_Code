#include <stdio.h>
#include <stdlib.h>

void backdoor(){
    system("/bin/sh");
}

char *gets(char *s);  // 由于已被禁用过滤，只能通过声明后调用

int main(){
    char name[0x10];
    puts("Please input your name: ");
    gets(name);
    printf("Hello, %s\n", name);
    return 0;
}
