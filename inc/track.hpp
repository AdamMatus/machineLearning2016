#ifndef _TRACK_HPP_
#define _TRACK_HPP_

#include <SFML/Graphics.hpp>

#include <chrono>
#include <vector>
#include <memory>

#include <car.hpp>

class Car;

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
	int trackMoveUntilBarrier(Car&, int limit); //if limit is negative then fun returns 0

private:
	class Barrier;
	std::vector<std::unique_ptr<Barrier>> barriers;


	class Barrier{
	public:
		bool testConstrains(const Car& contextCar);
		virtual sf::RectangleShape getBarrierRect() const
		{
			sf::RectangleShape rs(sf::Vector2f(xConstrains.y-xConstrains.x,yConstrains.y-yConstrains.x));
			rs.setPosition(xConstrains.x, yConstrains.x); //up-left corner
			rs.setFillColor(sf::Color::White);
			return rs;
		}
		virtual	void interactWithBarrier(Car& contextCar);
		Barrier(sf::Vector2f xCon, sf::Vector2f yCon):
			xConstrains(xCon),
			yConstrains(yCon)
		{}
		virtual ~Barrier() {}
	private:
			sf::Vector2f xConstrains, yConstrains;
			bool testSingleConstrain(sf::Vector2f constrain, float pos){
				if(pos >  constrain.x) 
					if(pos <  constrain.y)
						return true;

				return false;
			}
	}; //~Barrier class def

	class TexturedBarrier : public Barrier {
		public:
			TexturedBarrier(sf::Vector2f xCon, sf::Vector2f yCon) :
				Barrier(xCon, yCon) 
			{
				if(!texBarrier.loadFromFile("aux/barrier.png"))
				{
					return;
				}
			}

			sf::RectangleShape getBarrierRect() const
			{
				auto rs =	Barrier::getBarrierRect();
				rs.setTexture(&texBarrier);
				return rs;
			}
			~TexturedBarrier() { }

		private:
			sf::Texture texBarrier;

	}; //~textured barrier

	class FinishBarrier : public Barrier {
		public:
			FinishBarrier(sf::Vector2f xCon, sf::Vector2f yCon) :
				Barrier(xCon, yCon)
			{
				if(!checkeredTexture.loadFromFile("aux/checkered.png"))
				{
					return;
				}
			}

			sf::RectangleShape getBarrierRect() const
			{
				auto rs =	Barrier::getBarrierRect();
				rs.setTexture(&checkeredTexture);
				return rs;
			}
			void interactWithBarrier(Car& car);
			~FinishBarrier() {}
		private:
			sf::Texture checkeredTexture;

	}; //~FinishBarrier class def

}; //~Track class def

#endif
