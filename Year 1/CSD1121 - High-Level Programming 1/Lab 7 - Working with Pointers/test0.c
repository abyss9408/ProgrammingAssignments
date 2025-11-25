#include <stdio.h>
#include "../q.h"

int main(void)
{
	size_t count = read_total_count(); // Tested function
	printf("Input value was %zu.\n", count);
}
