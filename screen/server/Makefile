CC=g++
OBJS=server.o serialport.o
CFLAGS=-c -Wall -O2
LFLAGS=-static
PROGRAM=server

#Main program target
$(PROGRAM): $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM) $(LFLAGS)

#Server object target
server.o: server.cpp serialport.h keyboardInput.h screenInput.h
	$(CC) server.cpp -o server.o $(CFLAGS)

#Serialport target
serialport.o: serialport.cpp
	$(CC) serialport.cpp -o serialport.o $(CFLAGS)

#Removes all objects and executables
clean:
	@rm -f $(OBJS)
	@rm -f $(PROGRAM)
