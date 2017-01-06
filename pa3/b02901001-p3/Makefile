CC = g++
CXXFLAGS = -g  -Wall
EXEC = router
OBJS = router.cpp
OBJS2 = router.o
OBJS3 = libparser.a 


all: $(EXEC)

$(EXEC): $(OBJS2) $(OBJS3)
	@echo "Making router"
	@$(CC) $(CXXFLAGS) $+ -o $@

$(OBJS2): $(OBJS)
	@$(CC) $(CXXFLAGS) -c $<

.PHONY:clean
clean:
	@rm -rf *.o $(EXEC)

 
