// @author: Bryan Ang Wei Ze (bryanweize.ang@digipen.edu)

#include <stdio.h>

int exponent(int x, int y);

int main(void){
    printf("Enter base and power: ");
    int base, power;
    scanf("%d %d", &base, &power);
    int result = exponent(base, power);
    printf("%d ^ %d is: %d\n", base, power, result);
    return 0;
}

int exponent(int x, int y){
    int n = x, i = 1;
    while (i < y){
        n = n * x;
        i += 1;
    }
    return n;
}