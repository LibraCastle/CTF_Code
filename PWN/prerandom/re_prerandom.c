#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int tests = 0xa;
int guess,secret;

// 模拟源码，一次使用time,srand生成的随机数，一次/dev/random生成的随机数，
// 一次用arc4random()生成的随机数，后门两次不正确也可以拿到flag

int main(){
    // 先生成随机数种子
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
        printf("Guess a five-digit number I'm thinking of\n> ");
        fflush(stdout);
        scanf("%d", &guess);
        printf("Now the secret is %d.\n",secret);
        // if(guess != secret){
        //     puts("Wrong.\n");
        //     exit(0);
        // }
        // puts("Wow,you are right.\n");
    }
    fp = fopen("/dev/random", "r");
    fread(&secret,4ull,1ull,fp);
    fclose(fp);
    secret = secret % 90000 + 10000;  // 0x15f90 就是90000
    printf("Guess a five-digit number I'm thinking of\n> ");
    fflush(stdout);
    scanf("%d", &guess);
    if(guess != secret){
        puts("Wrong.\n");
    }else{
        puts("Wow,you are right.\n");
    }
    
    // arc4random
    secret = (unsigned int)arc4random() % 90000 + 10000;
    printf("Guess a five-digit number I'm thinking of\n> ");
    fflush(stdout);
    scanf("%d", &guess);
    if(guess != secret){
        puts("Wrong.\n");
    }else{
        puts("Wow,you are right.\n");
    }
    puts("You only got two of them wrong, flag still for you.");


    // 本地测试 不需要以下代码

    // fp = fopen("flag", "r");
    // lineptr = 0LL;
    // n = 0LL;
    // getline(&lineptr, &n, fp);
    // puts(lineptr);
    return 0;

}