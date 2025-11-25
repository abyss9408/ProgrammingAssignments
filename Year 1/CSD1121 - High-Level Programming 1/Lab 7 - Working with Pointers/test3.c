#include <stdio.h>
#include "../q.h"

int main(void)
{
	int num1, num2, num3;
	read_3_numbers(&num1, &num2, &num3);
	sort_3_numbers(&num1, &num2, &num3); // Tested function
	printf("%d, %d, %d\n", num1, num2, num3);
}
