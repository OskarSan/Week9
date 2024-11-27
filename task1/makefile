CC = gcc
CFLAGS = -Wall -Wextra -I.
DEPS = sum.h
OBJ = main.o sum.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

taskOne: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o taskOne