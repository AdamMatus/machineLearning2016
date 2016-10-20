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
		//barriers.push_back(windowConstrains);	//TODO ?? is it necessery to
		//implement?
	}

	void add_barrier(const sf::RectangleShape& );
	void add_barrier(const sf::Vector2f xCon, const sf::Vector2f yCon);
	bool getNextRectToDraw(sf::RectangleShape& rs) const // polling fun
	{
		static size_t index = 0;
		auto b_iter = barriers.begin() + index;

		if(b_iter == barriers.end())
		{
			index = 0;
			return false;
		}

		rs = (*b_iter).getBarrierRect();
		index++;
		return true;

	}
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
		sf::RectangleShape getBarrierRect() const
		{
			sf::RectangleShape rs(sf::Vector2f(xConstrains.y-xConstrains.x,yConstrains.y-yConstrains.x));
			rs.setPosition(xConstrains.x, yConstrains.x); //up-left corner
			return rs;
		}
		Barrier(sf::Vector2f xCon, sf::Vector2f yCon):
			xConstrains(xCon),
			yConstrains(yCon),
			lastCarDir(sf::Vector2f(0,0))
		{}
	private:
			sf::Vector2f xConstrains, yConstrains;
			sf::Vector2f lastCarDir; //versor onnly TODO change implementation for more than 1 car
			bool testSingleConstrain(sf::Vector2f constrain, float pos){
				if(pos >  constrain.x) 
					if(pos <  constrain.y)
						return true;

				return false;
			}
	};


};

#endif
