
CC=g++
CFLAGS=-std=c++11 -pedantic -Wall -Wextra -g

# Links together files needed to create executable
physicalmodel: # .c and .o files
	$(CC) $(CFLAGS) -o physicalmodel # same .c and .o files

# Compiles read_line.c to create read_line.o
functions.o: # .c and .o files
	$(CC) $(CFLAGS) -c # same .c and .o files

# Removes all object files and the executable named main,
# so we can start fresh
clean:
	rm -f *.o main
