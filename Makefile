CC=g++ -std=c++11 
CFLAGS=-Wall -g3 -O0
SOURCES=main.cpp car.cpp printer.cpp controller.cpp

INC_PATH=inc/
SRC_PATH=src/
OBJ_PATH=obj/

vpath %.hpp $(INC_PATH)
vpath %.cpp $(SRC_PATH)

CC=g++ -std=c++11
CFLAGS=-Wall -g3 -O0
IINC=-I$(INC_PATH)

OBJECTS=main.o car.o printer.o track.o controller.o
EXECUTABLE=AI

SFMLLIBS=-lsfml-graphics -lsfml-window -lsfml-system

AI: $(OBJECTS) 
	$(CC) $(CFLAGS) -o AI $^ $(SFMLLIBS)

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CC) -MM $< $(INC_PATH) > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\l.o $@ : ,g' < $@.$$$$ > $@; \
	rm -d $@.$$$$	

main.o: main.cpp car.hpp printer.hpp track.hpp controller.hpp
	$(CC) -c $(CFLAGS) $(IINC) $< 

car.o: car.cpp car.hpp
	$(CC) -c $(CFLAGS) $(IINC) $<

printer.o: printer.cpp printer.hpp track.hpp controller.hpp
	$(CC) -c $(CFLAGS) $(IINC) $<

track.o: track.cpp track.hpp car.hpp
	$(CC) -c $(CFLAGS) $(IINC) $<

controller.o: controller.cpp controller.hpp car.hpp
	$(CC) -c $(CFLAGS) $(IINC) $<

.PHONY : clean
clean: 
	rm *.o AI
