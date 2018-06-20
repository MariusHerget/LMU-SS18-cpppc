# run export LD_LIBRARY_PATH=~/LMU/LMU-SS18-cpppc/Assignments/07/solution/benchmarking beforehand

CC=g++
CFLAGS=--std=c++14 -Wall
INCLUDES=-I./include
LIBS=-L./lib -lcelero

OBJS = badVirtualDuDuDu.o

.DEFAULT: all
all: clean run

run: $(OBJS) badVirtualDuDuDu
	./badVirtualDuDuDu

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ $(LIBS)

%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ $(LIBS)

badVirtualDuDuDu: badVirtualDuDuDu.o
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@ $(LIBS)

.PHONY: clean
clean:
	-rm -f *.o
	-rm -f *.a
	-rm -f *.bin
	-rm -f ../solution/*.o
	-rm -f ../solution/*.a
