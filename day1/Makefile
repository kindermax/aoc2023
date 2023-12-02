GCC = gcc
CFLAGS = -Wall -g
BINS = main

ALL: $(BINS)

main: main.o
	$(GCC) $(CFLAGS) -o $@ $^

run: $(BINS)
	./$(BINS)

clean:
	rm -f *.o $(BINS)