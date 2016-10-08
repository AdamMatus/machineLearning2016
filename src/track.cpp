#include "../inc/track.hpp"


void Track::trackMove(Car& contextCar)
{
	auto actualPosition = contextCar.getPosition();
	auto aux_acc = sf::Vector2f(0,0);
	
	if(!testConstrain(xConstrains, actualPosition.x))
	{
		if(!contextCar.inConstrain())
		{
			auto currentVelocity = contextCar.getVelocity().x;
			aux_acc.x = -2*currentVelocity;
			contextCar.inConstrain(true);
		}
	}
	if(!testConstrain(yConstrains, actualPosition.y))
	{
		if(!contextCar.inConstrain())
		{
			auto currentVelocity = contextCar.getVelocity().y;
			aux_acc.y = -2*currentVelocity;
			contextCar.inConstrain(true);
		}
	}
	else
		contextCar.inConstrain(false);
	
	contextCar.accelerate(quantum_time, sf::Vector2f(0,0), aux_acc); 
}
