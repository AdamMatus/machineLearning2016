#ifndef _TRACK_HPP_
#define _TRACK_HPP_

#include <SFML/Graphics.hpp>

#include <chrono>
#include <vector>
#include <memory>

#include "../inc/car.hpp"

class Track{
public:

	Track(const sf::Vector2u& winSize)
	{
		//barriers.push_back(windowConstrains);	//TODO ?? is it necessery to
		//implement? maybe just remb winSize
	}

	void add_barrier(const sf::RectangleShape& );
	void add_barrier(sf::Vector2f xCon, sf::Vector2f yCon);
	void add_finish_barrier(sf::Vector2f xCon, sf::Vector2f);
	void add_finish_barrier(const sf::RectangleShape& rs)
	{
		add_finish_barrier(
				sf::Vector2f(rs.getPosition().x, rs.getPosition().x + rs.getSize().x),
				sf::Vector2f(rs.getPosition().y, rs.getPosition().y + rs.getSize().y)
		);

	}
	bool getNextRectToDraw(sf::RectangleShape& rs) const // polling fun
	{
		static size_t index = 0;
		auto b_iter = barriers.begin() + index; //barriers.begin can change

		if(b_iter == barriers.end())
		{
			index = 0;
			return false;
		}

		rs = (*b_iter)->getBarrierRect();
		index++;
		return true;
	}
	void trackMove(Car&);

private:
	class Barrier;
	std::vector<std::unique_ptr<Barrier>> barriers;


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
		virtual	void interactWithBarrier(Car& contextCar);
		Barrier(sf::Vector2f xCon, sf::Vector2f yCon):
			quantum_time(std::chrono::milliseconds(25)), //TODO 
			xConstrains(xCon),
			yConstrains(yCon),
			lastCarDir(sf::Vector2f(0,0))
		{}
		virtual ~Barrier() {}
	private:
			const std::chrono::milliseconds quantum_time ;
			sf::Vector2f xConstrains, yConstrains;
			sf::Vector2f lastCarDir; //versor onnly TODO change implementation for more than 1 car
			bool testSingleConstrain(sf::Vector2f constrain, float pos){
				if(pos >  constrain.x) 
					if(pos <  constrain.y)
						return true;

				return false;
			}
	}; //~Barrier class def

	class FinishBarrier : public Barrier {
		public:
			FinishBarrier(sf::Vector2f xCon, sf::Vector2f yCon) :
				Barrier(xCon, yCon)
		{}
			void interactWithBarrier(Car& car);
			~FinishBarrier() {};

	}; //~FinishBarrier class def

}; //~Track class def

#endif
