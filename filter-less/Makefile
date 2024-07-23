CC = clang
CFLAGS = -ggdb3 -O0 -std=c11 -Wall -Werror
LDLIBS = -lm

# Target for your main executable
filter: filter.o helpers.o
	$(CC) $(CFLAGS) -o filter filter.o helpers.o $(LDLIBS)

# Target to compile helpers.c into helpers.o
helpers.o: helpers.c helpers.h
	$(CC) $(CFLAGS) -c helpers.c

# Target to compile filter.c into filter.o
filter.o: filter.c helpers.h
	$(CC) $(CFLAGS) -c filter.c

# Clean target to remove object files and executables
clean:
	rm -f *.o filter
