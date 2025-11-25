#include <stdio.h> // to declare C standard library function printf
#include "calc.h"  // to declare functions squared, cubed, and minus

int main(void) {
	// testing function squared ...
	printf("Square of 2 is: %d\n", squared(2));
	int i = 3;
	printf("Square of %d is: %d\n", i, squared(i));
	// What happens if the argument to function squared is a value of type double?
	// The compiler will implicitly convert the function argument which is an
	// expression of type double to a value of type int. Here, the value
	// 3.4 is truncated to a value 3 of type int.
	printf("Square of %f is: %d\n", 3.4, squared(3.4));
	
	// testing function cubed ...
	double d = 3.4;
	printf("Cube of %f is: %f\n", d, cubed(d));
	// What happens if the argument to function cubed is a value of type int?
	// The compiler will implicitly promote the function argument which is an
	// expression of type int to a value of type double. Here, the value 4
	// is promoted to a value 4.0 of type double.
	printf("Cube of 4 is: %f\n", cubed(4));
	// Similarly, here the int value returned by function squared is promoted to
	// a value of type double ...
	printf("Cube of squared(%d) is: %f\n", i+1, cubed(squared(i+1)));
	
	// testing function minus ...
	
	// Again, the compiler will implicitly promote the function argument which is
	// an expression of type int to a value of type double. Here, the value 5
	// is promoted to a value 5.0 of type double.
	printf("Minus 5 is: %f\n", minus(5));
	printf("Minus %f is: %f\n", -d, minus(-d));	
	double x = 1.23;
	printf("Minus squared(cubed(%f)) is: %f\n", x, minus(squared(cubed(x))));
	
	return 0;
}
