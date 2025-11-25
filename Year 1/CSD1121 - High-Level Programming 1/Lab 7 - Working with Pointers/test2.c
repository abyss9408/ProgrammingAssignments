#include <stdio.h>
#include "../q.h"

int main(void)
{
	int num1, num2;
	scanf("%d%d", &num1, &num2);
	swap(&num1, &num2); // Tested function
	printf("%d, %d\n", num1, num2);
}
