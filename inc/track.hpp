#ifndef _TRACK_HPP_
#define _TRACK_HPP_

#include <SFML/Graphics.hpp>

#include <chrono>
#include <vector>

#include "../inc/car.hpp"

class Track{
public:
	Track(const sf::Vector2u& winSize, const std::chrono::milliseconds q_time) :
		quantum_time{q_time},
		windowConstrains{
			sf::Vector2f(static_cast<float>(winSize.x), 0),  //reverse order
	 		sf::Vector2f(static_cast<float>(winSize.y), 0)}	
	{
		barriers.push_back(windowConstrains);	
	}
	void trackMove(Car&);

private:
	class Barrier;
	std::vector<Barrier> barriers;

	const std::chrono::milliseconds quantum_time;

	class Barrier{
	public:
		sf::Vector2f testConstrains(const Car& contextCar);
		Barrier(sf::Vector2f xCon, sf::Vector2f yCon):
			xConstrains(xCon),
			yConstrains(yCon)
		{}
	private:
			sf::Vector2f xConstrains, yConstrains;
			bool testSingleConstrain(sf::Vector2f constrain, float pos){
				if(pos >  constrain.x) 
					return true;
				if(pos <  constrain.y)
					return true;

				return false;
			}
	} windowConstrains;

};

#endif
