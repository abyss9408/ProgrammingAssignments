# name of C compiler
GCC       = gcc
# options to C compiler
COMPILE_FLAGS = -c -Wall -Wextra -Werror

# name of compiler
NASM       = nasm
# options to nasm compiler
NASM_FLAGS = -f elf64 -g -F dwarf

# name of linker
LINK       = ld
# options to linker
LINK_FLAGS = -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc

# list of object files
OBJS      = main.o functions.o

# name of executable program
EXEC      = main

# by convention the default target (the target that is built when writing
# only make on the command line) should be called all and it should
# be the first target in a makefile
all : $(EXEC)

# however, the problem that arises with the previous rule is that make
# will think all is the name of the target file that should be created
# so, we tell make that all is not a file name
.PHONY : all

# this rule says that target $(EXEC) will be built if prerequisite
# files $(OBJS) have changed more recently than $(EXEC)
# text $(EXEC) will be replaced with value functions.out
# text $(OBJS) will be substituted with list of prerequisites in line 10
# line 33 says to build $(EXEC) using command $(LD) with
# options $(NASM_FLAGS) specified on line 6
$(EXEC) : $(OBJS)
	$(GCC) $(OBJS) -o $(EXEC)

# target main.o depends on main.asm
# and is created with command $(NASM) given the options $(NASM_FLAGS)
main.o : main.c
	$(GCC) $(COMPILE_FLAGS) main.c -o main.o

# target functions.o depends on functions.asm
# and is created with command $(NASM) given the options $(NASM_FLAGS)
functions.o : functions.asm
	$(NASM) $(NASM_FLAGS) functions.asm -o functions.o

# says that clean is not the name of a target file but simply the name for
# a recipe to be executed when an explicit request is made
.PHONY : clean
# clean is a target with no prerequisites;
# typing the command in the shell: make clean
# will only execute the command which is to delete the object files
clean :
	rm -f $(OBJS) $(EXEC)

# says that rebuild is not the name of a target file but simply the name
# for a recipe to be executed when an explicit request is made
.PHONY : rebuild
# rebuild is for starting over by removing cleaning up previous builds
# and starting a new one
rebuild :
	$(MAKE) clean
	$(MAKE)

.PHONY : test
test : $(EXEC)
	./$(EXEC) 0

test0 : $(EXEC)
	./$(EXEC) 0

test1 : $(EXEC)
	./$(EXEC) 1

test2 : $(EXEC)
	./$(EXEC) 2

test3 : $(EXEC)
	./$(EXEC) 3

test4 : $(EXEC)
	./$(EXEC) 4

test5 : $(EXEC)
	./$(EXEC) 5

test6 : $(EXEC)
	./$(EXEC) 6

test7 : $(EXEC)
	./$(EXEC) 7

test8 : $(EXEC)
	./$(EXEC) 8

test9 : $(EXEC)
	./$(EXEC) 9

test10 : $(EXEC)
	./$(EXEC) 10

.PHONY : debug
debug : $(EXEC)
	gdb ./$(EXEC)