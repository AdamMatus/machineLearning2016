#include "../inc/track.hpp"

bool Track::Barrier::testConstrains(const Car& contextCar)
{
	auto carPosition = contextCar.getPosition();

	if(	testSingleConstrain(xConstrains, carPosition.x) &&
			testSingleConstrain(yConstrains, carPosition.y))
		return true;
	else
		return false;
}

void Track::add_barrier(const sf::RectangleShape& rs)
{
	sf::Vector2f xConstrains = sf::Vector2f(rs.getPosition().x,
																				 	rs.getPosition().x + rs.getSize().x) ;
	sf::Vector2f yConstrains = sf::Vector2f(rs.getPosition().y,
																					rs.getPosition().y + rs.getSize().y) ;
	
	barriers.push_back(Barrier(xConstrains, yConstrains));
}

void Track::add_barrier(sf::Vector2f xCon, sf::Vector2f yCon)
{
	barriers.push_back(Barrier(xCon, yCon)); //TODO throw exce if xCon.x < xCon.y etc.
}

void Track::trackMove(Car& contextCar)
{
	auto aux_acc = sf::Vector2f(0,0);
	
	for(auto &b : barriers)
	{	
		auto dirInfo = b.getLastCarDir();
		b.updateCollisionInfo(contextCar);	

		if(b.testConstrains(contextCar))
		{
			if(!dirInfo.x)
			{
				if(!dirInfo.y) break; //if last time car was active constrains allow to go out
				aux_acc.y = -2*contextCar.getVelocity().y;
				break;
			}
			else if(!dirInfo.y)
			{
				aux_acc.x = -2*contextCar.getVelocity().x;
				break;
			}
			else //non of them is zero
			{
				aux_acc.x = -1.5*contextCar.getVelocity().x;
				aux_acc.y = -1.5*contextCar.getVelocity().y;
				break;
			}
		}
	}
	
	contextCar.accelerate(quantum_time, sf::Vector2f(0,0), aux_acc); 
}
