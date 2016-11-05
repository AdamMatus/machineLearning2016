#ifndef _PRINTER_HPP_
#define _PRINTER_HPP_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>

#include <car.hpp>
#include <track.hpp>

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
	void doBarrierGraphicsAndEndFrame(const Track& contextTrack)
	{
		mainWindow.clear(sf::Color::Black);
		drawBarriers(contextTrack);
		mainWindow.display();
		waitForNextFrame();
	}
	bool isWindowClosed() 
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
	void drawCarInfo(const Car&, const CarPredictedMovementInfo&);

	sf::RectangleShape mouseDrawingBarriersDetection();

public:

	Printer(unsigned int, unsigned int);
	void testPoll(Track& contextTrack, Car& contextCar);
	bool letUserDrawBarriers(Track& tr);
};

#endif
