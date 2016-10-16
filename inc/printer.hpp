#ifndef _PRINTER_HPP_
#define _PRINTER_HPP_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>

#include "../inc/car.hpp"
#include "../inc/track.hpp"


const auto basic_quantum_time = std::chrono::milliseconds(25);

class Printer{
private:
	sf::RenderWindow mainWindow;
	sf::Event event;
	sf::Font arial;

	void drawBarriers(const Track& tr);
	void drawCar(const Car& c) 
	{
		sf::RectangleShape car_rs(c.getSize());
		car_rs.setPosition(c.getPosition());
		car_rs.setFillColor(sf::Color::Red);
		mainWindow.draw(car_rs);	
	} 
	void waitForNextFrame();

public:

	void testPoll(Track& contextTrack, Car& contextCar);

	Printer(unsigned int, unsigned int);
	void letUserDrawBarriers(Track& tr);
};

#endif
