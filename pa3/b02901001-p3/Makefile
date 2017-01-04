CC = g++
CXXFLAGS = -g  -Wall
EXEC = router
EXEC2 = router_v2
OBJS = router.cpp
OBJS2 = router.o
OBJS3 = libparser.a 

OBJS_V2 = router_slow.cpp
OBJS2_V2 = router_slow.o

all: $(EXEC) $(EXEC2)

$(EXEC): $(OBJS2) $(OBJS3)
	@echo "Making router"
	@$(CC) $(CXXFLAGS) $+ -o $@

$(OBJS2): $(OBJS)
	@$(CC) $(CXXFLAGS) -c $<

$(EXEC2): $(OBJS2_V2) $(OBJS3)
	@echo "Making router_v2"
	@$(CC) $(CXXFLAGS) $+ -o $@

$(OBJS2_V2): $(OBJS_V2)
	@$(CC) $(CXXFLAGS) -c $<


.PHONY:clean
clean:
	@rm -rf *.o $(EXEC) $(EXEC2)

 
