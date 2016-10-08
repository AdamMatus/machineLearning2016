#ifndef _PRINTER_HPP_
#define _PRINTER_HPP_

#include <SFML/Graphics.hpp>

#include <vector>

#include "../inc/car.hpp"

class printer{
private:
	std::vector<Car> cars;
	sf::RenderWindow mainWindow;

public:
	printer(unsigned int, unsigned int);
	void display();

};

#endif
