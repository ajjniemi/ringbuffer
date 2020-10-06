GTEST_DIR=/u/f/e1700812/googletest/googletest
CC=gcc
GC=g++

test: test_case.c ringbuffer.c Gtest_main.c libgtest.a
	$(GC) -isystem $(GTEST_DIR)/include -pthread test_case.c ringbuffer.c Gtest_main.c libgtest.a -o test

release: string.c main.c
	$(CC) string.c main.c -o release

clean: 
	rm -f *.o
libgtest.a:
	$(GC) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread -c $(GTEST_DIR)/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o



