CC=g++ -std=c++11
CFLAGS=-Wall
SOURCES=src/main.cpp
OBJECTS=main.o
EXECUTABLE=AI
SFMLLIBS=-lsfml-graphics -lsfml-window -lsfml-system

AI: $(OBJECTS)
	$(CC) $(CFLAGS) -g -o AI $(OBJECTS) $(SFMLLIBS)

main.o: $(SOURCES)
	$(CC) -c -g3 $(CFLAGS) src/main.cpp 

clean: 
	rm main.o AI
