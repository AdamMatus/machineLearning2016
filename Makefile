CC=g++ -std=c++11
CFLAGS=-Wall -g3 
SOURCES=src/main.cpp src/car.cpp src/printer.cpp
OBJECTS=main.o car.o printer.o
EXECUTABLE=AI
SFMLLIBS=-lsfml-graphics -lsfml-window -lsfml-system

AI: $(OBJECTS)
	$(CC) $(CFLAGS) -o AI $(OBJECTS) $(SFMLLIBS)

main.o: $(SOURCES)
	$(CC) -c $(CFLAGS) src/main.cpp 

car.o: src/car.cpp inc/car.hpp
	$(CC) -c $(CFLAGS) src/car.cpp

printer.o: src/printer.cpp inc/printer.hpp
	$(CC) -c $(CFLAGS) src/printer.cpp

clean: 
	rm $(OBJECTS) AI
