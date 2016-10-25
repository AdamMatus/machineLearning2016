#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

#include <SFML/Graphics.hpp>

#include <car.hpp>

class Controller {
	public:
		virtual	void move(Car& contextCar) = 0;
		sf::Vector2f getDirInfo() const;
	protected:
		void setDir(sf::Vector2f d)
		{
			dir = d;
		}
	private:
		sf::Vector2f dir;

}; // ~Controller

class KeyboardController : public Controller {
	public:
		void move(Car& contextCar);
	private:
		void updateDirInfoFromKeyboard();

}; // ~keyboardController


#endif 
