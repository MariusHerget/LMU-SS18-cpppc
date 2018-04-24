
CC=clang++
CFLAGS=--std=c++11 -Wall -Wextra -pedantic
LDFLAGS=-lpthread -L${GTEST_BASE}/lib -lgtest

INCLUDES=-I${GTEST_BASE}/include -I../

OBJS = testsuite.o \
			 vector_test.o \
			 ../solution/vector.o \
			  deque_test.o \
			 stack_test.o \
			 # \
			 ../solution/deque.o \
			 ../solution/stack.o
.DEFAULT: all
all: $(OBJS) testsuite.bin

run: clean testsuite.bin
	./testsuite.bin

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -Wsign-compare

%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -Wsign-compare

%.bin: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) -Wsign-compare

.PHONY: clean
clean:
	-rm -f *.o
	-rm -f *.a
	-rm -f *.bin
	-rm -f ../solution/*.o
	-rm -f ../solution/*.a
