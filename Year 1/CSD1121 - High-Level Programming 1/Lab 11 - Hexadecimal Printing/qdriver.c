#include <stdio.h>
#include "q.h"

int main(void)
{	
	const DATA array[] = 
	{
		{ {0x41, 0x61, 0x4161}, {0x42, 0x62, 0x4262} },
		{ {0x43, 0x63, 0x4363}, {0x44, 0x64, 0x4464} },
		{ {0x45, 0x65, 0x4565}, {0x46, 0x66, 0x4666} },
		{ {0x47, 0x67, 0x4767}, {0x48, 0x68, 0x4868} },
		{ {0x49, 0x69, 0x4969}, {0x4A, 0x6A, 0x4A6A} },
		{ {0x4B, 0x6B, 0x4B6B}, {0x4C, 0x6C, 0x4C6C} },
		{ {0x4D, 0x6D, 0x4D6D}, {0x4E, 0x6E, 0x4E6E} },
		{ {0x4F, 0x6F, 0x4F6F}, {0x50, 0x70, 0x5070} }
	};

	
	print_data(array, sizeof(array), 16);
	printf("\n");	
	print_data(array, sizeof(array), 8);
	printf("\n");
	print_data(array, sizeof(array), 4);
	
	/*
	DO NOT UNCOMMENT THIS CODE
	before you attempt to answer: what is the output of each of the statements
	shown below? Write down your answers first, then check if you answered
	correctly.
	
	printf("%x\n", array[3][1].upper);
	printf("%d\n", *((char*)array + 20));
	printf("%x\n", *(&array[6][0].value - 6));
	printf("%o\n", *(&array[3][1].lower + 5));
	printf("%d\n", ((array[3] + 1)[1]).value);
	*/
	return 0;
}
