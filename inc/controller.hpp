#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

//TODO delete later
#include <iostream>

#include <fann.h>

#include <SFML/Graphics.hpp>

#include <car.hpp>

class Controller {
	public:
		void move(Car& contextCar);
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

class ANNController : public Controller {
	public:
		void move(Car & contextCar, struct fann *ann, Track &);
	private:
		void updateDirInfoFromANN(struct fann *ann, Car & contextCar, Track &);

}; // ~ANNController


#endif 
