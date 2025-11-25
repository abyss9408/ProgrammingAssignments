#include <stdio.h>
#include "../q.h"

int main(void)
{
	size_t count = read_total_count();
	int top1, top2, top3;
	read_3_numbers(&top1, &top2, &top3);
	sort_3_numbers(&top1, &top2, &top3);
	
	count -= 3;
	while (count--)
	{
		int number;
		scanf("%d", &number);
		maintain_3_largest(number, &top1, &top2, &top3);
	}
	
	printf("The third largest number is %d.\n", top3);
}
