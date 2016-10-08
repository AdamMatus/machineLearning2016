#ifndef _TRACK_HPP_
#define _TRACK_HPP_

#include <SFML/Graphics.hpp>

#include <chrono>

#include "../inc/car.hpp"

class Track{
private:
	const sf::Vector2f xConstrains;
	const sf::Vector2f yConstrains;

	const std::chrono::milliseconds quantum_time;


	bool testConstrain(sf::Vector2f constrain, float pos){
		if(pos < constrain.x) //lower constrain
			return false;
		if(pos > constrain.y) //upper constrain
			return false;

		return true;
	}

public:
	Track(const sf::Vector2u& winSize, const std::chrono::milliseconds q_time) :
	 	xConstrains{0,static_cast<float>(winSize.x)},
	 	yConstrains{0,static_cast<float>(winSize.y)},
		quantum_time{q_time}	
	{}
	void trackMove(Car&);
};

#endif
