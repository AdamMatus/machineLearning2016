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
	
	barriers.push_back(std::unique_ptr<Barrier>(new Barrier{xConstrains, yConstrains}));
}

void Track::add_barrier(sf::Vector2f xCon, sf::Vector2f yCon)
{
	barriers.push_back(std::unique_ptr<Barrier>{new Barrier(xCon, yCon)}); //TODO throw exce if xCon.x < xCon.y etc.
}

void Track::add_finish_barrier(sf::Vector2f xCon, sf::Vector2f yCon)
{
	barriers.push_back(std::unique_ptr<Barrier>{new FinishBarrier(xCon,yCon)});
}

void Track::trackMove(Car& contextCar)
{
	
	for(auto &b : barriers)
	{	
		b->interactWithBarrier(contextCar);
	}
	
}

void Track::Barrier::interactWithBarrier(Car& contextCar)
{
		auto dirInfo = this->getLastCarDir();
		auto aux_acc = sf::Vector2f(0,0);

		this->updateCollisionInfo(contextCar);	

		if(this->testConstrains(contextCar))
		{
			if(!dirInfo.x)
			{
				if(!dirInfo.y) return; //if last time car was active constrains allow to go out
				aux_acc.y = -2*contextCar.getVelocity().y;
			}
			else if(!dirInfo.y)
			{
				aux_acc.x = -2*contextCar.getVelocity().x;
			}
			else //non of them is zero
			{
				aux_acc.x = -2*contextCar.getVelocity().x;
				aux_acc.y = -2*contextCar.getVelocity().y;
			}
		}

	contextCar.accelerate(sf::Vector2f(0,0), aux_acc); 
}

void Track::FinishBarrier::interactWithBarrier(Car& contextCar)
{
	if(this->testConstrains(contextCar))	
	{
		contextCar.markAsFinished();
	}
}

