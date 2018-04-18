CC = g++
INCLUDES = -I/usr/include/libusb-1.0 -I../../src
LIB = -lusb-1.0
CFLAGS =  $(INCLUDES) $(LIB) -g -O  -std=c++11
OPTIONS =
EXEC = test
VPATH = . ../../src/
BDIR = ./bin

all: $(EXEC)

debug: OPTIONS = -DDEBUG -g
debug: $(EXEC)

$(EXEC): $(EXEC).o
	$(CC) -o $(BDIR)/$(EXEC) $(BDIR)/$(EXEC).o $(CFLAGS) $(LDFLAGS)
<<<<<<< HEAD
$(EXEC).o: testArray.cpp ../../src/*.cpp
=======
$(EXEC).o: testCapex.cpp ../../src/*.cpp
>>>>>>> e5052717c5ddb2aab752436b1a9d04b78e056ae5
	$(CC) -o $(BDIR)/$(EXEC).o -c *.cpp $(CFLAGS) $(OPTIONS)
clean:
	rm -f *.o core
mrproper: clean
	rm -f $(EXEC)
