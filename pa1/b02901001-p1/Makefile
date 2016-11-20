CC = g++
CFLAGS = -g -Wall
EXEC = sort
TEST = test

$(EXEC): sort.o parser.o
	$(CC) $+ -o $@

sort.o: sort.cpp
	$(CC) $(CFLAGS) -c $<

test_parser.o: test_parser.cpp parser.o
	$(CC) $(CFLAGS) -c $<
parser.o: parser.cpp parser.h
	$(CC) $(CFLAGS) -c $< 

test: test_parser.o parser.o
	$(CC) $+ -o $@


.PHONY:clean
clean:
	rm -rf *.o $(EXEC) $(TEST)
 
