CC=g++ -std=c++11 -Iinc/
CFLAGS=-Wall -g3 -O0
SOURCES=src/main.cpp src/car.cpp src/printer.cpp src/controller.cpp
OBJECTS=main.o car.o printer.o track.o controller.o
EXECUTABLE=AI
PROJ_PATH_HEADERS=../inc/
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lfann

AI: $(OBJECTS)
	$(CC) $(CFLAGS) -o AI $(OBJECTS) $(LIBS)

main.o: $(SOURCES)
	$(CC) -c $(CFLAGS) src/main.cpp 

car.o: src/car.cpp inc/car.hpp
	$(CC) -c $(CFLAGS) src/car.cpp

printer.o: src/printer.cpp inc/printer.hpp
	$(CC) -c $(CFLAGS) src/printer.cpp

track.o: src/track.cpp inc/track.hpp
	$(CC) -c $(CFLAGS) src/track.cpp

controller.o: src/controller.cpp inc/controller.hpp
	$(CC) -c $(CFLAGS) src/controller.cpp

clean: 
	rm $(OBJECTS) AI
