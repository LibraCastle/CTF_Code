#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int tests = 0xa;
int guess,secret;

// 模拟源码，一次使用time,srand生成的随机数，一次/dev/random生成的随机数，
// 一次用arc4random()生成的随机数，后门两次不正确也可以拿到flag

int main(){
    unsigned int v10;
    struct tm *v3;  
    time_t timer;
    char * lineptr;
    size_t n;
    FILE *fp;
    
    timer = time(NULL);
    v3 = localtime(&timer);
    srandom(v3->tm_yday);
    puts("Let's play a number guessing game.");
    while(tests--){
        secret = random() % 90000+10000;
        printf("%d,\n",secret);
    }
    
    return 0;
}