#include "../inc/printer.hpp"

//only constructor
printer::printer(unsigned int width, unsigned int hight){
	sf::RenderWindow mainWindow(sf::VideoMode(width, hight), "Driving doggo rectangles.");
	mainWindow.setVerticalSyncEnabled(true);
}

void printer::display(){
	
}
