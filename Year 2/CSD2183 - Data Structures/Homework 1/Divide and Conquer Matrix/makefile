all: matmul_growth_power.out

main.o: main.cpp
	g++ -c main.cpp -o main.o

matrix_utilities.o : matrix_utilities.cpp matrix_utilities.h
	g++ -c matrix_utilities.cpp -o matrix_utilities.o

matmul_divide_and_conquer.o: matmul_divide_and_conquer.cpp matmul_divide_and_conquer.h
	g++ -c matmul_divide_and_conquer.cpp -o matmul_divide_and_conquer.o

matmul_strassens.o : matmul_strassens.cpp matmul_strassens.h
	g++ -c matmul_strassens.cpp -o matmul_strassens.o

clean:
	rm -f *.o *.out

matmul_growth_power.out: matrix_utilities.o matmul_divide_and_conquer.o matmul_strassens.o main.o 
	g++ matrix_utilities.o matmul_divide_and_conquer.o matmul_strassens.o main.o -o matmul_growth_power.out

run: matmul_growth_power.out
	./matmul_growth_power.out 
