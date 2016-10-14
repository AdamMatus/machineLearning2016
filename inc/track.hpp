#ifndef _TRACK_HPP_
#define _TRACK_HPP_

#include <SFML/Graphics.hpp>

#include <chrono>
#include <vector>

#include "../inc/car.hpp"

class Track{
public:
	Track(const sf::Vector2u& winSize, const std::chrono::milliseconds q_time) :
		quantum_time{q_time}
	{
		//barriers.push_back(windowConstrains);	
	}

	void add_barrier(const sf::RectangleShape& );
	void trackMove(Car&);

private:
	class Barrier;
	std::vector<Barrier> barriers;

	const std::chrono::milliseconds quantum_time;

	class Barrier{
	public:
		bool testConstrains(const Car& contextCar);
		void updateCollisionInfo(const Car& contextCar)
		{
			lastCarDir.x = !testSingleConstrain(xConstrains, contextCar.getPosition().x);
			lastCarDir.y = !testSingleConstrain(yConstrains, contextCar.getPosition().y);
		}
		sf::Vector2f getLastCarDir() const
		{
			return lastCarDir;	
		}
		Barrier(sf::Vector2f xCon, sf::Vector2f yCon):
			xConstrains(xCon),
			yConstrains(yCon),
			lastCarDir(sf::Vector2f(0,0))
		{}
	private:
			sf::Vector2f xConstrains, yConstrains;
			sf::Vector2f lastCarDir; //versor onnly
			bool testSingleConstrain(sf::Vector2f constrain, float pos){
				if(pos >  constrain.x) 
					if(pos <  constrain.y)
						return true;

				return false;
			}
	};


};

#endif
