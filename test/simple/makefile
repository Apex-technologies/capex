CC = g++
CFLAGS = -I/home/maxime/Programmation/Array/src -g -Wall -O
OPTIONS =
EXEC = test

all: $(EXEC)

debug: OPTIONS = -DDEBUG -g
debug: $(EXEC)

$(EXEC): $(EXEC).o
	$(CC) -o ./bin/$(EXEC) ./bin/$(EXEC).o $(LDFLAGS)
$(EXEC).o: testArray.cpp
	$(CC) -o ./bin/$(EXEC).o -c testArray.cpp $(CFLAGS) $(OPTIONS)
clean:
	rm -f *.o core
mrproper: clean
	rm -f $(EXEC)
