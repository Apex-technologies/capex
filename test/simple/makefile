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

$(EXEC): $(EXEC).o mxm.o
	$(CC) -o $(BDIR)/$(EXEC) $(BDIR)/$(EXEC).o $(BDIR)/capex.o $(CFLAGS) $(LDFLAGS)
$(EXEC).o: testArray.cpp ../../src/array.cpp
	$(CC) -o $(BDIR)/$(EXEC).o -c *.cpp $(CFLAGS) $(OPTIONS)
mxm.o: usb.cpp
	$(CC) -o $(BDIR)/capex.o -c ../../src/usb.cpp $(CFLAGS) $(OPTIONS)
clean:
	rm -f *.o core
mrproper: clean
	rm -f $(EXEC)
