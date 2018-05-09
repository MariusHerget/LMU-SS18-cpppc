CC=g++
CFLAGS=--std=c++11 -lpthread #-Wall -Wextra -pedantic 
LDFLAGS=-lrt -lpthread -pthread -L${GTEST_BASE}/lib -lgtest
INCLUDES=-I${GTEST_BASE}/include -I../


OBJS = testsuite.o \
			 vector_test.o

.DEFAULT: all
all: $(OBJS) testsuite.bin

run: clean testsuite.bin
	./testsuite.bin

%.o: %.cc
	$(CC) $(CFLAGS)  $(INCLUDES) -c $< -o $@

%.bin: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.a: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

.PHONY: clean
clean:
	-rm -f *.o
	-rm -f *.a
	-rm -f *.bin
	-rm -f ../solution/*.o
	-rm -f ../solution/*.a
