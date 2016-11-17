CC = g++
CFLAGS = -g -Wall
EXEC = maxPlanarSubset

$(EXEC): $(EXEC).o 
	$(CC) $+ -o $@

$(EXEC).o: $(EXEC).cpp
	$(CC) $(CFLAGS) -c $<

.PHONY:clean
clean:
	rm -rf *.o $(EXEC)
 
