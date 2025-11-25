GCC_OPTIONS = -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra  -Werror -Werror=vla
OBJS = qdriver.o q.o
EXEC = q.out

$(EXEC) : $(OBJS)
	gcc $(GCC_OPTIONS) $(OBJS) -o q.out -lm
	
qdriver.o : qdriver.c q.h
	gcc $(GCC_OPTIONS) -c qdriver.c -o qdriver.o
	
q.o : q.c q.h
	gcc $(GCC_OPTIONS) -c q.c -o q.o

clean:
	rm $(OBJS) $(EXEC)
