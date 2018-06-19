CC=clang++
CFLAGS=--std=c++14 -L./include -lcelero
INCLUDES=-I./include

OBJS = badVirtualDuDuDu.o

.DEFAULT: all
all: clean run

run: $(OBJS) badVirtualDuDuDu
	./badVirtualDuDuDu

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

badVirtualDuDuDu: badVirtualDuDuDu.o
	$(CC) $< -o $@

.PHONY: clean
clean:
	-rm -f *.o
	-rm -f *.a
	-rm -f *.bin
	-rm -f ../solution/*.o
	-rm -f ../solution/*.a
