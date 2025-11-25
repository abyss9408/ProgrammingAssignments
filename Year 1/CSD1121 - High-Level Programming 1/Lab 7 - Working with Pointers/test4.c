#include <stdio.h>
#include "../q.h"

int main(void)
{
	int num1, num2, num3, num;
	read_3_numbers(&num1, &num2, &num3);
	sort_3_numbers(&num1, &num2, &num3);
	scanf("%d", &num);
	maintain_3_largest(num, &num1, &num2, &num3); // Tested function
	printf("%d, %d, %d\n", num1, num2, num3);
}
