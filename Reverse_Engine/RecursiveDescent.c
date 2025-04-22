#include <stdio.h>

int square(int x) {
    return x * x;  // call/ret 目标
}

int main() {
    int a = 3;
    int b = square(a);  // call
    if (b > 5) {         // 可能生成 ja、jg、jne 等
        printf("Greater than 5\n");
    } else {
        printf("Less or equal to 5\n");
    }

    return 0; // ret
}
