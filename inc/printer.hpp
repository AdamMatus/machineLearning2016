#ifndef _PRINTER_HPP_
#define _PRINTER_HPP_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

//fann
#include <fann.h>
#include <iostream>
#include <fstream>

#include <vector>
#include <car.hpp>
#include <track.hpp>
#include <terminal.hpp>

const auto basic_quantum_time = std::chrono::milliseconds(25);

class Printer{
private:
	sf::RenderWindow mainWindow;
	sf::Event event;
	sf::Font arial;

	void drawTerminal(const Terminal&);
	void drawBarriers(const Track& tr);
	void drawCar(const Car& c) 
	{
		sf::CircleShape car_rs(c.getSize().x);
		auto position = c.getPosition();
		position.x -= c.getSize().x;
		position.y -= c.getSize().y;
	
		car_rs.setPosition(position);
		car_rs.setFillColor(sf::Color::Red);
		mainWindow.draw(car_rs);	
	} 
	void waitForNextFrame();
	void doBarrierGraphicsAndEndFrame(const Track& contextTrack)
	{
		mainWindow.clear(sf::Color::Black);
		drawBarriers(contextTrack);
		mainWindow.display();
		waitForNextFrame();
	}
	bool isWindowClosed() //watch out that this function disables all event pending
	{
		while(mainWindow.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				mainWindow.close();
				return true;
			}
		} 
		return false;
	}
	void drawCarInfo(const Car&, const CarPredictedMovementInfo&, const CarPredictedMovementInfo& normalizedCPMI);

	sf::RectangleShape mouseDrawingBarriersDetection();
	unsigned int width;
	unsigned int hight;

public:

	Printer(unsigned int, unsigned int);
	void testPoll(Track& contextTrack, Car& contextCar);
	bool letUserDrawBarriers(Track& tr);
	void letUserDrawSingleBarrier(Track& contextTrack);
	void letUserDrawFinishBarrier(Track & contextTrack);
};

#endif
