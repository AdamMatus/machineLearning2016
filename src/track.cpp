#include "../inc/track.hpp"

sf::Vector2f Track::Barrier::testConstrains(const Car& contextCar)
{
	auto carPosition = contextCar.getPosition();
	auto collisionActiveConstrains = sf::Vector2f(0,0);

	collisionActiveConstrains.x = testSingleConstrain(xConstrains, carPosition.x);
	collisionActiveConstrains.y = testSingleConstrain(yConstrains, carPosition.y);

	return collisionActiveConstrains;
}

void Track::trackMove(Car& contextCar)
{
	auto pastActiveConstrain = contextCar.getCollisionState();
	auto aux_acc = sf::Vector2f(0,0);
	
	for(auto b : barriers)
	{	
		auto activeConstrains = b.testConstrains(contextCar);

		if(activeConstrains.x > 0)
		{
			if(pastActiveConstrain.x == 0)
			{
				auto currentVelocity = contextCar.getVelocity().x;
				aux_acc.x  = -2*currentVelocity;
				contextCar.setCollisionStateX(true);
				break;
			}
		}
		else
			contextCar.setCollisionStateX(false);

		if(activeConstrains.y > 0)
		{
			if(pastActiveConstrain.y == 0)
			{
				auto currentVelocity = contextCar.getVelocity().y;
				aux_acc.y  = -2*currentVelocity;
				contextCar.setCollisionStateY(true);
				break;
			}
			else
				contextCar.setCollisionStateY(false);
		}
	}
	
	contextCar.accelerate(quantum_time, sf::Vector2f(0,0), aux_acc); 
}
